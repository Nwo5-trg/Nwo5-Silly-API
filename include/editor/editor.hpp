#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    namespace impl {
        SILLY_API_DLL void createUndoObject(UndoCommand command);
        SILLY_API_DLL void toggleMoveObject(bool move);
        SILLY_API_DLL EditorUI* getEditorUI();
    }

    /// get editorui and optionally reinterpret_cast it
    template<typename ImplT = EditorUI, typename T = std::remove_pointer_t<ImplT>>
    auto ui() {
        return reinterpret_cast<T*>(impl::getEditorUI());
    };
    /// get leveleditorlayer and optionally reinterpret_cast it
    template<typename ImplT = LevelEditorLayer, typename T = std::remove_pointer_t<ImplT>>
    auto layer() {
        static const auto manager = GameManager::get();
        return reinterpret_cast<T*>(manager->m_levelEditorLayer);
    }

    enum class LoadedType {
        /// editorlayer initialized
        Editor,
        /// editorlayer (valid right before init starts)
        EditorValid,
        /// editorui initialized
        UI,
        /// editorui (valid right before init starts)
        UIValid
    };
    
    /// check LoadedType docs
    SILLY_API_DLL bool loaded(LoadedType type = LoadedType::Editor);
    /// same as !loaded()
    SILLY_API_DLL bool notLoaded(LoadedType type = LoadedType::Editor);

    /// call pretty much every editor update function (e.g. updating ui buttons, obj info label)
    SILLY_API_DLL void update(bool updateControls = true, bool otherwiseDeactivateControls = false);

    /// get editor soom
    /// @returns editor zoom
    SILLY_API_DLL float zoom();
    /// center of editor in objectlayer position
    /// @param toolbar whether to account for toolbarheight
    /// @returns center
    SILLY_API_DLL cocos2d::CCPoint center(bool toolbar = true);
    /// size of visible objectlayer
    /// @param toolbar whether to account for toolbarheight
    /// @returns size
    SILLY_API_DLL cocos2d::CCSize size(bool toolbar = true);
    
    /// move editor to position (objectlayer position)
    SILLY_API_DLL void move(cocos2d::CCPoint pos);
    /// move camera to obj and optionally zoom out
    /// @param obj object
    /// @param zoomToFit zoom out to fit obj on screen
    /// @param zoomBuffer *divide* zoom by this
    /// @param minimumZoom clamps zoom to this
    /// @param maximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(GameObject* obj, bool zoomToFit = true, float zoomBuffer = 1.5f, float minimumZoom = 0.0f, float maximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param objs objects (gets center)
    /// @param zoomToFit zoom out to fit objs on screen
    /// @param zoomBuffer *divide* zoom by this
    /// @param minimumZoom clamps zoom to this
    /// @param maximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(std::span<GameObject* const> objs, bool zoomToFit = true, float zoomBuffer = 1.5f, float minimumZoom = 0.0f, float maximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param objs objects (gets center)
    /// @param zoomToFit zoom out to fit objs on screen
    /// @param zoomBuffer *divide* zoom by this
    /// @param minimumZoom clamps zoom to this
    /// @param maximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(cocos2d::CCArray* objs, bool zoomToFit = true, float zoomBuffer = 1.5f, float minimumZoom = 0.0f, float maximumZoom = editor::zoom());
    /// set editor zoom
    SILLY_API_DLL void setZoom(float zoom);
    /// set editor zoom
    SILLY_API_DLL void setZoom(float zoom, cocos2d::CCPoint center);

    /// LevelEditorLayer::m_playbackMode == PlaybackMode::Playing
    SILLY_API_DLL bool isPlaytesting();
    /// LevelEditorLayer::m_playbackMode
    SILLY_API_DLL PlaybackMode playbackMode();

    /// activate rotation control
    /// @param refresh deactivate rotation control before activating it again
    SILLY_API_DLL void activateRotationControl(bool refresh = true);
    /// deactivate rotation control
    SILLY_API_DLL void deactivateRotationControl();
    /// activate scale control
    /// @param xY show xy control instead of normal scale control
    /// @param refresh deactivate scale control before activating it again
    SILLY_API_DLL void activateScaleControl(bool xY, bool refresh = true);
    /// deactivate scale control
    SILLY_API_DLL void deactivateScaleControl();
    /// activate transform control
    /// @param refresh deactivate transform control before activating it again
    SILLY_API_DLL void activateTransformControl(bool refresh = true);
    /// deactivate transform control
    SILLY_API_DLL void deactivateTransformControl();

    /// get current layer
    /// @returns current layer or editor::constants::ALL_LAYERS if editor not loaded
    SILLY_API_DLL int currentLayer();
    /// get if layer is currently selectable
    /// @param layer layer
    /// @param ignoreLocked if a layer is locked but otherwise selectable, still return true
    /// @returns if layer is currently selectable
    SILLY_API_DLL bool layerSelectable(int layer = currentLayer(), bool ignoreLocked = false);
    /// get if layer is locked
    /// @param layer
    /// @returns if layer is locked
    SILLY_API_DLL bool layerLocked(int layer = currentLayer());
    /// set current layer to layer
    SILLY_API_DLL void setLayer(int layer);
    SILLY_API_DLL void lockLayer(int layer, bool lock);

    /// get all objects
    /// @param copy whether to copy obj array (why)
    /// @returns objs
    SILLY_API_DLL cocos2d::CCArray* objectArray(bool copy = false);
    /// get all objects with group
    /// @param group group
    /// @param copy whether to copy obj array (why)
    /// @note will copy anyway (creating a new empty ccarray) if group doesnt have a m_groupDict entry
    /// @returns objs
    SILLY_API_DLL cocos2d::CCArray* objectsWithGroup(int group, bool copy = false);
    /// get group parent
    /// @returns group parent or returns nullptr if group has no group parent
    SILLY_API_DLL GameObject* groupParent(int group);

    /// gets grid snapped pos, optionally using an id as an offset
    /// @param gridSize grid size
    /// @returns pos of snapped position
    SILLY_API_DLL cocos2d::CCPoint snappedPos(cocos2d::CCPoint pos, std::optional<int> id = std::nullopt, float gridSize = 30.0f);
    /// gets grid snapped pos of object
    /// @param gridSize grid size object is snapped to
    /// @returns pos of object snapped to gridSize
    SILLY_API_DLL cocos2d::CCPoint snappedPos(GameObject* obj, float gridSize = 30.0f);

    /// saves current level
    /// @note does nothing if playtesting
    SILLY_API_DLL void save();

    /// reload editbuttonbar
    SILLY_API_DLL void updateEditorTabButtons();
}