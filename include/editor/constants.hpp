#pragma once

namespace nwo5::editor::constants {
    constexpr float GRID_SIZE = 30.0f;
    constexpr float GRID_SIZE_OBJECT = 10.0f;

    /// ok so apparently robtop just subtracts 90 from the position when making object strings cuz fuck u and
    /// doesnt use m_toolbarHeight or smth so (this took me like an hour of reverse engineering to figure out im kms)
    constexpr cocos2d::CCPoint OBJECT_STRING_POSITION_OFFSET{0.0f, -90.0f};

    constexpr int MAX_GROUPS = 9999;
    constexpr int MAX_LAYERS = 9999;
    constexpr int ALL_LAYERS = -1;

    constexpr float MIN_ZOOM = 0.1f;
    constexpr float MAX_ZOOM = 4.0f;
}