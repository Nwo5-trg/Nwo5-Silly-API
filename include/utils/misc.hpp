#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    /// count how many instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 3 will be outputed
    SILLY_API_DLL size_t stringCount(std::string_view string, std::string_view substr);
    /// count how many *independant* instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 2 will be outputed
    SILLY_API_DLL size_t stringCountIndependant(std::string_view string, std::string_view substr);
    /// the geode util
    SILLY_API_DLL size_t stringCount(std::string_view string, char substr);

    /// ccmenuitemtoggler triggers callback before its actually toggled so
    SILLY_API_DLL bool isToggled(cocos2d::CCObject* toggler);
    /// geodes toggle with callback sets m_toggled incorrectly whcih causes issues with some callbacks, this fixes that
    SILLY_API_DLL void toggleWithCallback(cocos2d::CCObject* toggler, bool on);

    /// set your label to this scale or not idk fuck you
    /// @param font 0, is default, 1-59 are editor fonts, 60 is chat font, 61 is gold font
    /// @todo make this an enum
    SILLY_API_DLL float getFontScaling(int font);
    /// texture to make ur cclabelbmfonts out of or smth
    /// @todo smth smth optimize cuz this is slow asf
    SILLY_API_DLL std::string getFontString(int font);

    /// ccobject dummy, useful for calling callbacks that require their sender to have a tag
    class SILLY_API_DLL CCTag final : public cocos2d::CCObject {
    public:
        static CCTag* create(int tag = cocos2d::kCCNodeTagInvalid);
    };

    template<typename T>
    T random(T min, T max) {
        return geode::utils::random::generate(min, max);
    }
    template<typename T>
    requires std::is_integral_v<T>
    T random(T min, T max) {
        // cant exactly cahnge the random generator to also work for int max or wtv but good enough
        return geode::utils::random::generate(min, std::min(max, std::numeric_limits<T>::max() - static_cast<T>(1)) + static_cast<T>(1));
    }

    template<typename T>
    auto numToString(T num, size_t precision = 4) {
        return geode::utils::numToString(num, precision);
    }
    /// opinionated numtostring
    /// trims trailing 0s
    /// zero precision acts as rounding
    template<typename T>
    requires std::is_floating_point_v<T>
    auto numToString(T num, size_t precision = 4) {
        if (!precision) {
            return std::to_string(static_cast<long>(std::round(num)));
        }
        
        auto str = geode::utils::numToString(num, precision);
        
        if (str.find('.') != std::string::npos) {
            if (const auto end = str.find_last_not_of('0'); end != std::string::npos) {
                str.erase(end + 1);
            }

            if (str.ends_with('.')) {
                str.pop_back();
            }
        }

        return str;
    }

    template<typename Callback>
    void setupKeybind(cocos2d::CCNode* node, std::string keybind, Callback&& callback, int priority = geode::Priority::Normal) {
        // no string_view 3:
        node->addEventListener(geode::KeybindSettingPressedEventV3(geode::Mod::get(), std::move(keybind)), std::forward<Callback>(callback), priority);
    }

    template<typename T>
    requires std::same_as<T, geode::KeyboardInputData>
    auto dataInfo(const T& data) {
        struct {
            const T& data;

            bool down() const {
                return data.action != geode::KeyboardInputData::Action::Release;
            }
            bool repeat() const {
                return data.action == geode::KeyboardInputData::Action::Repeat;
            }
        } wrapper{data};
        
        return wrapper;
    }
    template<typename T>
    requires std::same_as<T, geode::MouseInputData>
    auto dataInfo(const T& data) {
        struct {
            const T& data;

            bool down() const {
                return data.action == geode::MouseInputData::Action::Press;
            }

            bool leftButton() const {
                return data.button == geode::MouseInputData::Button::Left;
            }
            bool rightButton() const {
                return data.button == geode::MouseInputData::Button::Right;
            }
            bool middleButton() const {
                return data.button == geode::MouseInputData::Button::Middle;
            }
        } wrapper{data};
        
        return wrapper;
    }

    /// convert between numbers and enums
    /// @note i dont guarantee safty i js guarantee the compiler stfu
    template<typename After, typename Before>
    requires (std::is_arithmetic_v<After> || std::is_scoped_enum_v<After>) && (std::is_arithmetic_v<Before> || std::is_scoped_enum_v<Before>)
    constexpr After enum_cast(Before val) {
        if constexpr (std::is_scoped_enum_v<Before>) {
            return static_cast<After>(std::to_underlying(val));
        }
        else {
            return static_cast<After>(val);
        }
    }

    SILLY_API_DLL cocos2d::CCRect rectOverlap(const cocos2d::CCRect& a, const cocos2d::CCRect& b);

    // very unnecessary template shenanigans but fun :33333

    template<typename T>
    concept IsCCVec2 = requires (T vec2) { // ccvertex/ccpoint exist
        requires std::same_as<decltype(vec2.x), decltype(vec2.y)>;
    };

    template<IsCCVec2 T>
    constexpr auto ccMax(const T& vec2) noexcept {
        return (vec2.x > vec2.y) ? vec2.x : vec2.y;
    }
    constexpr auto ccMax(const cocos2d::CCSize& size) noexcept {
        return (size.width > size.height) ? size.width : size.height;
    }
    template<IsCCVec2 T>
    constexpr auto ccMin(const T& vec2) noexcept {
        return (vec2.x < vec2.y) ? vec2.x : vec2.y;
    }
    constexpr auto ccMin(const cocos2d::CCSize& size) noexcept {
        return (size.width < size.height) ? size.width : size.height;
    }
    template<IsCCVec2 T>
    constexpr auto ccAdd(const T& a, const T& b) noexcept {
        return T{a.x + b.x, a.y + b.y};
    }
    constexpr auto ccAdd(const cocos2d::CCSize& a, const cocos2d::CCSize& b) noexcept {
        return cocos2d::CCSize{a.width + b.width, a.height + b.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccAdd(const T& a, const decltype(T::x)& s) noexcept {
        return T{a.x + s, a.y + s};
    }
    constexpr auto ccAdd(const cocos2d::CCSize& a, const decltype(cocos2d::CCSize::width)& s) noexcept {
        return cocos2d::CCSize{a.width + s, a.height + s};
    }
    template<IsCCVec2 T>
    constexpr auto ccSub(const T& a, const T& b) noexcept {
        return T{a.x - b.x, a.y - b.y};
    }
    constexpr auto ccSub(const cocos2d::CCSize& a, const cocos2d::CCSize& b) noexcept {
        return cocos2d::CCSize{a.width - b.width, a.height - b.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccSub(const T& a, const decltype(T::x)& s) noexcept {
        return T{a.x - s, a.y - s};
    }
    constexpr auto ccSub(const cocos2d::CCSize& a, const decltype(cocos2d::CCSize::width)& s) noexcept {
        return cocos2d::CCSize{a.width - s, a.height - s};
    }
    template<IsCCVec2 T>
    constexpr auto ccMul(const T& a, const T& b) noexcept {
        return T{a.x * b.x, a.y * b.y};
    }
    constexpr auto ccMul(const cocos2d::CCSize& a, const cocos2d::CCSize& b) noexcept {
        return cocos2d::CCSize{a.width * b.width, a.height * b.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccMul(const T& a, const decltype(T::x)& s) noexcept {
        return T{a.x * s, a.y * s};
    }
    constexpr auto ccMul(const cocos2d::CCSize& a, const decltype(cocos2d::CCSize::width)& s) noexcept {
        return cocos2d::CCSize{a.width * s, a.height * s};
    }
    template<IsCCVec2 T>
    constexpr auto ccDiv(const T& a, const T& b) noexcept {
        return T{a.x / b.x, a.y / b.y};
    }
    constexpr auto ccDiv(const cocos2d::CCSize& a, const cocos2d::CCSize& b) noexcept {
        return cocos2d::CCSize{a.width / b.width, a.height / b.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccDiv(const T& a, const decltype(T::x)& s) noexcept {
        return T{a.x / s, a.y / s};
    }
    constexpr auto ccDiv(const cocos2d::CCSize& a, const decltype(cocos2d::CCSize::width)& s) noexcept {
        return cocos2d::CCSize{a.width / s, a.height / s};
    }
}