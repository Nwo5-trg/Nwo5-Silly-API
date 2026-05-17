#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    /// count how many instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 3 will be outputed
    SILLY_API_DLL size_t stringCount(std::string_view pString, std::string_view pSubstr);
    /// count how many *independant* instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 2 will be outputed
    SILLY_API_DLL size_t stringCountIndependant(std::string_view pString, std::string_view pSubstr);
    /// the geode util
    SILLY_API_DLL size_t stringCount(std::string_view pString, char pSubstr);

    /// ccmenuitemtoggler triggers callback before its actually toggled so
    SILLY_API_DLL bool isToggled(cocos2d::CCObject* pToggler);
    /// geodes toggle with callback sets m_toggled incorrectly whcih causes issues with some callbacks, this fixes that
    SILLY_API_DLL void toggleWithCallback(cocos2d::CCObject* pToggler, bool pOn);

    /// ccobject dummy, useful for calling callbacks that require their sender to have a tag
    class SILLY_API_DLL CCTag final : public cocos2d::CCObject {
    public:
        static CCTag* create(int pTag = cocos2d::kCCNodeTagInvalid);
    };

    template<typename T>
    T random(T pMin, T pMax) {
        return geode::utils::random::generate(pMin, pMax);
    }
    template<typename T>
    requires std::is_integral_v<T>
    T random(T pMin, T pMax) {
        // cant exactly cahnge the random generator to also work for int max or wtv but good enough
        return geode::utils::random::generate(pMin, std::min(pMax, std::numeric_limits<T>::max() - static_cast<T>(1)) + static_cast<T>(1));
    }

    template<typename T>
    auto numToString(T pNum, size_t pPrecision = 4) {
        return geode::utils::numToString(pNum, pPrecision);
    }
    template<typename T>
    requires std::is_floating_point_v<T>
    auto numToString(T pNum, size_t pPrecision = 4) {
        if (!pPrecision) {
            return std::to_string(static_cast<int>(std::round(pNum)));
        }
        
        auto str = geode::utils::numToString(pNum, pPrecision);
        
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
    void setupKeybind(cocos2d::CCNode* pNode, std::string pKeybind, Callback&& pCallback) {
        // no string_view 3:
        pNode->addEventListener(geode::KeybindSettingPressedEventV3(geode::Mod::get(), std::move(pKeybind)), std::forward<Callback>(pCallback));
    }

    /// convert between numbers and enums
    /// @note i dont guarantee safty i js guarantee the compiler stfu
    template<typename After, typename Before>
    requires (std::is_arithmetic_v<After> || std::is_scoped_enum_v<After>) && (std::is_arithmetic_v<Before> || std::is_scoped_enum_v<Before>)
    After enum_cast(Before pVal) {
        if constexpr (std::is_scoped_enum_v<Before>) {
            return static_cast<After>(std::to_underlying(pVal));
        }
        else {
            return static_cast<After>(pVal);
        }
    }

    // very unnecessary template shenanigans but fun :33333

    template<typename T>
    concept IsCCVec2 = requires (T pVec2) { // ccvertex/ccpoint exist
        requires std::same_as<decltype(pVec2.x), decltype(pVec2.y)>;
    };

    template<IsCCVec2 T>
    constexpr auto ccMax(const T& pVec2) noexcept {
        return (pVec2.x > pVec2.y) ? pVec2.x : pVec2.y;
    }
    constexpr auto ccMax(const cocos2d::CCSize& pSize) noexcept {
        return (pSize.width > pSize.height) ? pSize.width : pSize.height;
    }
    template<IsCCVec2 T>
    constexpr auto ccMin(const T& pVec2) noexcept {
        return (pVec2.x < pVec2.y) ? pVec2.x : pVec2.y;
    }
    constexpr auto ccMin(const cocos2d::CCSize& pSize) noexcept {
        return (pSize.width < pSize.height) ? pSize.width : pSize.height;
    }
    template<IsCCVec2 T>
    constexpr auto ccAdd(const T& pA, const T& pB) noexcept {
        return T{pA.x + pB.x, pA.y + pB.y};
    }
    constexpr auto ccAdd(const cocos2d::CCSize& pA, const cocos2d::CCSize& pB) noexcept {
        return cocos2d::CCSize{pA.width + pB.width, pA.height + pB.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccAdd(const T& pA, const decltype(T::x)& pS) noexcept {
        return T{pA.x + pS, pA.y + pS};
    }
    constexpr auto ccAdd(const cocos2d::CCSize& pA, const decltype(cocos2d::CCSize::width)& pS) noexcept {
        return cocos2d::CCSize{pA.width + pS, pA.height + pS};
    }
    template<IsCCVec2 T>
    constexpr auto ccSub(const T& pA, const T& pB) noexcept {
        return T{pA.x - pB.x, pA.y - pB.y};
    }
    constexpr auto ccSub(const cocos2d::CCSize& pA, const cocos2d::CCSize& pB) noexcept {
        return cocos2d::CCSize{pA.width - pB.width, pA.height - pB.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccSub(const T& pA, const decltype(T::x)& pS) noexcept {
        return T{pA.x - pS, pA.y - pS};
    }
    constexpr auto ccSub(const cocos2d::CCSize& pA, const decltype(cocos2d::CCSize::width)& pS) noexcept {
        return cocos2d::CCSize{pA.width - pS, pA.height - pS};
    }
    template<IsCCVec2 T>
    constexpr auto ccMul(const T& pA, const T& pB) noexcept {
        return T{pA.x * pB.x, pA.y * pB.y};
    }
    constexpr auto ccMul(const cocos2d::CCSize& pA, const cocos2d::CCSize& pB) noexcept {
        return cocos2d::CCSize{pA.width * pB.width, pA.height * pB.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccMul(const T& pA, const decltype(T::x)& pS) noexcept {
        return T{pA.x * pS, pA.y * pS};
    }
    constexpr auto ccMul(const cocos2d::CCSize& pA, const decltype(cocos2d::CCSize::width)& pS) noexcept {
        return cocos2d::CCSize{pA.width * pS, pA.height * pS};
    }
    template<IsCCVec2 T>
    constexpr auto ccDiv(const T& pA, const T& pB) noexcept {
        return T{pA.x / pB.x, pA.y / pB.y};
    }
    constexpr auto ccDiv(const cocos2d::CCSize& pA, const cocos2d::CCSize& pB) noexcept {
        return cocos2d::CCSize{pA.width / pB.width, pA.height / pB.height};
    }
    template<IsCCVec2 T>
    constexpr auto ccDiv(const T& pA, const decltype(T::x)& pS) noexcept {
        return T{pA.x / pS, pA.y / pS};
    }
    constexpr auto ccDiv(const cocos2d::CCSize& pA, const decltype(cocos2d::CCSize::width)& pS) noexcept {
        return cocos2d::CCSize{pA.width / pS, pA.height / pS};
    }
}