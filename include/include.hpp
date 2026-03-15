#pragma once

#include "settings/include.hpp"
#include "editor/include.hpp"
#include "utils/include.hpp"

namespace nwo5 {
    namespace syntax {
        using editor::AUTO_CENTER;

        using nwo5::utils::SetNodePosition, nwo5::utils::SetNodePositionX, nwo5::utils::SetNodePositionY, 
        nwo5::utils::ChangeNodePosition, nwo5::utils::ChangeNodePositionX, nwo5::utils::ChangeNodePositionY, 
        nwo5::utils::SetNodeRotation, nwo5::utils::ChangeNodeRotation, nwo5::utils::SetNodeScale, nwo5::utils::SetNodeScaleX, 
        nwo5::utils::SetNodeScaleY, nwo5::utils::ChangeNodeScale, nwo5::utils::ChangeNodeScaleX, nwo5::utils::ChangeNodeScaleY, 
        nwo5::utils::SetNodeScaleWithSize, nwo5::utils::SetNodeScaleWithWidth, nwo5::utils::SetNodeScaleWithHeight, 
        nwo5::utils::LimitNodeScaleWithSize, nwo5::utils::LimitNodeScaleWithWidth, nwo5::utils::LimitNodeScaleWithHeight,
        nwo5::utils::SetNodeSize, nwo5::utils::SetNodeWidth, nwo5::utils::SetNodeHeight, nwo5::utils::ChangeNodeSize, 
        nwo5::utils::ChangeNodeWidth, nwo5::utils::ChangeNodeHeight, nwo5::utils::SetNodeAnchor,  nwo5::utils::SetNodeChildren, 
        nwo5::utils::SetNodeParent, nwo5::utils::SetNodeID, nwo5::utils::SetNodeTag, nwo5::utils::SetNodeOrder, nwo5::utils::SetNodeVisibility, 
        nwo5::utils::SetNodeInvisible, nwo5::utils::SetNodeColor, nwo5::utils::SetNodeOpacity;

        using nwo5::utils::GetChildQuery;

        using nwo5::utils::TextInputCallback;

        using nwo5::utils::DEFAULT_TEXT_INPUT_HEIGHT;
        
        using nwo5::utils::TOP_RIGHT_ANCHOR, nwo5::utils::TOP_CENTER_ANCHOR, nwo5::utils::TOP_LEFT_ANCHOR,
        nwo5::utils::LEFT_CENTER_ANCHOR, nwo5::utils::BOTTOM_LEFT_ANCHOR, nwo5::utils::BOTTOM_CENTER_ANCHOR,
        nwo5::utils::BOTTOM_RIGHT_ANCHOR, nwo5::utils::RIGHT_CENTER_ANCHOR, nwo5::utils::CENTER_ANCHOR;
    }
    
    namespace prelude {
        using namespace nwo5::settings::prelude;
        using namespace nwo5::editor::prelude;
        
        using namespace nwo5::syntax;
    }
};