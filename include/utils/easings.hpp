#pragma once

#include <numbers>

namespace nwo5::utils {
    using EasingFunction = float(*)(float, float);

    template<typename T>
    requires std::is_floating_point_v<T>
    struct Easing final {
    private:
        static T bounceTime(T pX) {
            if (pX < 1 / T{2.75}) {
                return T{7.5625} * pX * pX;
            }
            else if (pX < 2 / T{2.75}) {
                pX -= T{1.5} / T{2.75};

                return T{7.5625} * pX * pX + T{0.75};
            }
            else if(pX < T{2.5} / T{2.75}) {
                pX -= T{2.25} / T{2.75};

                return T{7.5625} * pX * pX + T{0.9375};
            }

            pX -= T{2.625} / T{2.75};

            return T{7.5625} * pX * pX + T{0.984375};
        }
        
    public:
        static T linear(T pX, T pE) {
            return pX;
        }
        static T inOut(T pX, T pE) {
            pX *= 2;

            if (pX < 1) {
                return T{0.5} * std::pow<T>(pX, pE);
            }

            return T{0.5} * (T{2} - std::pow<T>(T{2} - pX, pE));
        }
        static T in(T pX, T pE) {
            return std::pow<T>(pX, pE);
        }
        static T out(T pX, T pE) {
            return 1 - std::pow<T>(1 - pX, pE);
        }
        static T elasticInOut(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }
            
            if (!pE) {
                pE = T{0.3} * T{1.5};
            }

            pX = pX * 2 - 1; 

            if (pX < 0) {
                return -T{0.5} * std::pow<T>(2, 10 * pX) * std::sin<T>((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE);
            }
            else
            {
                return std::pow<T>(2, -10 * pX) * std::sin<T>((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE) * T{0.5} + 1;
            }
        }
        static T elasticIn(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }

            pX -= 1;

            return -std::pow<T>(2, 10 * pX) * std::sin<T>((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE);
        }
        static T elasticOut(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }

            return std::pow<T>(2, -10 * pX) * std::sin<T>((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE) + 1;
        }
        static T bounceInOut(T pX, T pE) {
            if (pX < 0.5f) {
                return (1 - bounceTime(1 - (pX * 2))) * T{0.5};
            }
            else {
                return bounceTime(pX * 2 - 1) * T{0.5} + T{0.5};
            }
        }
        static T bounceIn(T pX, T pE) {
            return 1 - bounceTime(1 - pX);
        }
        static T bounceOut(T pX, T pE) {
            return bounceTime(pX);
        }
        static T exponentialInOut(T pX, T pE) {
            if(!pX || pX == 1) {
                return pX;
            }
            
            if (pX < T{0.5}) {
                return T{0.5} * std::pow<T>(2, 10 * (pX * 2 - 1));
            }
            
            return T{0.5} * (-std::pow<T>(2, -10 * (pX * 2 - 1)) + 2);
        }
        static T exponentialIn(T pX, T pE) {
            if (!pX || pX == 1) {
                return pX;
            }

            // ????? y cocos this seemse so pointless but ill do it anyway for the sake of parity
            return std::pow<T>(2, 10 * (pX - 1)) - T{0.001};
        }
        static T exponentialOut(T pX, T pE) {
            if (!pX || pX == 1) {
                return pX;
            }
            
            return -std::pow<T>(2, -10 * pX) + 1;
        }
        static T sineInOut(T pX, T pE) {
            return -T{0.5} * (std::cos<T>(std::numbers::pi_v<T> * pX) - 1);
        }
        static T sineIn(T pX, T pE) {
            return -1 * std::cos<T>(pX * (std::numbers::pi_v<T> / 2)) + 1;
        }
        static T sineOut(T pX, T pE) {
            return std::sin<T>(pX * (std::numbers::pi_v<T> / 2));
        }
        static T backInOut(T pX, T pE) {
            constexpr auto overshoot = T{1.70158} * T{1.525};

            pX *= 2;

            if (pX < 1) {
                return (pX * pX * ((overshoot + 1) * pX - overshoot)) / 2;
            }
            else {
                pX -= 2;
                return (pX * pX * ((overshoot + 1) * pX + overshoot)) / 2 + 1;
            }
        }
        static T backIn(T pX, T pE) {
            constexpr auto overshoot = T{1.70158};

            return pX * pX * ((overshoot + 1) * pX - overshoot);
        }
        static T backOut(T pX, T pE) {
            constexpr auto overshoot = T{1.70158};

            pX -= 1;

            return pX * pX * ((overshoot + 1) * pX + overshoot) + 1;
        }
    };

    template<typename T>
    T ease(EasingType pType, T pX, T pE = T{}) {
        switch (pType) {
            case EasingType::None: return nwo5::utils::Easing<T>::easeLinear(pX, pE);
            case EasingType::EaseIn: return nwo5::utils::Easing<T>::easeIn(pX, pE);
            case EasingType::EaseOut: return nwo5::utils::Easing<T>::easeOut(pX, pE);
            case EasingType::EaseInOut: return nwo5::utils::Easing<T>::easeInOut(pX, pE);
            case EasingType::ElasticInOut: return nwo5::utils::Easing<T>::easeElasticInOut(pX, pE);
            case EasingType::ElasticIn: return nwo5::utils::Easing<T>::easeElasticIn(pX, pE);
            case EasingType::ElasticOut: return nwo5::utils::Easing<T>::easeElasticOut(pX, pE);
            case EasingType::BounceInOut: return nwo5::utils::Easing<T>::easeBounceInOut(pX, pE);
            case EasingType::BounceIn: return nwo5::utils::Easing<T>::easeBounceIn(pX, pE);
            case EasingType::BounceOut: return nwo5::utils::Easing<T>::easeBounceOut(pX, pE);
            case EasingType::ExponentialInOut: return nwo5::utils::Easing<T>::easeExponentialInOut(pX, pE);
            case EasingType::ExponentialIn: return nwo5::utils::Easing<T>::easeExponentialIn(pX, pE);
            case EasingType::ExponentialOut: return nwo5::utils::Easing<T>::easeExponentialOut(pX, pE);
            case EasingType::SineInOut: return nwo5::utils::Easing<T>::easeSineInOut(pX, pE);
            case EasingType::SineIn: return nwo5::utils::Easing<T>::easeSineIn(pX, pE);
            case EasingType::SineOut: return nwo5::utils::Easing<T>::easeSineOut(pX, pE);
            case EasingType::BackInOut: return nwo5::utils::Easing<T>::easeBackInOut(pX, pE);
            case EasingType::BackIn: return nwo5::utils::Easing<T>::easeBackIn(pX, pE);
            case EasingType::BackOut: return nwo5::utils::Easing<T>::easeBackOut(pX, pE);
            default: return T{};
        }
    }

    template<typename T>
    EasingFunction getEasingFunction(EasingType pType) {
        switch (pType) {
            case EasingType::None: return nwo5::utils::Easing<T>::easeLinear;
            case EasingType::EaseIn: return nwo5::utils::Easing<T>::easeIn;
            case EasingType::EaseOut: return nwo5::utils::Easing<T>::easeOut;
            case EasingType::EaseInOut: return nwo5::utils::Easing<T>::easeInOut;
            case EasingType::ElasticInOut: return nwo5::utils::Easing<T>::easeElasticInOut;
            case EasingType::ElasticIn: return nwo5::utils::Easing<T>::easeElasticIn;
            case EasingType::ElasticOut: return nwo5::utils::Easing<T>::easeElasticOut;
            case EasingType::BounceInOut: return nwo5::utils::Easing<T>::easeBounceInOut;
            case EasingType::BounceIn: return nwo5::utils::Easing<T>::easeBounceIn;
            case EasingType::BounceOut: return nwo5::utils::Easing<T>::easeBounceOut;
            case EasingType::ExponentialInOut: return nwo5::utils::Easing<T>::easeExponentialInOut;
            case EasingType::ExponentialIn: return nwo5::utils::Easing<T>::easeExponentialIn;
            case EasingType::ExponentialOut: return nwo5::utils::Easing<T>::easeExponentialOut;
            case EasingType::SineInOut: return nwo5::utils::Easing<T>::easeSineInOut;
            case EasingType::SineIn: return nwo5::utils::Easing<T>::easeSineIn;
            case EasingType::SineOut: return nwo5::utils::Easing<T>::easeSineOut;
            case EasingType::BackInOut: return nwo5::utils::Easing<T>::easeBackInOut;
            case EasingType::BackIn: return nwo5::utils::Easing<T>::easeBackIn;
            case EasingType::BackOut: return nwo5::utils::Easing<T>::easeBackOut;
            default: return nullptr;
        }
    }
}