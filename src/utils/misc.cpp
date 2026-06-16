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

    float getFontScaling(int pFont) {
        if (pFont == 0) {
            return 1.0f;
        }
        else if (pFont <= 59) {
            return 0.75f;
        }
        else if (pFont == 60) {
            return 1.75f;
        }
        else {
            return 1.0f;
        }
    }
    std::string getFontString(int pFont) {
        if (pFont == 0) {
            return "bigFont.fnt";
        }
        else if (pFont <= 59) {
            return fmt::format("gjFont{}{}.fnt", pFont < 10 ? "0" : "", pFont);
        } 
        else if (pFont == 60) {
            return "chatFont.fnt";
        } 
        else if (pFont == 61) {
            return "goldFont.fnt";
        }
        else {
            return "bigFont.fnt";
        }
    }

    CCTag* CCTag::create(int pTag) {
        auto ret = new CCTag;

        ret->setTag(pTag);

        ret->autorelease();

        return ret;
    }
}