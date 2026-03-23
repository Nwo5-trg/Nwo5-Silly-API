#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
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

    void removeAllObjects(CCArray* pArray, bool pRelease) {
        while (pArray->count()) {
            pArray->removeLastObject(pRelease);
        }
    }
    void removeObjectsFromArray(CCArray* pArray, CCArray* pOther, bool pRelease) {
        for (auto obj : pOther->asExt()) {
            pArray->removeObject(obj, pRelease);
        }
    }
    CCArray* sharedObjects(CCArray* pArray, CCArray* pOther) {
        const auto size = std::max(pArray->count(), pOther->count());

        if (!size) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(std::max(pArray->count(), pOther->count()));

        for (auto obj : pOther->asExt()) {
            if (pArray->containsObject(obj)) {
                out->addObject(obj);
            }
        }

        return out;
    }
    std::optional<unsigned int> findObject(CCArray* pArray, CCObject* pObj) {
        const auto find = pArray->indexOfObject(pObj);

        if (find == UINT_MAX) {
            return std::nullopt;
        }
        else {
            return find;
        }
    }
    CCArray* objectsBefore(CCArray* pArray, CCObject* pObj, bool pInclusive) {
        const auto find = pArray->indexOfObject(pObj);

        if (find == UINT_MAX) {
            return CCArray::createWithArray(pArray);
        }

        const auto pos = pInclusive ? find : find - 1;

        if (pos == UINT_MAX) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(pos + 1);

        for (int i = 0; i <= pos; i++) {
            out->addObject(pArray->objectAtIndex(i));
        }

        return out;
    }
    CCArray* objectsAfter(CCArray* pArray, CCObject* pObj, bool pInclusive) {
        const auto find = pArray->indexOfObject(pObj);

        if (find == UINT_MAX) {
            return CCArray::createWithArray(pArray);
        }

        const auto pos = pInclusive ? find : find + 1;
        const auto count = pArray->count();

        if (pos == count) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(count - pos);

        for (int i = pos; i < count; i++) {
            out->addObject(pArray->objectAtIndex(i));
        }

        return out;
    }
}