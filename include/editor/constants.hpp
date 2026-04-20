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

    constexpr float SLOW_SPEED = 251.16008f;
    constexpr float NORMAL_SPEED = 311.5801f;
    constexpr float FAST_SPEED = 387.42014f;
    constexpr float FASTER_SPEED = 468.00015f;
    constexpr float FASTEST_SPEED = 576.0002f;
    constexpr float SLOW_SPEED_BPS = SLOW_SPEED / GRID_SIZE;
    constexpr float NORMAL_SPEED_BPS = NORMAL_SPEED / GRID_SIZE;
    constexpr float FAST_SPEED_BPS = FAST_SPEED / GRID_SIZE;
    constexpr float FASTER_SPEED_BPS = FASTER_SPEED / GRID_SIZE;
    constexpr float FASTEST_SPEED_BPS = FASTEST_SPEED / GRID_SIZE;

    constexpr int OBJECT_IDS = 4539;

    constexpr float toSpeed(Speed pSpeed) {
        switch (pSpeed) {
            case Speed::Normal: return NORMAL_SPEED;
            case Speed::Slow: return SLOW_SPEED;
            case Speed::Fast: return FAST_SPEED;
            case Speed::Faster: return FASTER_SPEED;
            case Speed::Fastest: return FASTEST_SPEED;
        }
    }
}