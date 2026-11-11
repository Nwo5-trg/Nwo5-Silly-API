#pragma once

#include <numbers>

namespace nwo5::utils {
    template<typename T>
    using EasingFunction = T(*)(T, T);

    template<typename T>
    requires std::is_floating_point_v<T>
    struct Easing final {
    private:
        static T bounceTime(T x) {
            if (x < 1 / T{2.75}) {
                return T{7.5625} * x * x;
            }
            else if (x < 2 / T{2.75}) {
                x -= T{1.5} / T{2.75};

                return T{7.5625} * x * x + T{0.75};
            }
            else if(x < T{2.5} / T{2.75}) {
                x -= T{2.25} / T{2.75};

                return T{7.5625} * x * x + T{0.9375};
            }

            x -= T{2.625} / T{2.75};

            return T{7.5625} * x * x + T{0.984375};
        }
        
    public:
        static T linear(T x, T e) {
            return x;
        }
        static T inOut(T x, T e) {
            x *= 2;

            if (x < 1) {
                return T{0.5} * std::pow(x, e);
            }

            return 1 - T{0.5} * std::pow(T{2} - x, e);
        }
        static T in(T x, T e) {
            return std::pow(x, e);
        }
        static T out(T x, T e) {
            return std::pow(x, 1 / e);
        }
        static T elasticInOut(T x, T e) {
            if (x == 0 || x == 1) {
                return x;
            }

            x *= 2;

            if (!e) {
                e = T{0.3} * T{1.5};
            }

            x -= 1;

            if (x < 0) {
                return -T{0.5} * std::pow(2, 10 * x) * std::sin((x - (e / 4)) * (std::numbers::pi_v<T> * 2) / e);
            }
            else {
                return std::pow(2, -10 * x) * std::sin((x - (e / 4)) * (std::numbers::pi_v<T> * 2) / e) * T{0.5} + 1;
            }
        }
        static T elasticIn(T x, T e) {
            if (x == 0 || x == 1) {
                return x;
            }

            if (!e) {
                e = T{0.3};
            }

            x -= 1;

            return -std::pow(2, 10 * x) * std::sin((x - (e / 4)) * (std::numbers::pi_v<T> * 2) / e);
        }
        static T elasticOut(T x, T e) {
            if (x == 0 || x == 1) {
                return x;
            }

            if (!e) {
                e = T{0.3};
            }

            return std::pow(2, -10 * x) * std::sin((x - (e / 4)) * (std::numbers::pi_v<T> * 2) / e) + 1;
        }
        static T bounceInOut(T x, T e) {
            if (x < 0.5f) {
                return (1 - bounceTime(1 - (x * 2))) * T{0.5};
            }
            else {
                return bounceTime(x * 2 - 1) * T{0.5} + T{0.5};
            }
        }
        static T bounceIn(T x, T e) {
            return 1 - bounceTime(1 - x);
        }
        static T bounceOut(T x, T e) {
            return bounceTime(x);
        }
        static T exponentialInOut(T x, T e) {
            if(!x || x == 1) {
                return x;
            }
            
            if (x < T{0.5}) {
                return T{0.5} * std::pow(2, 10 * (x * 2 - 1));
            }
            
            return T{0.5} * (-std::pow(2, -10 * (x * 2 - 1)) + 2);
        }
        static T exponentialIn(T x, T e) {
            if (!x || x == 1) {
                return x;
            }

            // ????? y cocos this seemse so pointless but ill do it anyway for the sake of parity
            return std::pow(2, 10 * (x - 1)) - T{0.001};
        }
        static T exponentialOut(T x, T e) {
            if (!x || x == 1) {
                return x;
            }
            
            return -std::pow(2, -10 * x) + 1;
        }
        static T sineInOut(T x, T e) {
            return -T{0.5} * (std::cos(std::numbers::pi_v<T> * x) - 1);
        }
        static T sineIn(T x, T e) {
            return -1 * std::cos(x * (std::numbers::pi_v<T> / 2)) + 1;
        }
        static T sineOut(T x, T e) {
            return std::sin(x * (std::numbers::pi_v<T> / 2));
        }
        static T backInOut(T x, T e) {
            constexpr auto overshoot = T{1.70158} * T{1.525};

            x *= 2;

            if (x < 1) {
                return (x * x * ((overshoot + 1) * x - overshoot)) / 2;
            }
            else {
                x -= 2;
                return (x * x * ((overshoot + 1) * x + overshoot)) / 2 + 1;
            }
        }
        static T backIn(T x, T e) {
            constexpr auto overshoot = T{1.70158};

            return x * x * ((overshoot + 1) * x - overshoot);
        }
        static T backOut(T x, T e) {
            constexpr auto overshoot = T{1.70158};

            x -= 1;

            return x * x * ((overshoot + 1) * x + overshoot) + 1;
        }
    };

    template<typename T>
    T ease(EasingType type, T x, T e = T{}) {
        switch (type) {
            case EasingType::None: return nwo5::utils::Easing<T>::linear(x, e);
            case EasingType::EaseIn: return nwo5::utils::Easing<T>::in(x, e);
            case EasingType::EaseOut: return nwo5::utils::Easing<T>::out(x, e);
            case EasingType::EaseInOut: return nwo5::utils::Easing<T>::inOut(x, e);
            case EasingType::ElasticInOut: return nwo5::utils::Easing<T>::elasticInOut(x, e);
            case EasingType::ElasticIn: return nwo5::utils::Easing<T>::elasticIn(x, e);
            case EasingType::ElasticOut: return nwo5::utils::Easing<T>::elasticOut(x, e);
            case EasingType::BounceInOut: return nwo5::utils::Easing<T>::bounceInOut(x, e);
            case EasingType::BounceIn: return nwo5::utils::Easing<T>::bounceIn(x, e);
            case EasingType::BounceOut: return nwo5::utils::Easing<T>::bounceOut(x, e);
            case EasingType::ExponentialInOut: return nwo5::utils::Easing<T>::exponentialInOut(x, e);
            case EasingType::ExponentialIn: return nwo5::utils::Easing<T>::exponentialIn(x, e);
            case EasingType::ExponentialOut: return nwo5::utils::Easing<T>::exponentialOut(x, e);
            case EasingType::SineInOut: return nwo5::utils::Easing<T>::sineInOut(x, e);
            case EasingType::SineIn: return nwo5::utils::Easing<T>::sineIn(x, e);
            case EasingType::SineOut: return nwo5::utils::Easing<T>::sineOut(x, e);
            case EasingType::BackInOut: return nwo5::utils::Easing<T>::backInOut(x, e);
            case EasingType::BackIn: return nwo5::utils::Easing<T>::backIn(x, e);
            case EasingType::BackOut: return nwo5::utils::Easing<T>::backOut(x, e);
            default: return T{};
        }
    }

    template<typename T>
    EasingFunction<T> getEasingFunction(EasingType type) {
        switch (type) {
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