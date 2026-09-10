#pragma once

#include <numbers>

namespace nwo5::utils {
    template<typename T>
    using EasingFunction = T(*)(T, T);

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
                return T{0.5} * std::pow(pX, pE);
            }

            return 1 - T{0.5} * std::pow(T{2} - pX, pE);
        }
        static T in(T pX, T pE) {
            return std::pow(pX, pE);
        }
        static T out(T pX, T pE) {
            return std::pow(pX, 1 / pE);
        }
        static T elasticInOut(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }

            pX *= 2;

            if (!pE) {
                pE = T{0.3} * T{1.5};
            }

            pX -= 1;

            if (pX < 0) {
                return -T{0.5} * std::pow(2, 10 * pX) * std::sin((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE);
            }
            else {
                return std::pow(2, -10 * pX) * std::sin((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE) * T{0.5} + 1;
            }
        }
        static T elasticIn(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }

            if (!pE) {
                pE = T{0.3};
            }

            pX -= 1;

            return -std::pow(2, 10 * pX) * std::sin((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE);
        }
        static T elasticOut(T pX, T pE) {
            if (pX == 0 || pX == 1) {
                return pX;
            }

            if (!pE) {
                pE = T{0.3};
            }

            return std::pow(2, -10 * pX) * std::sin((pX - (pE / 4)) * (std::numbers::pi_v<T> * 2) / pE) + 1;
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
                return T{0.5} * std::pow(2, 10 * (pX * 2 - 1));
            }
            
            return T{0.5} * (-std::pow(2, -10 * (pX * 2 - 1)) + 2);
        }
        static T exponentialIn(T pX, T pE) {
            if (!pX || pX == 1) {
                return pX;
            }

            // ????? y cocos this seemse so pointless but ill do it anyway for the sake of parity
            return std::pow(2, 10 * (pX - 1)) - T{0.001};
        }
        static T exponentialOut(T pX, T pE) {
            if (!pX || pX == 1) {
                return pX;
            }
            
            return -std::pow(2, -10 * pX) + 1;
        }
        static T sineInOut(T pX, T pE) {
            return -T{0.5} * (std::cos(std::numbers::pi_v<T> * pX) - 1);
        }
        static T sineIn(T pX, T pE) {
            return -1 * std::cos(pX * (std::numbers::pi_v<T> / 2)) + 1;
        }
        static T sineOut(T pX, T pE) {
            return std::sin(pX * (std::numbers::pi_v<T> / 2));
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
            case EasingType::None: return nwo5::utils::Easing<T>::linear(pX, pE);
            case EasingType::EaseIn: return nwo5::utils::Easing<T>::in(pX, pE);
            case EasingType::EaseOut: return nwo5::utils::Easing<T>::out(pX, pE);
            case EasingType::EaseInOut: return nwo5::utils::Easing<T>::inOut(pX, pE);
            case EasingType::ElasticInOut: return nwo5::utils::Easing<T>::elasticInOut(pX, pE);
            case EasingType::ElasticIn: return nwo5::utils::Easing<T>::elasticIn(pX, pE);
            case EasingType::ElasticOut: return nwo5::utils::Easing<T>::elasticOut(pX, pE);
            case EasingType::BounceInOut: return nwo5::utils::Easing<T>::bounceInOut(pX, pE);
            case EasingType::BounceIn: return nwo5::utils::Easing<T>::bounceIn(pX, pE);
            case EasingType::BounceOut: return nwo5::utils::Easing<T>::bounceOut(pX, pE);
            case EasingType::ExponentialInOut: return nwo5::utils::Easing<T>::exponentialInOut(pX, pE);
            case EasingType::ExponentialIn: return nwo5::utils::Easing<T>::exponentialIn(pX, pE);
            case EasingType::ExponentialOut: return nwo5::utils::Easing<T>::exponentialOut(pX, pE);
            case EasingType::SineInOut: return nwo5::utils::Easing<T>::sineInOut(pX, pE);
            case EasingType::SineIn: return nwo5::utils::Easing<T>::sineIn(pX, pE);
            case EasingType::SineOut: return nwo5::utils::Easing<T>::sineOut(pX, pE);
            case EasingType::BackInOut: return nwo5::utils::Easing<T>::backInOut(pX, pE);
            case EasingType::BackIn: return nwo5::utils::Easing<T>::backIn(pX, pE);
            case EasingType::BackOut: return nwo5::utils::Easing<T>::backOut(pX, pE);
            default: return T{};
        }
    }

    template<typename T>
    EasingFunction<T> getEasingFunction(EasingType pType) {
        switch (pType) {
            case EasingType::None: return nwo5::utils::Easing<T>::linear;
            case EasingType::EaseIn: return nwo5::utils::Easing<T>::in;
            case EasingType::EaseOut: return nwo5::utils::Easing<T>::out;
            case EasingType::EaseInOut: return nwo5::utils::Easing<T>::inOut;
            case EasingType::ElasticInOut: return nwo5::utils::Easing<T>::elasticInOut;
            case EasingType::ElasticIn: return nwo5::utils::Easing<T>::elasticIn;
            case EasingType::ElasticOut: return nwo5::utils::Easing<T>::elasticOut;
            case EasingType::BounceInOut: return nwo5::utils::Easing<T>::bounceInOut;
            case EasingType::BounceIn: return nwo5::utils::Easing<T>::bounceIn;
            case EasingType::BounceOut: return nwo5::utils::Easing<T>::bounceOut;
            case EasingType::ExponentialInOut: return nwo5::utils::Easing<T>::exponentialInOut;
            case EasingType::ExponentialIn: return nwo5::utils::Easing<T>::exponentialIn;
            case EasingType::ExponentialOut: return nwo5::utils::Easing<T>::exponentialOut;
            case EasingType::SineInOut: return nwo5::utils::Easing<T>::sineInOut;
            case EasingType::SineIn: return nwo5::utils::Easing<T>::sineIn;
            case EasingType::SineOut: return nwo5::utils::Easing<T>::sineOut;
            case EasingType::BackInOut: return nwo5::utils::Easing<T>::backInOut;
            case EasingType::BackIn: return nwo5::utils::Easing<T>::backIn;
            case EasingType::BackOut: return nwo5::utils::Easing<T>::backOut;
            default: return nullptr;
        }
    }
}