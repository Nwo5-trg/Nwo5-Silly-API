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

            static void onModify(auto& self) {
                (void)self.setHookPriority("EditorUI::init", Priority::First);
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

        void createUndoObject(UndoCommand command) {
            ui()->createUndoObject(command, false);
        }
        void toggleMoveObject(bool move) {
            s_shouldMoveObject = move;
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

    bool loaded(LoadedType type) {
        switch (type) {
            case LoadedType::Editor: return layer() && !layer()->m_initializing;
            case LoadedType::EditorValid: return layer();
            case LoadedType::UI: return layer() && impl::s_editorUIEarlyPtr;
            case LoadedType::UIValid: return ui();
        }
    }
    bool notLoaded(LoadedType type) {
        return !loaded(type);
    }

    void update(bool updateControls, bool otherwiseDeactivateControls) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        auto editor = ui();

        editor->updateButtons();
        editor->updateObjectInfoLabel();
        editor->updateGridNodeSize();
        editor->updateStickyControls();
        editor->m_editorLayer->m_drawGridLayer->m_updateTimeMarkers = true;
        
        if (updateControls) {
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
        else if (otherwiseDeactivateControls) {
            editor->deactivateRotationControl();
            editor->deactivateScaleControl();
            editor->deactivateTransformControl();
        }
    }

    float zoom() {
        return layer() ? layer()->m_objectLayer->getScale() : 0.0f;
    }
    CCPoint center(bool toolbar) {
        if (notLoaded(LoadedType::UI)) {
            return CCPointZero;
        }
        
        return CCPoint{
            (CCDirector::get()->getWinSize() / 2) - CCPoint{
                layer()->m_objectLayer->getPositionX(), 
                layer()->m_objectLayer->getPositionY() - (toolbar ? (ui()->m_toolbarHeight / 2) : 0.0f)
            }
        } / zoom();
    }
    CCSize size(bool toolbar) {
        if (notLoaded(LoadedType::UI)) {
            return CCSizeZero;
        }
        
        return CCSize{
            CCDirector::get()->getWinSize().width,
            CCDirector::get()->getWinSize().height - (toolbar ? ui()->m_toolbarHeight : 0.0f)
        } / zoom();
    }

    void move(cocos2d::CCPoint pos) {
        if (notLoaded(LoadedType::UIValid)) {
            return;
        }

        const float scale = layer()->m_objectLayer->getScale();
        const auto currentPos = layer()->m_objectLayer->getPosition();

        ui()->moveGamelayer(
            -pos * scale + CCDirector::get()->getWinSize() / 2 - currentPos
        );
    }
    void moveTo(GameObject* obj, bool zoomToFit, float zoomBuffer, float minimumZoom, float maximumZoom) {
        const auto bounds = editor::object::bounds(obj, true);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                minimumZoom, maximumZoom
            )
        );
    }
    void moveTo(std::span<GameObject* const> objs, bool zoomToFit, float zoomBuffer, float minimumZoom, float maximumZoom) {
        const auto bounds = editor::object::bounds(objs, true);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                minimumZoom, maximumZoom
            )
        );
    }
    void moveTo(CCArray* objs, bool zoomToFit, float zoomBuffer, float minimumZoom, float maximumZoom) {
        const auto bounds = editor::object::bounds(objs);

        editor::move(bounds.origin + bounds.size / 2);
        editor::setZoom(
            std::clamp(
                (CCDirector::get()->getWinSize().width / bounds.size.width) / 1.5f, 
                minimumZoom, maximumZoom
            )
        );
    }

    void setZoom(float zoom) {
        setZoom(zoom, CCDirector::get()->getWinSize() / 2);
    }
    void setZoom(float zoom, CCPoint center) {
        if (notLoaded(LoadedType::UIValid)) {
            return;
        }

        if (!zoom) {
            return;
        }

        ui()->updateZoom(zoom, center);
    }

    bool isPlaytesting() {
        return layer() ? layer()->m_playbackMode == PlaybackMode::Playing : false;
    }
    PlaybackMode playbackMode() {
        return layer() ? layer()->m_playbackMode : PlaybackMode::Not;
    }

    void activateRotationControl(bool refresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_rotationControl) {
            return;
        }

        if (refresh) {
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
    void activateScaleControl(bool xY, bool refresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_scaleControl) {
            return;
        }

        if (refresh) {
            deactivateScaleControl();
        }
        else if (ui()->m_scaleControl->isVisible()) {
            return;
        }

        ui()->activateScaleControl(nwo5::utils::CCTag::create(xY ? 30 : 29));
    }
    void deactivateScaleControl() {
        if (loaded(LoadedType::UI) && ui()->m_scaleControl && ui()->m_scaleControl->isVisible()) {
            ui()->deactivateScaleControl();
        }
    }
    void activateTransformControl(bool refresh) {
        if (notLoaded(LoadedType::UI)) {
            return;
        }
        
        if (!ui()->m_transformControl) {
            return;
        }

        if (refresh) {
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
    bool layerSelectable(int layer, bool ignoreLocked) {
        if (notLoaded(LoadedType::EditorValid) || layer > editor::constants::MAX_LAYERS || layer < 0 || (!ignoreLocked && layerLocked(layer))) {
            return false;
        }
        
        const auto cl = currentLayer();

        return cl == editor::constants::ALL_LAYERS || layer == cl;
    }
    bool layerLocked(int layer) {
        if (notLoaded(LoadedType::EditorValid) || layer > editor::constants::MAX_LAYERS || layer < 0) {
            return false;
        }

        return editor::layer()->isLayerLocked(layer);
    }
    void setLayer(int layer) {
        if (notLoaded(LoadedType::UI) || layer > editor::constants::MAX_LAYERS || layer < editor::constants::ALL_LAYERS) {
            return;
        }

        editor::layer()->m_currentLayer = layer;
        // its fucking crazy to me that robtop calls layers "groups" internally :sob:
        ui()->updateGroupIDLabel();
    }
    void lockLayer(int layer, bool lock) {
        if (notLoaded(LoadedType::UI) || layer > editor::constants::MAX_LAYERS || layer < editor::constants::ALL_LAYERS || layerLocked(layer) == lock) {
            return;
        }

        const auto editorLayer = currentLayer();
        const auto lockingEnabled = editor::layer()->m_layerLockingEnabled;

        editor::layer()->m_currentLayer = layer;
        editor::layer()->m_layerLockingEnabled = true;
        
        // i dont wanna re this function it looks like a bunch of math and im scared
        editor::layer()->toggleLockActiveLayer();
        ui()->updateGroupIDLabel();

        editor::layer()->m_currentLayer = editorLayer;
        editor::layer()->m_layerLockingEnabled = lockingEnabled;
    }

    CCArray* objectArray(bool copy) {
        return loaded(LoadedType::Editor) ? (copy ? utils::array::copy(layer()->m_objects) : layer()->m_objects) : CCArray::create();
    }
    CCArray* objectsWithGroup(int group, bool copy) {
        if (notLoaded(LoadedType::Editor)) {
            return CCArray::create();
        }
        
        if (auto ptr = layer()->m_groupDict->objectForKey(group)) {
            return copy ? utils::array::copy(static_cast<CCArray*>(ptr)) : static_cast<CCArray*>(ptr);
        }
        else {
            return CCArray::create();
        }
    }
    GameObject* groupParent(int group) {
        if (notLoaded(LoadedType::Editor)) {
            return nullptr;
        }

        if (auto parents = static_cast<cocos2d::CCArray*>(layer()->m_parentGroupsDict->objectForKey(group)); parents->count() != 0) {
            return static_cast<GameObject*>(parents->firstObject());
        }
        
        return nullptr;
    }

    cocos2d::CCPoint snappedPos(cocos2d::CCPoint pos, std::optional<int> id, float gridSize) {
        const auto offset = ui()->offsetForKey(id.value_or(1));
        pos -= offset;
        gridSize *= (editor::object::size(id.value_or(1)) / 30.0f);

        return CCPoint{
            (std::floor(pos.x / gridSize) + 0.5f) * gridSize,
            (std::floor(pos.y / gridSize) + 0.5f) * gridSize
        } + offset;
    }
    cocos2d::CCPoint snappedPos(GameObject* obj, float gridSize) {
        return snappedPos(
            obj->getRealPosition(), editor::object::id(obj), gridSize
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