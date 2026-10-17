#include <editor/include.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor {
    namespace impl {
        static bool s_shouldMoveObject = true;

        // its safe trust trust
        static EditorUI* s_editorUIEarlyPtr;

        class $modify(UtilsEditorUI, EditorUI) {
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
                s_editorUIEarlyPtr = nullptr;
                GameManager::get()->m_levelEditorLayer = this;
                
                return LevelEditorLayer::init(level, noUI);
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
            if (notLoaded(LoadedType::EditorValid)) {
                return nullptr;
            }

            return s_editorUIEarlyPtr;
        }
    }

    bool loaded(LoadedType pType) {
        switch (pType) {
            case LoadedType::Editor: return layer() && !layer()->m_initializing;
            case LoadedType::EditorValid: return layer();
            case LoadedType::UI: return layer() && impl::s_editorUIEarlyPtr;
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
    void moveTo(GameObject* pObj, bool pZoomToFit, float pZoomBuffer, float pMinimumZoom, float pMaximumZoom) {
        const auto bounds = editor::object::bounds(pObj, true);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                pMinimumZoom, pMaximumZoom
            )
        );
    }
    void moveTo(std::span<GameObject* const> pObjs, bool pZoomToFit, float pZoomBuffer, float pMinimumZoom, float pMaximumZoom) {
        const auto bounds = editor::object::bounds(pObjs, true);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                pMinimumZoom, pMaximumZoom
            )
        );
    }
    void moveTo(CCArray* pObjs, bool pZoomToFit, float pZoomBuffer, float pMinimumZoom, float pMaximumZoom) {
        const auto bounds = editor::object::bounds(pObjs);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                pMinimumZoom, pMaximumZoom
            )
        );
    }
    void setZoom(float pZoom) {
        if (notLoaded(LoadedType::UIValid)) {
            return;
        }

        if (!pZoom) {
            return;
        }

        ui()->updateZoom(pZoom);
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
            deactivateRotationControl();
        }
        else if (ui()->m_rotationControl->isVisible()) {
            return;
        }

        ui()->activateRotationControl(nullptr);
    }
    void deactivateRotationControl() {
        if (loaded(LoadedType::UI) && ui()->m_rotationControl && ui()->m_rotationControl->isVisible()) {
            ui()->deactivateRotationControl();
        }
    }
    void activateScaleControl(bool pXY, bool pRefresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_scaleControl) {
            return;
        }

        if (pRefresh) {
            deactivateScaleControl();
        }
        else if (ui()->m_scaleControl->isVisible()) {
            return;
        }

        ui()->activateScaleControl(nwo5::utils::CCTag::create(pXY ? 30 : 29));
    }
    void deactivateScaleControl() {
        if (loaded(LoadedType::UI) && ui()->m_scaleControl && ui()->m_scaleControl->isVisible()) {
            ui()->deactivateScaleControl();
        }
    }
    void activateTransformControl(bool pRefresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_transformControl) {
            return;
        }

        if (pRefresh) {
            deactivateTransformControl();
        }
        else if (ui()->m_transformControl->isVisible()) {
            return;
        }

        ui()->activateTransformControl(nullptr);
    }
    void deactivateTransformControl() {
        if (loaded(LoadedType::UI) && ui()->m_transformControl && ui()->m_transformControl->isVisible()) {
            ui()->deactivateTransformControl();
        }
    }

    int currentLayer() {
        if (notLoaded(LoadedType::EditorValid)) {
            return editor::constants::ALL_LAYERS;
        }
        
        return layer()->m_currentLayer;
    }
    bool layerSelectable(int pLayer, bool pIgnoreLocked) {
        if (notLoaded(LoadedType::EditorValid) || pLayer > editor::constants::MAX_LAYERS || pLayer < 0 || (!pIgnoreLocked && layerLocked(pLayer))) {
            return false;
        }
        
        const auto layer = currentLayer();

        return layer == editor::constants::ALL_LAYERS || layer == pLayer;
    }
    bool layerLocked(int pLayer) {
        if (notLoaded(LoadedType::EditorValid) || pLayer > editor::constants::MAX_LAYERS || pLayer < 0) {
            return false;
        }

        return layer()->isLayerLocked(pLayer);
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

    CCArray* objectArray(bool pCopy) {
        return loaded(LoadedType::Editor) ? (pCopy ? utils::array::copy(layer()->m_objects) : layer()->m_objects) : CCArray::create();
    }
    CCArray* objectsWithGroup(int pGroup, bool pCopy) {
        if (notLoaded(LoadedType::Editor)) {
            return CCArray::create();
        }
        
        if (auto ptr = layer()->m_groupDict->objectForKey(pGroup)) {
            return pCopy ? utils::array::copy(static_cast<CCArray*>(ptr)) : static_cast<CCArray*>(ptr);
        }
        else {
            return CCArray::create();
        }
    }
    GameObject* groupParent(int pGroup) {
        return loaded(LoadedType::Editor) ? layer()->getGroupParent(pGroup) : nullptr;
    }

    cocos2d::CCPoint snappedPos(cocos2d::CCPoint pPos, std::optional<int> pID, float pGridSize) {
        const auto offset = ui()->offsetForKey(pID.value_or(1));
        const auto pos = pPos - offset;
        const auto gridSize = pGridSize * (editor::object::size(pID.value_or(1)) / 30.0f);

        return CCPoint{
            (std::floor(pos.x / gridSize) + 0.5f) * gridSize,
            (std::floor(pos.y / gridSize) + 0.5f) * gridSize
        } + offset;
    }
    cocos2d::CCPoint snappedPos(GameObject* pObj, float pGridSize) {
        return snappedPos(
            pObj->getRealPosition(), editor::object::id(pObj), pGridSize
        );
    }

    void save() {
        if (notLoaded(LoadedType::Editor) || editor::isPlaytesting()) {
            return;
        }
        
        impl::getFakePauseLayer()->saveLevel();
    }

    void updateEditorTabButtons() {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }

        ui()->m_editButtonBar->reloadItems(
            GameManager::get()->getIntGameVariable(GameVar::EditorButtonsPerRow),
            GameManager::get()->getIntGameVariable(GameVar::EditorButtonRows)
        );
    }
}