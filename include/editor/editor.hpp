#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    namespace impl {
        SILLY_API_DLL void createUndoObject(UndoCommand pCommand);
        SILLY_API_DLL void toggleMoveObject(bool pMove);
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
    SILLY_API_DLL bool loaded(LoadedType pType = LoadedType::Editor);
    /// same as !loaded()
    SILLY_API_DLL bool notLoaded(LoadedType pType = LoadedType::Editor);

    /// call pretty much every editor update function (e.g. updating ui buttons, obj info label)
    SILLY_API_DLL void update(bool pUpdateControls = true, bool pOtherwiseDeactivateControls = false);

    /// get editor soom
    /// @returns editor zoom
    SILLY_API_DLL float zoom();
    /// center of editor in objectlayer position
    /// @param pToolbar whether to account for toolbarheight
    /// @returns center
    SILLY_API_DLL cocos2d::CCPoint center(bool pToolbar = true);
    /// size of visible objectlayer
    /// @param pToolbar whether to account for toolbarheight
    /// @returns size
    SILLY_API_DLL cocos2d::CCSize size(bool pToolbar = true);
    
    /// move editor to position (objectlayer position)
    SILLY_API_DLL void move(cocos2d::CCPoint pPos);
    /// move camera to obj and optionally zoom out
    /// @param pObj object
    /// @param pZoomToFit zoom out to fit obj on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(GameObject* pObj, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param pObjs objects (gets center)
    /// @param pZoomToFit zoom out to fit objs on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(std::span<GameObject* const> pObjs, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param pObjs objects (gets center)
    /// @param pZoomToFit zoom out to fit objs on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(cocos2d::CCArray* pObjs, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());
    /// set editor zoom
    SILLY_API_DLL void setZoom(float pZoom);

    /// LevelEditorLayer::m_playbackMode == PlaybackMode::Playing
    SILLY_API_DLL bool isPlaytesting();
    /// LevelEditorLayer::m_playbackMode
    SILLY_API_DLL PlaybackMode playbackMode();

    /// activate rotation control
    /// @param pRefresh deactivate rotation control before activating it again
    SILLY_API_DLL void activateRotationControl(bool pRefresh = true);
    /// deactivate rotation control
    SILLY_API_DLL void deactivateRotationControl();
    /// activate scale control
    /// @param pXY show xy control instead of normal scale control
    /// @param pRefresh deactivate scale control before activating it again
    SILLY_API_DLL void activateScaleControl(bool pXY, bool pRefresh = true);
    /// deactivate scale control
    SILLY_API_DLL void deactivateScaleControl();
    /// activate transform control
    /// @param pRefresh deactivate transform control before activating it again
    SILLY_API_DLL void activateTransformControl(bool pRefresh = true);
    /// deactivate transform control
    SILLY_API_DLL void deactivateTransformControl();

    /// get current layer
    /// @returns current layer or editor::constants::ALL_LAYERS if editor not loaded
    SILLY_API_DLL int currentLayer();
    /// get if layer is currently selectable
    /// @param pLayer layer
    /// @param pIgnoreLocked if a layer is locked but otherwise selectable, still return true
    /// @returns if layer is currently selectable
    SILLY_API_DLL bool layerSelectable(int pLayer = currentLayer(), bool pIgnoreLocked = false);
    /// get if layer is locked
    /// @param pLayer
    /// @returns if layer is locked
    SILLY_API_DLL bool layerLocked(int pLayer = currentLayer());
    /// set current layer to pLayer
    SILLY_API_DLL void setLayer(int pLayer);
    SILLY_API_DLL void lockLayer(int pLayer, bool pLock);

    /// get all objects
    /// @param pCopy whether to copy obj array (why)
    /// @returns objs
    SILLY_API_DLL cocos2d::CCArray* objectArray(bool pCopy = false);
    /// get all objects with group
    /// @param pGroup group
    /// @param pCopy whether to copy obj array (why)
    /// @note will copy anyway (creating a new empty ccarray) if pGroup doesnt have a m_groupDict entry
    /// @returns objs
    SILLY_API_DLL cocos2d::CCArray* objectsWithGroup(int pGroup, bool pCopy = false);
    /// get group parent
    /// @returns group parent or returns nullptr if group has no group parent
    SILLY_API_DLL GameObject* groupParent(int pGroup);

    /// gets grid snapped pos, optionally using an id as an offset
    /// @param pGridSize grid size
    /// @returns pos of snapped position
    SILLY_API_DLL cocos2d::CCPoint snappedPos(cocos2d::CCPoint pPos, std::optional<int> pID = std::nullopt, float pGridSize = 30.0f);
    /// gets grid snapped pos of object
    /// @param pGridSize grid size object is snapped to
    /// @returns pos of object snapped to pGridSize
    SILLY_API_DLL cocos2d::CCPoint snappedPos(GameObject* pObj, float pGridSize = 30.0f);

    /// saves current level
    /// @note does nothing if playtesting
    SILLY_API_DLL void save();

    /// reload editbuttonbar
    SILLY_API_DLL void updateEditorTabButtons();
}