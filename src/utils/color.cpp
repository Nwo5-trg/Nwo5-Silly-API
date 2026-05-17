#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
    namespace impl {
        ccColor4F getChroma4F(float pSpeed, float pOffset, float pSaturation, float pValue) {
            const auto t = asp::time::SystemTime::now().timeSinceEpoch().seconds<double>();

            const auto rgba = impl::toRGB4F({
                static_cast<float>(std::fmod((std::fmod(t, pSpeed) / pSpeed) * 360 + pOffset, 360)), 
                pSaturation, pValue, 1.0f
            });

            return {
                static_cast<float>(rgba.r), static_cast<float>(rgba.g), static_cast<float>(rgba.b), 1.0f
            };
        }
    }
}