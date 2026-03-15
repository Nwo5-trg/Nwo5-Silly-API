#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    using EasingFunction = float(*)(float, float);

    SILLY_API_DLL EasingFunction getEasingFunction(EasingType pType);

    namespace easings {
        constexpr float EASING_CC5 = 1.39626f;
        constexpr float EASING_CC4 = 2.09440f;
        constexpr float EASING_CC3 = 2.70158f;
        constexpr float EASING_CC2 = 2.59491f;
        constexpr float EASING_CC1 = 1.70158f;

        SILLY_API_DLL float easeLinear(float pX, float pE);
        SILLY_API_DLL float easeInOut(float pX, float pE);
        SILLY_API_DLL float easeIn(float pX, float pE);
        SILLY_API_DLL float easeOut(float pX, float pE);
        SILLY_API_DLL float easeElasticInOut(float pX, float pE);
        SILLY_API_DLL float easeElasticIn(float pX, float pE);
        SILLY_API_DLL float easeElasticOut(float pX, float pE);
        SILLY_API_DLL float easeBounceInOut(float pX, float pE);
        SILLY_API_DLL float easeBounceIn(float pX, float pE);
        SILLY_API_DLL float easeBounceOut(float pX, float pE);
        SILLY_API_DLL float easeExponentialInOut(float pX, float pE);
        SILLY_API_DLL float easeExponentialIn(float pX, float pE);
        SILLY_API_DLL float easeExponentialOut(float pX, float pE);
        SILLY_API_DLL float easeSineInOut(float pX, float pE);
        SILLY_API_DLL float easeSineIn(float pX, float pE);
        SILLY_API_DLL float easeSineOut(float pX, float pE);
        SILLY_API_DLL float easeBackInOut(float pX, float pE);
        SILLY_API_DLL float easeBackIn(float pX, float pE);
        SILLY_API_DLL float easeBackOut(float pX, float pE);
    }
}