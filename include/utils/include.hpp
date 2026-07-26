#pragma once

#include "nodes.hpp"
#include "misc.hpp"
#include "color.hpp"
#include "easings.hpp"
#include "array.hpp"
#include "drawnode.hpp"

#include <ranges>

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