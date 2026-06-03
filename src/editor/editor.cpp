#include <editor/include.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor {
    namespace impl {
        static bool s_shouldMoveObject;

        static bool s_editButtonsLoaded;
        static std::vector<EditTabButton> s_editTabButtons;
        static std::unordered_map<std::string, CCMenuItemSpriteExtra*> s_editTabButtonMap;
        static std::unordered_set<std::string> s_removedEditTabButtons;

        static EditorUI* s_editorUIEarlyPtr;

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
        static void tryRegisterEditTabButton(CCObject* pButton, CCArray* pArray) {
            if (!pButton) {
                return;
            }

            const auto shouldBeRemoved = s_removedEditTabButtons.contains(
                static_cast<CCNode*>(pButton)->getID()
            );

            static_cast<CCNode*>(pButton)->setVisible(!shouldBeRemoved);

            if (!shouldBeRemoved) {
                pArray->addObject(pButton);
            }
        }

        class $modify(UtilsEditorUI, EditorUI) {
            void updateEditorTabButtons() {
                if (notLoaded(LoadedType::UI)) {
                    return;
                }
                
                auto& buttonArray = m_editButtonBar->m_buttonArray;

                std::vector<CCObject*> robtopButtons;

                for (auto obj : buttonArray->asExt()) {
                    if (obj->getTag()) {
                        robtopButtons.push_back(obj);
                    }
                }

                std::vector<std::pair<int, std::pair<CCArray*, CCObject*>>> editButtons;

                auto i = robtopButtons.size();

                for (auto obj : robtopButtons) {
                    editButtons.emplace_back(
                        -(i--), std::pair<CCArray*, CCObject*>{
                            nwo5::utils::array::before(buttonArray, obj, false), obj
                        }
                    );
                    nwo5::utils::array::remove(
                        buttonArray, 
                        nwo5::utils::array::before(buttonArray, obj, true)
                    );
                }

                CCArray* remainingCustomButtons = CCArray::create();

                for (auto obj : buttonArray->asExt()) {
                    remainingCustomButtons->addObject(obj);
                }

                constexpr size_t BACK_BUTTONS = 0;

                editButtons.emplace_back(BACK_BUTTONS, std::pair<CCArray*, CCObject*>{remainingCustomButtons, nullptr});

                nwo5::utils::array::clear(buttonArray);

                s_editTabButtonMap.clear();

                i = 0;

                for (const auto& [prio, buttons] : editButtons) {
                    const auto& [array, robtop] = buttons;

                    for (auto button : CCArrayExt<CCNode>(array)) {
                        tryRegisterEditTabButton(button, buttonArray);
                    }

                    while(
                        i < s_editTabButtons.size() 
                        && (s_editTabButtons[i].prio <= prio || prio == BACK_BUTTONS)
                    ) {
                        const auto& data = s_editTabButtons[i++];
                        const auto& key = data.key;

                        if (
                            nwo5::utils::array::find(buttonArray, [key] (auto pPtr) {
                                return pPtr && static_cast<CCNode*>(pPtr)->getID() == key;
                            }).has_value()
                        ) {
                            continue;
                        }

                        auto button = createEditTabButton(data);
                        button->setID(key);

                        tryRegisterEditTabButton(button, buttonArray);
                        s_editTabButtonMap[data.key] = button;
                    }

                    tryRegisterEditTabButton(robtop, buttonArray);
                }

                m_editButtonBar->reloadItems(
                    GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonsPerRow), 
                    GameManager::sharedState()->getIntGameVariable(GameVar::EditorButtonRows)
                );

                s_editButtonsLoaded = true;
            }

            void moveObject(GameObject* obj, CCPoint amount) {
                if (s_shouldMoveObject) {
                    EditorUI::moveObject(obj, amount);
                }
            }

            static void onModify(auto& pSelf) {
                (void)pSelf.setHookPriority("EditorUI::init", Priority::First);
            }

            bool init(LevelEditorLayer* editorLayer) {
                s_editorUIEarlyPtr = this;

                return EditorUI::init(editorLayer);
            }
        };

        class $modify(LevelEditorLayer) {
            bool init(GJGameLevel* level, bool noUI) {
                s_shouldMoveObject = true;
                s_editButtonsLoaded = false;
                s_editorUIEarlyPtr = nullptr;
                
                if (!LevelEditorLayer::init(level, noUI)) {
                    return false;
                }

                updateEditorTabButtons();

                return true;
            }
        };

        void createUndoObject(UndoCommand pCommand) {
            ui()->createUndoObject(pCommand, false);
        }
        void toggleMoveObject(bool pMove) {
            s_shouldMoveObject = pMove;
        }

        // hjfod
        struct FakePauseLayer final {
            char alloc[sizeof(EditorPauseLayer)]; 

            auto get() {
                return reinterpret_cast<EditorPauseLayer*>(&alloc);
            }
        };

        static EditorPauseLayer* getFakePauseLayer() {
            static auto pauseLayer = FakePauseLayer{};

            pauseLayer.get()->m_editorLayer = layer();

            return pauseLayer.get();
        }

        EditorUI* getEditorUI() {
            if (!loaded(LoadedType::EditorValid)) {
                return nullptr;
            }

            return s_editorUIEarlyPtr;
        }
    }

    bool loaded(LoadedType pType) {
        switch (pType) {
            case LoadedType::Editor: return layer() && !layer()->m_initializing;
            case LoadedType::EditorValid: return layer();
            case LoadedType::UI: return ui();
            case LoadedType::UIValid: return ui();
        }
    }
    bool notLoaded(LoadedType pType) {
        return !loaded(pType);
    }

    void update(bool pUpdateControls, bool pOtherwiseDeactivateControls) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        auto editor = ui();

        editor->updateButtons();
        editor->updateObjectInfoLabel();
        editor->updateGridNodeSize();
        editor->updateStickyControls();
        editor->m_editorLayer->m_drawGridLayer->m_updateTimeMarkers = true;
        
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
        return layer() ? layer()->m_objectLayer->getScale() : 0.0f;
    }
    CCPoint center(bool pToolbar) {
        if (notLoaded(LoadedType::UI)) {
            return CCPointZero;
        }
        
        return CCPoint{
            (CCDirector::get()->getWinSize() / 2) - CCPoint{
                layer()->m_objectLayer->getPositionX(), 
                layer()->m_objectLayer->getPositionY() - (pToolbar ? (ui()->m_toolbarHeight / 2) : 0.0f)
            }
        } / zoom();
    }
    CCSize size(bool pToolbar) {
        if (notLoaded(LoadedType::UI)) {
            return CCSizeZero;
        }
        
        return CCSize{
            CCDirector::get()->getWinSize().width,
            CCDirector::get()->getWinSize().height - (pToolbar ? ui()->m_toolbarHeight : 0.0f)
        } / zoom();
    }

    void move(cocos2d::CCPoint pPos) {
        if (notLoaded(LoadedType::UIValid)) {
            return;
        }

        const float scale = layer()->m_objectLayer->getScale();
        const auto currentPos = layer()->m_objectLayer->getPosition();

        ui()->moveGamelayer(
            -pPos * scale + CCDirector::get()->getWinSize() / 2 - currentPos
        );
    }

    bool isPlaytesting() {
        return layer() ? layer()->m_playbackMode == PlaybackMode::Playing : false;
    }
    PlaybackMode playbackMode() {
        return layer() ? layer()->m_playbackMode : PlaybackMode::Not;
    }

    void activateRotationControl(bool pRefresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
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
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_scaleControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateScaleControl();
        }
        else if (ui()->m_scaleControl->isVisible()) {
            return;
        }

        ui()->activateScaleControl(nwo5::utils::CCTag::create(pXY ? 30 : 29));
    }
    void activateTransformControl(bool pRefresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
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
        if (notLoaded(LoadedType::EditorValid)) {
            return editor::constants::ALL_LAYERS;
        }
        
        return layer()->m_currentLayer;
    }
    bool layerSelectable(int pLayer, bool pIgnoreLocked) {
        if (notLoaded(LoadedType::EditorValid) || pLayer > editor::constants::MAX_LAYERS || (!pIgnoreLocked && layerLocked(pLayer))) {
            return false;
        }
        
        const auto layer = currentLayer();

        return layer == editor::constants::ALL_LAYERS || layer == pLayer;
    }
    bool layerLocked(int pLayer) {
        return loaded(LoadedType::EditorValid) && layer()->isLayerLocked(pLayer);
    }
    void setLayer(int pLayer) {
        if (notLoaded(LoadedType::UI) || pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS) {
            return;
        }

        layer()->m_currentLayer = pLayer;
        // its fucking crazy to me that robtop calls layers "groups" internally :sob:
        ui()->updateGroupIDLabel();
    }
    void lockLayer(int pLayer, bool pLock) {
        if (notLoaded(LoadedType::UI) || pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS || layerLocked(pLayer) == pLock) {
            return;
        }

        const auto editorLayer = currentLayer();
        const auto lockingEnabled = layer()->m_layerLockingEnabled;

        layer()->m_currentLayer = pLayer;
        layer()->m_layerLockingEnabled = true;
        
        // i dont wanna re this function it looks like a bunch of math and im scared
        layer()->toggleLockActiveLayer();
        ui()->updateGroupIDLabel();

        layer()->m_currentLayer = editorLayer;
        layer()->m_layerLockingEnabled = lockingEnabled;
    }

    int nextFreeGroup(int pOffset, bool pCheckTargetGroups) {
        if (notLoaded(LoadedType::Editor)) {
            return 0;
        }
        
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

    void save() {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        impl::getFakePauseLayer()->saveLevel();
    }

    bool registerEditTabButton(impl::EditTabButton::SpriteFunc pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback) {
        if (
            std::ranges::find_if(impl::s_editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }) != impl::s_editTabButtons.end()
        ) {
            return false;
        }

        impl::s_editTabButtons.emplace_back(std::move(pKey), pPrio, pScale, std::move(pSprite), std::move(pCallback));

        std::ranges::sort(impl::s_editTabButtons, [] (const auto& pA, const auto& pB) {
            return pA.prio < pB.prio;
        });

        if (const auto it = impl::s_removedEditTabButtons.find(pKey); it != impl::s_removedEditTabButtons.end()) {
            impl::s_removedEditTabButtons.erase(it);
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
            const auto it = std::ranges::find_if(impl::s_editTabButtons, [&] (const auto& pButton) {
                return pButton.key == pKey;
            }); it != impl::s_editTabButtons.end()
        ) {
            impl::s_editTabButtonMap.erase((*it).key);
            impl::s_editTabButtons.erase(it);
        }

        const auto it = impl::s_removedEditTabButtons.find(pKey);

        if (it == impl::s_removedEditTabButtons.end() && !pRestore) {
            impl::s_removedEditTabButtons.insert(pKey);

            return true;
        }
        else if (it != impl::s_removedEditTabButtons.end() && pRestore) {
            impl::s_removedEditTabButtons.erase(it);

            return true;
        }

        return false;
    }
    CCMenuItemSpriteExtra* getEditTabButton(const std::string& pKey) {
        if (notLoaded(LoadedType::UI) || !impl::s_editButtonsLoaded) {
            return nullptr;
        }

        if (const auto it = impl::s_editTabButtonMap.find(pKey); it != impl::s_editTabButtonMap.end()) {
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
    void updateEditorTabButtons() {
        if (auto ptr = ui<impl::UtilsEditorUI>()) {
            ptr->updateEditorTabButtons();
        }
    }
}