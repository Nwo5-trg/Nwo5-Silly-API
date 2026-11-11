#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
    size_t stringCount(std::string_view string, std::string_view substr) {
        size_t count = 0;

        for (auto i = string.find(substr); i != std::string::npos; i = string.find(substr, ++i)) {
            count++;
        }

        return count;
    }
    size_t stringCountIndependant(std::string_view string, std::string_view substr) {
        size_t count = 0;
        const auto size = substr.size();

        for (auto i = string.find(substr); i != std::string::npos; i = string.find(substr, i + size)) {
            count++;
        }

        return count;
    }
    size_t stringCount(std::string_view string, char substr) {
        return string::count(string, substr);
    }

    bool isToggled(CCObject* toggler) {
        return !static_cast<CCMenuItemToggler*>(toggler)->m_toggled;
    }
    void toggleWithCallback(CCObject* toggler, bool on) {
        auto node = static_cast<CCMenuItemToggler*>(toggler);
        
        node->m_toggled = !on;
        node->toggleWithCallback(on);
    }

    float getFontScaling(int font) {
        if (font == 0) {
            return 1.0f;
        }
        else if (font <= 59) {
            return 0.75f;
        }
        else if (font == 60) {
            return 1.75f;
        }
        else {
            return 1.0f;
        }
    }
    std::string getFontString(int font) {
        if (font == 0) {
            return "bigFont.fnt";
        }
        else if (font <= 59) {
            return fmt::format("gjFont{}{}.fnt", font < 10 ? "0" : "", font);
        } 
        else if (font == 60) {
            return "chatFont.fnt";
        } 
        else if (font == 61) {
            return "goldFont.fnt";
        }
        else {
            return "bigFont.fnt";
        }
    }

    CCTag* CCTag::create(int tag) {
        auto ret = new CCTag;

        ret->setTag(tag);

        ret->autorelease();

        return ret;
    }

    CCRect rectOverlap(const CCRect& a, const CCRect& b) {
        const CCPoint pointA{std::max(a.getMinX(), b.getMinX()), std::max(a.getMinY(), b.getMinY())};
        const CCPoint pointB{std::min(a.getMaxX(), b.getMaxX()), std::min(a.getMaxY(), b.getMaxY())};

        if (pointB.x > pointA.x && pointB.y > pointA.y) {
            return CCRect{pointA, pointB - pointA};
        }

        return CCRectZero;
    }
}