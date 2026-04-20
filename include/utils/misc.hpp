#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    namespace impl {
        SILLY_API_DLL cocos2d::ccColor4F getChroma4F(float pSpeed, float pOffset, float pSaturation, float pValue);
    }

    /// count how many instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 3 will be outputed
    SILLY_API_DLL size_t stringCount(std::string_view pString, std::string_view pSubstr);
    /// count how many *independant* instances of a substr appear in str
    /// for str "aaaa" and substr "aa", 2 will be outputed
    SILLY_API_DLL size_t stringCountIndependant(std::string_view pString, std::string_view pSubstr);
    /// the geode util
    SILLY_API_DLL size_t stringCount(std::string_view pString, char pSubstr);
    /// ccmenuitemtoggler triggers callback before its actually toggled so
    /// technically breaks when calling with togglewithcallback but idk fuck robtop
    SILLY_API_DLL bool isToggled(cocos2d::CCObject* pToggler);

    SILLY_API_DLL void removeAllObjects(cocos2d::CCArray* pArray, bool pRelease = false);
    SILLY_API_DLL void removeObjectsFromArray(cocos2d::CCArray* pArray, cocos2d::CCArray* pOther, bool pRelease = false);
    SILLY_API_DLL cocos2d::CCArray* sharedObjects(cocos2d::CCArray* pArray, cocos2d::CCArray* pOther);
    SILLY_API_DLL std::optional<unsigned int> findObject(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj);
    SILLY_API_DLL cocos2d::CCArray* objectsBefore(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj, bool pInclusive = true);
    SILLY_API_DLL cocos2d::CCArray* objectsAfter(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj, bool pInclusive = true);

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

    /// casts a numer to another number (but also works with enums)
    /// another day some more bullshit i learn abt templates this is literally just for chroma to work
    template<typename T, typename U>
    requires std::is_arithmetic_v<T> && (std::is_arithmetic_v<U> || std::is_scoped_enum_v<U>)
    T enumNumCast(U pEnum) {
        if constexpr (std::is_scoped_enum_v<U>) {
            return static_cast<T>(std::to_underlying(pEnum));
        }
        else {
            return static_cast<T>(pEnum);
        }
    }

    /// get a chroma color based on the current time
    /// @param pSpeed how long it should take for color to do a full 360 hue rotation (seconds)
    /// @param pOffset added to hue (hint, u can use enums)
    /// @param pSaturation saturation of outputted color
    /// @param pValue value of outputted color
    template<typename ImplT = cocos2d::ccColor4F, typename Offset = float, typename T = std::decay_t<ImplT>>
    T getChroma(float pSpeed, Offset pOffset = Offset{}, float pSaturation = 1.0f, float pValue = 1.0f) {
        const auto cc4f = nwo5::utils::impl::getChroma4F(pSpeed, enumNumCast<float>(pOffset), pSaturation, pValue);

        if constexpr (std::same_as<T, cocos2d::ccColor3B>) {
            return {static_cast<GLubyte>(cc4f.r * 255), static_cast<GLubyte>(cc4f.g * 255), static_cast<GLubyte>(cc4f.b * 255)};
        }
        else if constexpr (std::same_as<T, cocos2d::ccColor4B>) {
            return cocos2d::ccc4BFromccc4F(cc4f);
        }
        else if constexpr (std::same_as<T, cocos2d::ccColor4F>) {
            return cc4f;
        }
        else {
            static_assert(false, "u cant b that type of gay ;3");
        }
    }
}