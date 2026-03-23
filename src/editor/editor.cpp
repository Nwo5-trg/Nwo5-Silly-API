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
        static std::vector<std::string> removedEditTabButtons;

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
                
                std::vector<std::pair<int, std::pair<CCArray*, CCObject*>>> editButtons;

                auto i = m_editButtonDict->allKeys()->count();

                for (auto key : CCArrayExt<CCInteger*>(m_editButtonDict->allKeys())) {
                    auto obj = m_editButtonDict->objectForKey(key->getValue());

                    editButtons.emplace_back(
                        -(i--), std::pair<CCArray*, CCObject*>{
                            nwo5::utils::objectsBefore(m_editButtonBar->m_buttonArray, obj, false), obj
                        }
                    );
                    nwo5::utils::removeObjectsFromArray(
                        m_editButtonBar->m_buttonArray, 
                        nwo5::utils::objectsBefore(m_editButtonBar->m_buttonArray, obj, true)
                    );
                    
                }
                editButtons.emplace_back(
                    0, std::pair<CCArray*, CCObject*>{CCArray::createWithArray(m_editButtonBar->m_buttonArray), nullptr}
                );
                nwo5::utils::removeAllObjects(m_editButtonBar->m_buttonArray);

                std::ranges::sort(editButtons, [] (const auto& pA, const auto& pB) {
                    return pA < pB;
                });

                editTabButtonMap.clear();
                i = 0;

                for (const auto& [prio, buttons] : editButtons) {
                    const auto& [array, robtop] = buttons;

                    m_editButtonBar->m_buttonArray->addObjectsFromArray(array);

                    while(i < impl::editTabButtons.size() && impl::editTabButtons[i].prio <= prio) {
                        const auto& data = impl::editTabButtons[i++];
                        auto button = createEditTabButton(data);

                        m_editButtonBar->m_buttonArray->addObject(button);
                        editTabButtonMap[data.key] = button;
                    }

                    if (!robtop) {
                        continue;
                    }

                    const auto shouldBeRemoved = std::ranges::contains(
                        impl::removedEditTabButtons, std::string{static_cast<CCNode*>(robtop)->getID()}
                    );

                    static_cast<CCNode*>(robtop)->setVisible(!shouldBeRemoved);

                    if (!shouldBeRemoved) {
                        m_editButtonBar->m_buttonArray->addObject(robtop);
                    }
                }

                m_editButtonBar->reloadItems(
                    GameManager::sharedState()->getIntGameVariable("0049"), 
                    GameManager::sharedState()->getIntGameVariable("0050")
                );

                editButtonsLoaded = true;
            }
        };

        int nextFreeGroupFast(int pOffset) {
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
        void createUndoObject(UndoCommand pCommand) {
            ui()->createUndoObject(pCommand, false);
        }
        void toggleMoveObject(bool pMove) {
            shouldMoveObject = pMove;
        }
        CCMenuItemSpriteExtra* createEditTabButton(const EditTabButton& pButton) {
            return ui()->getSpriteButton(pButton.spriteFunc(), pButton.callback, nullptr, pButton.scale, 1, CCPointZero);
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

    bool registerEditTabButton(impl::EditTabButton::SpriteFunc pSprite, std::string pKey, float pScale, int pPrio, SEL_MenuHandler pCallback) {
        if (
            std::ranges::find_if(impl::editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }) != impl::editTabButtons.end()
        ) {
            return false;
        }

        impl::editTabButtons.emplace_back(pKey, pPrio, pScale, std::move(pSprite), pCallback);

        std::ranges::sort(impl::editTabButtons, [] (const auto& pA, const auto& pB) {
            return pA.prio < pB.prio;
        });

        return true;
    }
    bool registerEditTabButton(std::string pSprite, float pScale, int pPrio, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, pSprite, pScale, pPrio, pCallback);
    }
    bool registerEditTabButton(std::string pSprite, int pPrio, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, pSprite, 1.0f, pPrio, pCallback);
    }
    bool registerEditTabButton(std::string pSprite, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::create(pSprite.c_str()); }, pSprite, 1.0f, 0, pCallback);
    }
    bool registerEditTabButtonFrame(std::string pSprite, float pScale, int pPrio, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, pSprite, pScale, pPrio, pCallback);
    }
    bool registerEditTabButtonFrame(std::string pSprite, int pPrio, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, pSprite, 1.0f, pPrio, pCallback);
    }
    bool registerEditTabButtonFrame(std::string pSprite, SEL_MenuHandler pCallback) {
        return registerEditTabButton([=] () { return CCSprite::createWithSpriteFrameName(pSprite.c_str()); }, pSprite, 1.0f, 0, pCallback);
    }
    bool unregisterEditTabButton(const std::string& pKey, bool pRestore) {
        if (
            const auto it = std::ranges::find_if(impl::editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }); it != impl::editTabButtons.end()
        ) {
            impl::editTabButtonMap.erase((*it).key);
            impl::editTabButtons.erase(it);

            return true;
        }

        const auto it = std::ranges::find(impl::removedEditTabButtons, pKey);

        if (it == impl::removedEditTabButtons.end() && !pRestore) {
            impl::removedEditTabButtons.push_back(pKey);
        }
        else if (it != impl::removedEditTabButtons.end() && pRestore) {
            impl::removedEditTabButtons.erase(it);
        }
        else {
            return false;
        }

        return true;
    }
    CCMenuItemSpriteExtra* getEditTabButton(const std::string& pKey) {
        if (!ui() || !impl::editButtonsLoaded) {
            return nullptr;
        }

        if (const auto it = impl::editTabButtonMap.find(pKey); it != impl::editTabButtonMap.end()) {
            return (*it).second;
        }

        return nullptr;
    }
    void toggleEditTabButton(const std::string& pKey, bool pOn) {
        auto button = getEditTabButton(pKey);

        if (!button) {
            return;
        }

        // lowkey robtop does it differently but who cares
        button->setColor(pOn ? ccWHITE : ccc3(150, 150, 150));
        button->setEnabled(pOn);
    }
}