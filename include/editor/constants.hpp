#pragma once

namespace nwo5::editor::constants {
    static constexpr float GRID_SIZE = 30.0f;
    static constexpr float GRID_SIZE_OBJECT = 10.0f;

    /// ok so apparently robtop just subtracts 90 from the position when making object strings cuz fuck u and
    /// doesnt use m_toolbarHeight or smth so (this took me like an hour of reverse engineering to figure out im kms)
    static constexpr cocos2d::CCPoint OBJECT_STRING_POSITION_OFFSET{0.0f, -90.0f};

    static constexpr int MAX_OBJECT_ID = 4539;
    static constexpr int MAX_GROUPS = 9999;
    static constexpr int MAX_LAYERS = 9999;
    static constexpr int ALL_LAYERS = -1;

    static constexpr float MIN_ZOOM = 0.1f;
    static constexpr float MAX_ZOOM = 4.0f;

    static constexpr float SLOW_SPEED = 251.16008f;
    static constexpr float NORMAL_SPEED = 311.5801f;
    static constexpr float FAST_SPEED = 387.42014f;
    static constexpr float FASTER_SPEED = 468.00015f;
    static constexpr float FASTEST_SPEED = 576.0002f;
    static constexpr float SLOW_SPEED_BPS = SLOW_SPEED / GRID_SIZE;
    static constexpr float NORMAL_SPEED_BPS = NORMAL_SPEED / GRID_SIZE;
    static constexpr float FAST_SPEED_BPS = FAST_SPEED / GRID_SIZE;
    static constexpr float FASTER_SPEED_BPS = FASTER_SPEED / GRID_SIZE;
    static constexpr float FASTEST_SPEED_BPS = FASTEST_SPEED / GRID_SIZE;

    static constexpr int BACKGROUND_COLOR = 1000;
    static constexpr int GROUND_COLOR = 1001;
    static constexpr int LINE_COLOR = 1002;
    static constexpr int LINE_3D_COLOR = 1003;
    static constexpr int OBJECT_COLOR = 1004;
    static constexpr int PLAYER_1_COLOR = 1005;
    static constexpr int PLAYER_2_COLOR = 1006;
    static constexpr int LIGHT_BACKGROUND_COLOR = 1007;
    static constexpr int GROUND_2_COLOR = 1009;
    static constexpr int BLACK_COLOR = 1010;
    static constexpr int WHITE_COLOR = 1011;
    static constexpr int LIGHTER_COLOR = 1012;
    static constexpr int MIDDLEGROUND_COLOR = 1013;
    static constexpr int MIDDLEGROUND_2_COLOR = 1014;

    static constexpr int P1_AREA_SPECIAL_TARGET = -1;
    static constexpr int P2_AREA_SPECIAL_TARGET = -2;
    static constexpr int CAMERA_AREA_SPECIAL_TARGET = -3;
    static constexpr int BOTTOM_LEFT_AREA_SPECIAL_TARGET = -4;
    static constexpr int CENTER_LEFT_AREA_SPECIAL_TARGET = -5;
    static constexpr int TOP_LEFT_AREA_SPECIAL_TARGET = -6;
    static constexpr int BOTTOM_CENTER_AREA_SPECIAL_TARGET = -7;
    static constexpr int TOP_CENTER_AREA_SPECIAL_TARGET = -8;
    static constexpr int BOTTOM_RIGHT_AREA_SPECIAL_TARGET = -9;
    static constexpr int CENTER_RIGHT_AREA_SPECIAL_TARGET = -10;
    static constexpr int TOP_RIGHT_AREA_SPECIAL_TARGET = -11;

    /// convert speed enum to units per seccond
    /// @returns units per second for speed
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