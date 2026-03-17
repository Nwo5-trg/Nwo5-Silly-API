#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    SILLY_API_DLL EditorUI* ui();
    SILLY_API_DLL LevelEditorLayer* layer();
    
    SILLY_API_DLL bool loaded();

    SILLY_API_DLL void update(bool pUpdateControls = true, bool pOtherwiseDeactivateControls = false);

    SILLY_API_DLL float zoom();
    SILLY_API_DLL cocos2d::CCPoint center();

    SILLY_API_DLL void activateRotationControl(bool pRefresh = true);
    SILLY_API_DLL void activateScaleControl(bool pXY, bool pRefresh = true);
    SILLY_API_DLL void activateTransformControl(bool pRefresh = true);

    SILLY_API_DLL int currentLayer();
    SILLY_API_DLL bool layerSelectable(int pLayer, bool pIgnoreLocked = false);
    SILLY_API_DLL bool layerLocked(int pLayer);
    SILLY_API_DLL void setLayer(int pLayer);
    SILLY_API_DLL void lockLayer(int pLayer = currentLayer());

    namespace impl {
        SILLY_API_DLL int nextFreeGroupFast(int pOffset = 1);
    }
    /// @param pOffset search starts from this gid, clamped from 1-9999
    /// @note only accounts for target gid and center gid rn, ill do like sequence/advrand checks and stuff l8r
    /// @returns next free gid or 0 if all 9999 groups are used
    SILLY_API_DLL int nextFreeGroup(int pOffset = 1, bool pCheckTargetGroups = false);

    constexpr cocos2d::CCPoint AUTO_CENTER{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    namespace impl {
        SILLY_API_DLL void createUndoObject(UndoCommand pCommand);
    }
}