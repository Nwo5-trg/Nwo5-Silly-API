#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
    size_t stringCount(std::string_view pString, std::string_view pSubstr) {
        size_t count = 0;

        for (auto i = pString.find(pSubstr); i != std::string::npos; i = pString.find(pSubstr, ++i)) {
            count++;
        }

        return count;
    }
    size_t stringCountIndependant(std::string_view pString, std::string_view pSubstr) {
        size_t count = 0;
        const auto size = pSubstr.size();

        for (auto i = pString.find(pSubstr); i != std::string::npos; i = pString.find(pSubstr, i + size)) {
            count++;
        }

        return count;
    }
    size_t stringCount(std::string_view pString, char pSubstr) {
        return string::count(pString, pSubstr);
    }

    bool isToggled(CCObject* pToggler) {
        return !static_cast<CCMenuItemToggler*>(pToggler)->m_toggled;
    }
    void toggleWithCallback(CCObject* pToggler, bool pOn) {
        auto toggler = static_cast<CCMenuItemToggler*>(pToggler);
        
        toggler->m_toggled = !pOn;
        toggler->toggleWithCallback(pOn);
    }

    CCTag* CCTag::create(int pTag) {
        auto ret = new CCTag;

        ret->setTag(pTag);

        ret->autorelease();

        return ret;
    }

    namespace impl {
        ccColor4F getChroma4F(float pSpeed, float pOffset, float pSaturation, float pValue) {
            const auto t = asp::time::SystemTime::now().timeSinceEpoch().seconds<double>();

            const auto rgba = extension::CCControlUtils::RGBfromHSV({
                std::fmod((std::fmod(t, pSpeed) / pSpeed) * 360 + pOffset, 360), pSaturation, pValue
            });

            return {
                static_cast<float>(rgba.r), static_cast<float>(rgba.g), static_cast<float>(rgba.b), 1.0f
            };
        }
    }
}