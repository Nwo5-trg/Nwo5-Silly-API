#pragma once

#include "setup-node.hpp"
#include "nodes.hpp"
#include "misc.hpp"
#include "color.hpp"
#include "easings.hpp"
#include "array.hpp"
#include "drawnode.hpp"

namespace nwo5::utils::prelude {
    namespace nutils = nwo5::utils;
    namespace array = nwo5::utils::array;

    using array::ArrayIndex;

    using nutils::enum_cast, nutils::color_cast;

    using nutils::ccMax, nutils::ccMin, nutils::ccAdd, 
    nutils::ccSub, nutils::ccMul, nutils::ccDiv;

    using nutils::EasingFunction;

    using nutils::SillyDrawNode;

    using nutils::SillyHSV;

    using nutils::CLEAR_COLOR;

    using nutils::GetChildQuery, nutils::GetChildQueryID, nutils::GetChildQueryIndex,
    nutils::GetChildQueryType;
}

namespace nwo5::utils::setup {
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
}