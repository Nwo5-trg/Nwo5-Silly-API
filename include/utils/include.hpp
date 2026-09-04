#pragma once

#include "nodes.hpp"
#include "misc.hpp"
#include "color.hpp"
#include "color-type.hpp"
#include "easings.hpp"
#include "array.hpp"
#include "drawnode.hpp"

#include <ranges>

namespace nwo5::utils::prelude {
    namespace misc = nwo5::utils;
    namespace array = nwo5::utils::array;

    using array::ArrayIndex;

    using misc::enum_cast, misc::color_cast;

    using misc::ccMax, misc::ccMin, misc::ccAdd, 
    misc::ccSub, misc::ccMul, misc::ccDiv;

    using misc::EasingFunction;

    using misc::SillyDrawNode;

    using misc::SillyHSV;

    using misc::CLEAR_COLOR;

    using misc::Query;

    using misc::Col;
}