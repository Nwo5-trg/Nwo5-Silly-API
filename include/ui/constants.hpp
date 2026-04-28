#pragma once

#include "../export.hpp"

namespace nwo5::ui {
    constexpr cocos2d::CCPoint TOP_RIGHT_ANCHOR{1.0f, 1.0f};
    constexpr cocos2d::CCPoint TOP_CENTER_ANCHOR{0.5f, 1.0f};
    constexpr cocos2d::CCPoint TOP_LEFT_ANCHOR{0.0f, 1.0f};
    constexpr cocos2d::CCPoint LEFT_CENTER_ANCHOR{0.0f, 0.5f};
    constexpr cocos2d::CCPoint BOTTOM_LEFT_ANCHOR{0.0f, 0.0f};
    constexpr cocos2d::CCPoint BOTTOM_CENTER_ANCHOR{0.5f, 0.0f};
    constexpr cocos2d::CCPoint BOTTOM_RIGHT_ANCHOR{1.0f, 0.0f};
    constexpr cocos2d::CCPoint RIGHT_CENTER_ANCHOR{1.0f, 0.5f};
    constexpr cocos2d::CCPoint CENTER_ANCHOR{0.5f, 0.5f};

    constexpr auto DEFAULT_TEXT_INPUT_HEIGHT = 30.0f;
    using TextInputCallback = geode::Function<void(const std::string&)>;

    struct Font {
        static constexpr auto BigFont = "bigFont.fnt";
        static constexpr auto Default = BigFont;
        static constexpr auto ChatFont = "chatFont.fnt";
        static constexpr auto Chat = ChatFont;
        static constexpr auto GoldFont = "goldFont.fnt";
        static constexpr auto Gold = GoldFont;
    };
}