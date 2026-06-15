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

    void getFontScaling(int pStr) {
        if (labelFont == 0) {
            return 1.0f;
        }
        else if (labelFont <= 59) {
            return 0.75f;
        }
        else if (labelFont == 60) {
            return 1.75f;
        }
        else if (labelFont == 61) {
            return 1.0f;
        }
    }
    std::string getFontString(int pFont) {
        if (labelFont == 0) {
            return "bigFont.fnt";
        }
        else if (labelFont <= 59) {
            return fmt::format("gjFont{}{}.fnt", labelFont < 10 ? "0" : "", labelFont);
        } 
        else if (labelFont == 60) {
            return "chatFont.fnt";
        } 
        else if (labelFont == 61) {
            return "goldFont.fnt";
        }
    }

    CCTag* CCTag::create(int pTag) {
        auto ret = new CCTag;

        ret->setTag(pTag);

        ret->autorelease();

        return ret;
    }
}