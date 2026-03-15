#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
    size_t stringCount(std::string_view pString, std::string_view pSubstr) {
        size_t count = 0;
        const auto size = pSubstr.size();

        for (auto i = pString.find(pSubstr); i != std::string::npos; i = pString.find(pSubstr, i + size)) {
            count++;
        }

        return count;
    }
    size_t stringCount(std::string_view pString, char pSubstr) {
        return std::ranges::count(pString, pSubstr);
    }

    bool isToggled(CCObject* pToggler) {
        return !static_cast<CCMenuItemToggler*>(pToggler)->m_toggled;
    }

    namespace impl {
        ccColor4F getChroma4F(double pOffset, double pSpeed) {
            const auto t = asp::time::SystemTime::now().timeSinceEpoch().seconds<double>();

            const auto rgba = cocos2d::extension::CCControlUtils::RGBfromHSV({
                // not sure if cocos handles hue higher than 360 well so
                std::fmod((std::fmod(t, pSpeed) / pSpeed) * 360 + pOffset, 360), 1.0, 1.0
            });

            return {
                static_cast<float>(rgba.r), static_cast<float>(rgba.g), static_cast<float>(rgba.b), 1.0f
            };
        }
    }
}