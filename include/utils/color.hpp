#pragma once

#include "../export.hpp"
#include "misc.hpp"

namespace nwo5::utils {
    class SillyHSV;

    namespace impl {
        constexpr SillyHSV toHSV4F(cocos2d::ccColor4F col);
        constexpr cocos2d::ccColor4F toRGB4F(SillyHSV hSV);
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
        constexpr SillyHSV(float h, float s, float v)
            : h(h), s(s), v(v), a(1.0f) {}
        constexpr SillyHSV(float h, float s, float v, float a)
            : h(h), s(s), v(v), a(a) {}
        constexpr SillyHSV(cocos2d::ccColor4F col)
            : SillyHSV(impl::toHSV4F(col)) {}

        constexpr SillyHSV hueShift(float amount) {
            return {std::fmod(h + amount, HUE_MAX), s, v, a};
        }
    };

    namespace impl {
        constexpr SillyHSV toHSV4F(cocos2d::ccColor4F col) {
            const float max = std::max(std::max(col.r, col.g), col.b);
            const float min = std::min(std::min(col.r, col.g), col.b);
            const float delta = max - min;

            SillyHSV out{0.0f, max ? (delta / max) : 0.0f, max, col.a};

            if (delta > 0.0f) {
                if (max == col.r) {
                    out.h = std::fmod((col.g - col.b) / delta, 6.0f);
                }
                else if (max == col.g) {
                    out.h = ((col.b - col.r) / delta) + 2.0f;
                }
                else {
                    out.h = ((col.r - col.g) / delta) + 4.0f;
                }

                out.h *= 60.0f;

                if (out.h < 0.0f) {
                    out.h += SillyHSV::HUE_MAX;
                }
            }

            return out;
        }
        constexpr cocos2d::ccColor4F toRGB4F(SillyHSV hSV) {
            hSV.h = std::fmod(hSV.h, SillyHSV::HUE_MAX);

            const float c = hSV.v * hSV.s;
            const float x = c * (1.0f - std::fabs(std::fmod(hSV.h / 60.0f, 2.0f) - 1.0f));
            const float m = hSV.v - c;

            float r = 0.0f, g = 0.0f, b = 0.0f;

            if (hSV.h >= 0.0f && hSV.h < 60.0f) {
                r = c; g = x; b = 0.0f;
            }
            else if (hSV.h >= 60.0f && hSV.h < 120.0f) {
                r = x; g = c; b = 0.0f;
            }
            else if (hSV.h >= 120.0f && hSV.h < 180.0f) {
                r = 0.0f; g = c; b = x;
            }
            else if (hSV.h >= 180.0f && hSV.h < 240.0f) {
                r = 0.0f; g = x; b = c;
            }
            else if (hSV.h >= 240.0f && hSV.h < 300.0f) {
                r = x; g = 0.0f; b = c;
            }
            else if (hSV.h >= 300.0f && hSV.h < 360.0f) {
                r = c; g = 0.0f; b = x;
            }

            return {r + m, g + m, b + m, hSV.a};
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
    template<typename T>
    concept ColorHasOpacity = (
        IsColorHSV<T>,
        requires(T val) {
            val.a;
        }
    );

    template<IsColorHSV After, IsColorHSV Before>
    constexpr After color_cast(Before val) {
        if constexpr (std::same_as<Before, After>) {
            return val;
        }
        else if constexpr (std::same_as<Before, SillyHSV>) {
            return color_cast<cocos2d::ccColor4F>(impl::toRGB4F(val));
        }
        else if constexpr (std::same_as<After, SillyHSV>) {
            return impl::toHSV4F(color_cast<cocos2d::ccColor4F>(val));
        }
        else if constexpr (std::same_as<Before, cocos2d::ccColor3B>) {
            if constexpr (std::same_as<After, cocos2d::ccColor4B>) {
                return {val.r, val.g, val.b, 255};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4F>) {
                return {val.r / 255.0f, val.g / 255.0f, val.b / 255.0f, 1.0f};
            }
        }
        else if constexpr (std::same_as<Before, cocos2d::ccColor4B>) {
            if constexpr (std::same_as<After, cocos2d::ccColor3B>) {
                return {val.r, val.g, val.b};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4F>) {
                return {val.r / 255.0f, val.g / 255.0f, val.b / 255.0f, val.a / 255.0f};
            }
        }
        else {
            if constexpr (std::same_as<After, cocos2d::ccColor3B>) {
                return {static_cast<GLubyte>(val.r * 255), static_cast<GLubyte>(val.g * 255), static_cast<GLubyte>(val.b * 255)};
            }
            else if constexpr (std::same_as<After, cocos2d::ccColor4B>) {
                return {static_cast<GLubyte>(val.r * 255), static_cast<GLubyte>(val.g * 255), static_cast<GLubyte>(val.b * 255), static_cast<GLubyte>(val.a * 255)};
            }
        }
    }
    
    template<IsColor T, typename U>
    constexpr T setRed(T col, U red) {
        col.r = red;
        return col;
    }
    template<IsColor T, typename U>
    constexpr T setGreen(T col, U red) {
        col.g = red;
        return col;
    }
    template<IsColor T, typename U>
    constexpr T setBlue(T col, U red) {
        col.b = red;
        return col;
    }
    template<ColorHasOpacity T, typename U>
    constexpr T setOpacity(T col, U opacity) {
        col.a = opacity;
        return col;
    }

    template<IsColor T>
    constexpr SillyHSV toHSV(T col) {
        return impl::toHSV4F(color_cast<cocos2d::ccColor4F>(col));
    }
    template<IsColor T>
    constexpr T toRGB(SillyHSV col) {
        return color_cast<T>(impl::toRGB4F(col));
    }

    /// darken a colors value
    /// @param factor 0 is no change, 1 is black
    /// @note kinda slow since it converts to and from hsv
    template<IsColor T>
    constexpr T darken(T col, float factor) {
        auto hsv = toHSV(col);

        hsv.v = std::clamp(hsv.v * (1.0f - factor), 0.0f, 1.0f);

        return toRGB<T>(hsv);
    }
    /// lighten a colors value
    /// @param factor 0 is no change, 1 is white
    /// @note kinda slow since it converts to and from hsv
    template<IsColor T>
    constexpr T lighten(T col, float factor) {
        auto hsv = toHSV(col);

        hsv.v = std::clamp(hsv.v + (1.0f - hsv.v) * factor, 0.0f, 1.0f);

        return toRGB<T>(hsv);
    }

    template<IsColor T>
    constexpr T lerp(T start, T end, float time) {
        if constexpr (std::same_as<T, cocos2d::ccColor3B>) {
            return {
                static_cast<GLubyte>(std::clamp(start.r + (static_cast<float>(end.r) - start.r) * time, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(start.g + (static_cast<float>(end.g) - start.g) * time, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(start.b + (static_cast<float>(end.b) - start.b) * time, 0.0f, 255.0f))
            };
        }
        else if constexpr (std::same_as<T, cocos2d::ccColor4B>) {
            return {
                static_cast<GLubyte>(std::clamp(start.r + (static_cast<float>(end.r) - start.r) * time, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(start.g + (static_cast<float>(end.g) - start.g) * time, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(start.b + (static_cast<float>(end.b) - start.b) * time, 0.0f, 255.0f)),
                static_cast<GLubyte>(std::clamp(start.a + (static_cast<float>(end.a) - start.a) * time, 0.0f, 255.0f))
            };
        }
        else {
            return {
                start.r + (end.r - start.r) * time,
                start.g + (end.g - start.g) * time,
                start.b + (end.b - start.b) * time,
                start.a + (end.a - start.a) * time
            };
        }
    }

    namespace impl {
        SILLY_API_DLL cocos2d::ccColor4F getChroma4F(float speed, float offset, float saturation, float value);
    }

    /// get a chroma color based on the current time
    /// @param speed how long it should take for color to do a full 360 hue rotation (seconds)
    /// @param offset added to hue (hint, u can use enums) * 360
    /// @param saturation saturation of outputted color
    /// @param value value of outputted color
    template<typename ImplT = cocos2d::ccColor4F, typename Offset = float, typename T = std::decay_t<ImplT>>
    T getChroma(float speed, Offset offset = Offset{}, float saturation = 1.0f, float value = 1.0f) {
        return color_cast<T>(nwo5::utils::impl::getChroma4F(speed, enum_cast<float>(offset), saturation, value));
    }
}