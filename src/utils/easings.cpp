#include <utils/include.hpp>
#include <numbers>

using namespace geode::prelude;

namespace nwo5::utils {
    EasingFunction getEasingFunction(EasingType pType) {
        switch (pType) {
            case EasingType::None: return nwo5::utils::easings::easeLinear;
            case EasingType::EaseIn: return nwo5::utils::easings::easeIn;
            case EasingType::EaseOut: return nwo5::utils::easings::easeOut;
            case EasingType::EaseInOut: return nwo5::utils::easings::easeInOut;
            case EasingType::ElasticInOut: return nwo5::utils::easings::easeElasticInOut;
            case EasingType::ElasticIn: return nwo5::utils::easings::easeElasticIn;
            case EasingType::ElasticOut: return nwo5::utils::easings::easeElasticOut;
            case EasingType::BounceInOut: return nwo5::utils::easings::easeBounceInOut;
            case EasingType::BounceIn: return nwo5::utils::easings::easeBounceIn;
            case EasingType::BounceOut: return nwo5::utils::easings::easeBounceOut;
            case EasingType::ExponentialInOut: return nwo5::utils::easings::easeExponentialInOut;
            case EasingType::ExponentialIn: return nwo5::utils::easings::easeExponentialIn;
            case EasingType::ExponentialOut: return nwo5::utils::easings::easeExponentialOut;
            case EasingType::SineInOut: return nwo5::utils::easings::easeSineInOut;
            case EasingType::SineIn: return nwo5::utils::easings::easeSineIn;
            case EasingType::SineOut: return nwo5::utils::easings::easeSineOut;
            case EasingType::BackInOut: return nwo5::utils::easings::easeBackInOut;
            case EasingType::BackIn: return nwo5::utils::easings::easeBackIn;
            case EasingType::BackOut: return nwo5::utils::easings::easeBackOut;
            default: return nwo5::utils::easings::easeLinear;
        }
    }

    namespace easings {
        float easeLinear(float pX, float pE) {
            return pX;
        }
        float easeInOut(float pX, float pE) {
            if (pX) {
                return std::pow(2 * pX, pE) / 2;
            }
            else {
                return 1 - (std::pow(2 * (1 - pX), pE) / 2);
            }
        }
        float easeIn(float pX, float pE) {
            return std::pow(pX, pE);
        }
        float easeOut(float pX, float pE) {
            return 1 - std::pow(1 - pX, pE);
        }
        float easeElasticInOut(float pX, float pE) {
            if (!pX || pX == 1.0f) {
                return pX;
            }
            
            const float expo = pE * 10;

            if (pX < 0.5f) {
                return -0.5f * std::pow(2, expo * 2 * pX - expo) * std::sin(((expo * 2 * pX) - expo + 0.25f) * nwo5::utils::easings::EASING_CC5);
            }
            else {
                return 0.5f * std::pow(2, -expo * 2 * (pX - 0.5f)) * std::sin(((expo * 2 * (pX - 0.5f)) - 0.75f) * nwo5::utils::easings::EASING_CC5) + 1;
            }
        }
        float easeElasticIn(float pX, float pE) {
            if (!pX || pX == 1.0f) {
                return pX;
            }

            const float expo = pE * 10;

            return -std::pow(2, expo * pX - expo) * std::sin(((pX * expo) - expo + 0.25f) * nwo5::utils::easings::EASING_CC4);
        }
        float easeElasticOut(float pX, float pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }
            const float expo = pE * 10;

            return std::pow(2, -expo * pX) * std::sin(((pX * expo) - 0.75f) * nwo5::utils::easings::EASING_CC4) + 1;
        }
        float easeBounceInOut(float pX, float pE) {
            if(pX < 0.5f) {
                return 8 * std::pow(2, 8 * (pX - 1)) * std::abs(std::sin((pX * std::numbers::pi) * 7));
            }
            else {
                return 1 - (8 * std::pow( 2, -8 * pX) * std::abs(std::sin((pX * std::numbers::pi) * 7)));
            }
        }
        float easeBounceIn(float pX, float pE) {
            return std::pow(2, 6 * (pX - 1)) * std::abs(std::sin((pX * std::numbers::pi) * 3.5f));
        }
        float easeBounceOut(float pX, float pE) {
            return 1 - (std::pow(2, -6 * pX) * std::abs(std::cos((pX * std::numbers::pi) * 3.5f)));
        }
        float easeExponentialInOut(float pX, float pE) {
            if (!pX || pX == 1.0f) {
                return pX;
            }
            else if (pX < 0.5f) {
                return std::pow(2, (20 * pX) - 10) / 2;
            }
            else {
                return (2 - std::pow(2, (-20 * pX) + 10)) / 2;
            }
        }
        float easeExponentialIn(float pX, float pE) {
            if (pX) {
                return std::pow(2, 10 * (pX - 1));
            }
            else {
                return pX;
            }
        }
        float easeExponentialOut(float pX, float pE) {
            if (pX == 1.0f) {
                return pX;
            }
            else {
                return 1 - std::pow(2, -10 * pX);
            }
        }
        float easeSineInOut(float pX, float pE) {
            return -(std::cos(std::numbers::pi * pX) - 1) / 2;
        }
        float easeSineIn(float pX, float pE) {
            return 1 - std::cos((pX * std::numbers::pi) / 2);
        }
        float easeSineOut(float pX, float pE) {
            return std::sin((pX * std::numbers::pi) / 2);
        }
        float easeBackInOut(float pX, float pE) {
            if (pX < 0.5f) {
                return (std::pow(((2 * pX)), 2)) * ((((nwo5::utils::easings::EASING_CC2 + 1) * ((2 * pX))) - nwo5::utils::easings::EASING_CC2)) / 2;
            }
            else {
                return (((std::pow((((2 * pX) - 2)), 2)) * (((nwo5::utils::easings::EASING_CC2 + 1) * (((2 * pX) - 2))) + nwo5::utils::easings::EASING_CC2)) + 2) / 2;
            }
        }
        float easeBackIn(float pX, float pE) {
            return (nwo5::utils::easings::EASING_CC3 * std::pow(pX, 3)) - (nwo5::utils::easings::EASING_CC1 * std::pow(pX, 2));
        }
        float easeBackOut(float pX, float pE) {
            return 1 + ((nwo5::utils::easings::EASING_CC3 * std::pow(pX - 1, 3)) + (nwo5::utils::easings::EASING_CC1 * std::pow(pX - 1, 2)));
        }
    }
}