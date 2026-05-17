#pragma 

#include "../export.hpp"

namespace nwo5::utils {
    class SillyHSV;

    namespace impl {
        constexpr SillyHSV toHSV4F(cocos2d::ccColor4F pCol);
        constexpr cocos2d::ccColor4F toRGB4F(SillyHSV pHSV);
    }

    /// hsva class !
    /// hue from 0-360
    /// saturation from 0-1
    /// value from 0-1
    /// alpha from 0-1
    class SillyHSV {
    public:
        float h = 0.0f;
        float s = 0.0f;
        float v = 0.0f;
        float a = 0.0f;

        static constexpr float HUE_MAX = 360.0f;
        static constexpr float SATURATION_MAX = 1.0f;
        static constexpr float VALUE_MAX = 1.0f;
        static constexpr float ALPHA_MAX = 1.0f;

        constexpr SillyHSV() = default;
        constexpr SillyHSV(float pH, float pS, float pV)
            : h(pH), s(pS), v(pV), a(1.0f) {}
        constexpr SillyHSV(float pH, float pS, float pV, float pA)
            : h(pH), s(pS), v(pV), a(pA) {}
        constexpr SillyHSV(cocos2d::ccColor4F pCol)
            : SillyHSV(impl::toHSV4F(pCol)) {}

        constexpr SillyHSV hueShift(float pAmount) {
            return {std::fmod(h + pAmount, HUE_MAX), s, v, a};
        }
    };

    namespace impl {
        constexpr SillyHSV toHSV4F(cocos2d::ccColor4F pCol) {
            const float max = std::max(std::max(pCol.r, pCol.g), pCol.b);
            const float min = std::min(std::min(pCol.r, pCol.g), pCol.b);
            const float delta = max - min;

            SillyHSV out{0.0f, max ? (delta / max) : 0.0f, max, pCol.a};

            if (delta > 0.0f) {
                if (max == pCol.r) {
                    out.h = std::fmod((pCol.g - pCol.b) / delta, 6.0f);
                }
                else if (max == pCol.g) {
                    out.h = ((pCol.b - pCol.r) / delta) + 2.0f;
                }
                else {
                    out.h = ((pCol.r - pCol.g) / delta) + 4.0f;
                }

                out.h *= 60.0f;

                if (out.h < 0.0f) {
                    out.h += SillyHSV::HUE_MAX;
                }
            }

            return out;
        }
        constexpr cocos2d::ccColor4F toRGB4F(SillyHSV pHSV) {
            pHSV.h = std::fmod(pHSV.h, SillyHSV::HUE_MAX);

            const float c = pHSV.v * pHSV.s;
            const float x = c * (1.0f - std::fabs(std::fmod(pHSV.h / 60.0f, 2.0f) - 1.0f));
            const float m = pHSV.v - c;

            float r = 0.0f, g = 0.0f, b = 0.0f;

            if (pHSV.h >= 0.0f && pHSV.h < 60.0f) {
                r = c; g = x; b = 0.0f;
            }
            else if (pHSV.h >= 60.0f && pHSV.h < 120.0f) {
                r = x; g = c; b = 0.0f;
            }
            else if (pHSV.h >= 120.0f && pHSV.h < 180.0f) {
                r = 0.0f; g = c; b = x;
            }
            else if (pHSV.h >= 180.0f && pHSV.h < 240.0f) {
                r = 0.0f; g = x; b = c;
            }
            else if (pHSV.h >= 240.0f && pHSV.h < 300.0f) {
                r = x; g = 0.0f; b = c;
            }
            else if (pHSV.h >= 300.0f && pHSV.h < 360.0f) {
                r = c; g = 0.0f; b = x;
            }

            return {r + m, g + m, b + m, pHSV.a};
        }
    }

    template<typename T>
    concept IsColor = (
        std::same_as<T, cocos2d::ccColor3B> 
        || std::same_as<T, cocos2d::ccColor4B>
        || std::same_as<T, cocos2d::ccColor4F>
    );
    template<typename T>
    concept IsColorHSV = (
        IsColor<T>
        || std::same_as<T, SillyHSV>
    );

    template<IsColorHSV After, IsColorHSV Before>
    constexpr After color_cast(Before pVal) {
        if constexpr (std::same_as<Before, After>) {
            return pVal;
        }
        else if constexpr (std::same_as<Before, SillyHSV>) {
            return color_cast<cocos2d::ccColor4F>(impl::toRGB4F(pVal));
        }
        else if constexpr (std::same_as<After, SillyHSV>) {
            return impl::toHSV4F(color_cast<cocos2d::ccColor4F>(pVal));
        }
        else if constexpr (std::same_as<Before, cocos2d::ccColor3B>) {
            if constexpr (std::same_as<After, cocos2d::ccColor4B>) {
                return {pVal.r, pVal.g, pVal.b, 255};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4F>) {
                return {pVal.r / 255.0f, pVal.g / 255.0f, pVal.b / 255.0f, 1.0f};
            }
        }
        else if constexpr (std::same_as<Before, cocos2d::ccColor4B>) {
            if constexpr (std::same_as<After, cocos2d::ccColor3B>) {
                return {pVal.r, pVal.g, pVal.b};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4F>) {
                return {pVal.r / 255.0f, pVal.g / 255.0f, pVal.b / 255.0f, pVal.a / 255.0f};
            }
        }
        else {
            if constexpr (std::same_as<After, cocos2d::ccColor3B>) {
                return {static_cast<GLubyte>(pVal.r * 255), static_cast<GLubyte>(pVal.g * 255), static_cast<GLubyte>(pVal.b * 255)};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4B>) {
                return {static_cast<GLubyte>(pVal.r * 255), static_cast<GLubyte>(pVal.g * 255), static_cast<GLubyte>(pVal.b * 255), static_cast<GLubyte>(pVal.a * 255)};
            }
        }
    }

    template<IsColor T>
    constexpr SillyHSV toHSV(T pCol) {
        return impl::toHSV4F(color_cast<cocos2d::ccColor4F>(pCol));
    }
    template<IsColor T>
    constexpr T toRGB(SillyHSV pCol) {
        return color_cast<T>(impl::toRGB4F(pCol));
    }

    /// darken a colors value
    /// @param pFactor 0 is no change, 1 is black
    /// @note kinda slow since it converts to and from hsv
    template<IsColor T>
    constexpr T darken(T pCol, float pFactor) {
        auto hsv = toHSV(pCol);

        hsv.v = std::clamp(hsv.v * (1.0f - pFactor), 0.0f, 1.0f);

        return toRGB<T>(hsv);
    }
    /// lighten a colors value
    /// @param pFactor 0 is no change, 1 is white
    /// @note kinda slow since it converts to and from hsv
    template<IsColor T>
    constexpr T lighten(T pCol, float pFactor) {
        auto hsv = toHSV(pCol);

        hsv.v = std::clamp(hsv.v + (1.0f - hsv.v) * pFactor, 0.0f, 1.0f);

        return toRGB<T>(hsv);
    }

    template<IsColor T>
    constexpr T lerp(T pStart, T pEnd, float pTime) {
        if constexpr (std::same_as<T, cocos2d::ccColor3B>) {
            return {
                static_cast<GLubyte>(std::clamp(pStart.r + (static_cast<float>(pEnd.r) - pStart.r) * pTime, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(pStart.g + (static_cast<float>(pEnd.g) - pStart.g) * pTime, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(pStart.b + (static_cast<float>(pEnd.b) - pStart.b) * pTime, 0.0f, 255.0f))
            };
        }
        else if constexpr (std::same_as<T, cocos2d::ccColor4B>) {
            return {
                static_cast<GLubyte>(std::clamp(pStart.r + (static_cast<float>(pEnd.r) - pStart.r) * pTime, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(pStart.g + (static_cast<float>(pEnd.g) - pStart.g) * pTime, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(pStart.b + (static_cast<float>(pEnd.b) - pStart.b) * pTime, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(pStart.a + (static_cast<float>(pEnd.a) - pStart.a) * pTime, 0.0f, 255.0f))
            };
        }
        else {
            return {
                pStart.r + (pEnd.r - pStart.r) * pTime,
                pStart.g + (pEnd.g - pStart.g) * pTime,
                pStart.b + (pEnd.b - pStart.b) * pTime,
                pStart.a + (pEnd.a - pStart.a) * pTime
            };
        }
    }

    namespace impl {
        SILLY_API_DLL cocos2d::ccColor4F getChroma4F(float pSpeed, float pOffset, float pSaturation, float pValue);
    }

    /// get a chroma color based on the current time
    /// @param pSpeed how long it should take for color to do a full 360 hue rotation (seconds)
    /// @param pOffset added to hue (hint, u can use enums) * 360
    /// @param pSaturation saturation of outputted color
    /// @param pValue value of outputted color
    template<typename ImplT = cocos2d::ccColor4F, typename Offset = float, typename T = std::decay_t<ImplT>>
    T getChroma(float pSpeed, Offset pOffset = Offset{}, float pSaturation = 1.0f, float pValue = 1.0f) {
        return color_cast<T>(nwo5::utils::impl::getChroma4F(pSpeed, enum_cast<float>(pOffset), pSaturation, pValue));
    }
}