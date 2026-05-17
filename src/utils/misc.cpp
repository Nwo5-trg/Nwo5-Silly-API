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
}