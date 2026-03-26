#include <editor/include.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor {
    namespace impl {
        static bool shouldMoveObject;

        static bool editButtonsLoaded;
        static std::vector<EditTabButton> editTabButtons;
        static std::unordered_map<std::string, CCMenuItemSpriteExtra*> editTabButtonMap;
        static std::unordered_set<std::string> removedEditTabButtons;

        static int nextFreeGroupFast(int pOffset) {
            pOffset = std::clamp(pOffset, 1, editor::constants::MAX_GROUPS);

            auto keys = layer()->m_groupDict->allKeys();

            if (!keys->count()) {
                return pOffset;
            }

            std::set<int> usedGroups;

            for (auto key : CCArrayExt<CCInteger*>(keys)) {
                usedGroups.insert(key->getValue());
            }

            for (auto it = usedGroups.lower_bound(pOffset); it != usedGroups.end(); it++) {
                if (*it == pOffset) {
                    pOffset++;
                } 
                else {
                    return pOffset;
                }
            }
            
            return pOffset > editor::constants::MAX_GROUPS ? 0 : pOffset;
        }
        static CCMenuItemSpriteExtra* createEditTabButton(const EditTabButton& pButton) {
            auto button = ui()->getSpriteButton(pButton.spriteFunc(), nullptr, nullptr, pButton.scale, 1, CCPointZero);

            // i *think* this is the correct thing to do cuz i shouldnt be std::move-ing a member var
            cocos::CCMenuItemExt::assignCallback(button, geode::Function<void(CCMenuItemSpriteExtra*)>{pButton.callback});

            return button;
        }
        static void tryRegisterEditTabButton(CCObject* pButton) {
            if (!pButton) {
                return;
            }

            const auto shouldBeRemoved = impl::removedEditTabButtons.contains(
                static_cast<CCNode*>(pButton)->getID()
            );

            static_cast<CCNode*>(pButton)->setVisible(!shouldBeRemoved);

            if (!shouldBeRemoved) {
                ui()->m_editButtonBar->m_buttonArray->addObject(pButton);
            }
        }

        class $modify(UtilsEditorUI, EditorUI) {
            bool init(LevelEditorLayer* editorLayer) {
                shouldMoveObject = true;
                editButtonsLoaded = false;
                
                return EditorUI::init(editorLayer);
            }

            void moveObject(GameObject* obj, CCPoint amount) {
                if (shouldMoveObject) {
                    EditorUI::moveObject(obj, amount);
                }
            }

            void createMoveMenu() {
                EditorUI::createMoveMenu();
                
                auto& buttonArray = m_editButtonBar->m_buttonArray;

                std::vector<CCObject*> robtopButtons;

                for (auto obj : buttonArray->asExt()) {
                    if (!obj->getTag()) {
                        continue;
                    }

                    const auto str = static_cast<CCNode*>(obj)->getID().view();

                    // i rly dont wanna make more robust checks so if someone adds a non prefixed editor button with a tag thats on them
                    if (!str.empty() && !str.contains('/') && !str.contains('.') && str.contains("-button")) {
                        robtopButtons.push_back(obj);
                    }
                }

                std::vector<std::pair<int, std::pair<CCArray*, CCObject*>>> editButtons;

                auto i = robtopButtons.size();

                for (auto obj : robtopButtons) {
                    editButtons.emplace_back(
                        -(i--), std::pair<CCArray*, CCObject*>{
                            nwo5::utils::objectsBefore(buttonArray, obj, false), obj
                        }
                    );
                    nwo5::utils::removeObjectsFromArray(
                        buttonArray, 
                        nwo5::utils::objectsBefore(buttonArray, obj, true)
                    );
                    
                }

                CCArray* remainingCustomButtons = CCArray::create();

                for (auto obj : buttonArray->asExt()) {
                    remainingCustomButtons->addObject(obj);
                }

                editButtons.emplace_back(0, std::pair<CCArray*, CCObject*>{remainingCustomButtons, nullptr});
                nwo5::utils::removeAllObjects(buttonArray);

                std::ranges::sort(editButtons, [] (const auto& pA, const auto& pB) {
                    return pA < pB;
                });

                editTabButtonMap.clear();
                i = 0;

                for (const auto& [prio, buttons] : editButtons) {
                    const auto& [array, robtop] = buttons;

                    buttonArray->addObjectsFromArray(array);

                    while(i < impl::editTabButtons.size() && impl::editTabButtons[i].prio <= prio) {
                        const auto& data = impl::editTabButtons[i++];

                        auto button = createEditTabButton(data);
                        button->setID(data.key);

                        tryRegisterEditTabButton(button);
                        editTabButtonMap[data.key] = button;
                    }

                    tryRegisterEditTabButton(robtop);
                }

                m_editButtonBar->reloadItems(
                    GameManager::sharedState()->getIntGameVariable("0049"), 
                    GameManager::sharedState()->getIntGameVariable("0050")
                );

                editButtonsLoaded = true;
            }
        };

        void createUndoObject(UndoCommand pCommand) {
            ui()->createUndoObject(pCommand, false);
        }
        void toggleMoveObject(bool pMove) {
            shouldMoveObject = pMove;
        }
    }

    bool loaded() {
        return layer();
    }

    void update(bool pUpdateControls, bool pOtherwiseDeactivateControls) {
        auto editor = ui();

        editor->updateButtons();
        editor->updateObjectInfoLabel();
        editor->updateGridNodeSize();
        editor->tryUpdateTimeMarkers();
        editor->updateStickyControls();
        
        if (pUpdateControls) {
            if (auto control = editor->m_rotationControl; control && control->isVisible()) {
                activateRotationControl();
            }
            if (auto control = editor->m_scaleControl; control && control->isVisible()) {
                activateScaleControl(!control->m_scaleLabel->isVisible());
            }
            if (auto control = editor->m_transformControl; control && control->isVisible()) {
                activateTransformControl();
            }
        }
        else if (pOtherwiseDeactivateControls) {
            editor->deactivateRotationControl();
            editor->deactivateScaleControl();
            editor->deactivateTransformControl();
        }
    }

    float zoom() {
        return layer()->m_objectLayer->getScale();
    }
    CCPoint center() {
        return CCPoint{
            (CCDirector::get()->getWinSize() / 2) - CCPoint{
                layer()->m_objectLayer->getPositionX(), 
                layer()->m_objectLayer->getPositionY() - ui()->m_toolbarHeight / 2
            }
         } / zoom();
    }

    void activateRotationControl(bool pRefresh) {
        if (!ui()->m_rotationControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateRotationControl();
        }
        else if (ui()->m_rotationControl->isVisible()) {
            return;
        }

        ui()->activateRotationControl(nullptr);
    }
    void activateScaleControl(bool pXY, bool pRefresh) {
        if (!ui()->m_scaleControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateScaleControl();
        }
        else if (ui()->m_scaleControl->isVisible()) {
            return;
        }

        auto obj = CCNode::create();
        obj->setTag(pXY ? 30 : 29);

        ui()->activateScaleControl(obj);
    }
    void activateTransformControl(bool pRefresh) {
        if (!ui()->m_transformControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateTransformControl();
        }
        else if (ui()->m_transformControl->isVisible()) {
            return;
        }

        ui()->activateTransformControl(nullptr);
    }

    int currentLayer() {
        return layer()->m_currentLayer;
    }
    bool layerSelectable(int pLayer, bool pIgnoreLocked) {
        if (pLayer > editor::constants::MAX_LAYERS || (!pIgnoreLocked && layerLocked(pLayer))) {
            return false;
        }

        const auto layer = currentLayer();

        return layer == editor::constants::ALL_LAYERS || layer == pLayer;
    }
    bool layerLocked(int pLayer) {
        return layer()->isLayerLocked(pLayer);
    }
    void setLayer(int pLayer) {
        if (pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS) {
            return;
        }

        layer()->m_currentLayer = pLayer;
        // its fucking crazy to me that robtop calls layers "groups" internally :sob:
        ui()->updateGroupIDLabel();
    }
    void lockLayer(int pLayer) {
        if (pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS) {
            return;
        }

        const auto ret = currentLayer();

        layer()->m_currentLayer = pLayer;
        ui()->onLockLayer(nullptr);

        layer()->m_currentLayer = ret;
    }

    int nextFreeGroup(int pOffset, bool pCheckTargetGroups) {
        if (!pCheckTargetGroups) {
            return impl::nextFreeGroupFast(pOffset);
        }

        pOffset = std::clamp(pOffset, 1, 9999);

        auto objs = editor::object::getAll();

        if (!objs->count()) {
            return pOffset;
        }

        std::set<int> usedGroups;

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (obj->m_groups) {
                for (const auto group : *obj->m_groups) {
                    if (group) {
                        usedGroups.insert(group);
                    }
                }
            }

            if (obj->m_isTrigger) {
                if (const auto group = static_cast<EffectGameObject*>(obj)->m_targetGroupID) {
                    usedGroups.insert(group);
                }
                if (const auto group = static_cast<EffectGameObject*>(obj)->m_centerGroupID) {
                    usedGroups.insert(group);
                }
            }
        }

        for (auto it = usedGroups.lower_bound(pOffset); it != usedGroups.end(); it++) {
            if (*it == pOffset) {
                pOffset++;
            } 
            else {
                return pOffset;
            }
        }
        
        return pOffset > constants::MAX_GROUPS ? 0 : pOffset;
    }

    bool registerEditTabButton(impl::EditTabButton::SpriteFunc pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback) {
        if (
            std::ranges::find_if(impl::editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }) != impl::editTabButtons.end()
        ) {
            return false;
        }

        impl::editTabButtons.emplace_back(std::move(pKey), pPrio, pScale, std::move(pSprite), std::move(pCallback));

        std::ranges::sort(impl::editTabButtons, [] (const auto& pA, const auto& pB) {
            return pA.prio < pB.prio;
        });

        if (const auto it = impl::removedEditTabButtons.find(pKey); it != impl::removedEditTabButtons.end()) {
            impl::removedEditTabButtons.erase(it);
        }

        return true;
    }
    bool registerEditTabButton(std::string pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, std::move(pKey), pScale, pPrio, std::move(pCallback));
    }
    bool registerEditTabButton(std::string pSprite, std::string pKey, int pPrio, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, std::move(pKey), 1.0f, pPrio, std::move(pCallback));
    }
    bool registerEditTabButton(std::string pSprite, std::string pKey, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, std::move(pKey), 1.0f, 0, std::move(pCallback));
    }
    bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, std::move(pKey), pScale, pPrio, std::move(pCallback));
    }
    bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, int pPrio, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, std::move(pKey), 1.0f, pPrio, std::move(pCallback));
    }
    bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, impl::EditTabButton::Callback pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, std::move(pKey), 1.0f, 0, std::move(pCallback));
    }
    bool unregisterEditTabButton(const std::string& pKey, bool pRestore) {
        if (
            const auto it = std::ranges::find_if(impl::editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }); it != impl::editTabButtons.end()
        ) {
            impl::editTabButtonMap.erase((*it).key);
            impl::editTabButtons.erase(it);
        }

        const auto it = impl::removedEditTabButtons.find(pKey);

        if (it == impl::removedEditTabButtons.end() && !pRestore) {
            impl::removedEditTabButtons.insert(pKey);

            return true;
        }
        else if (it != impl::removedEditTabButtons.end() && pRestore) {
            impl::removedEditTabButtons.erase(it);

            return true;
        }

        return false;
    }
    CCMenuItemSpriteExtra* getEditTabButton(const std::string& pKey) {
        if (!ui() || !impl::editButtonsLoaded) {
            return nullptr;
        }

        if (const auto it = impl::editTabButtonMap.find(pKey); it != impl::editTabButtonMap.end()) {
            return (*it).second;
        }

        for (auto obj : CCArrayExt<CCMenuItemSpriteExtra*>(ui()->m_editButtonBar->m_buttonArray)) {
            if (obj->getID() == pKey) {
                return obj;
            }
        }

        return nullptr;
    }
    void toggleEditTabButton(const std::string& pKey, bool pOn) {
        auto button = getEditTabButton(pKey);

        if (!button) {
            return;
        }

        button->getChildByType<ButtonSprite*>(0)->setColor(pOn ? ccWHITE : ccc3(150, 150, 150));
        button->setEnabled(pOn);
    }
    bool isEditTabButtonRegistered(const std::string& pKey) {
        if (auto button = getEditTabButton(pKey)) {
            return button->isVisible();
        }
        else {
            return false;
        }
    }
}