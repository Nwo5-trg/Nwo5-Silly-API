#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils::array {
    cocos2d::CCArray* copy(cocos2d::CCArray* pArray) {
        auto out = CCArray::createWithCapacity(pArray->capacity());

        for (auto obj : pArray->asExt()) {
            out->addObject(obj);
        }

        return out;
    }
    void clear(CCArray* pArray, bool pRelease) {
        while (pArray->count()) {
            pArray->removeLastObject(pRelease);
        }
    }
    void remove(CCArray* pArray, CCArray* pOther, bool pRelease) {
        for (auto obj : pOther->asExt()) {
            pArray->removeObject(obj, pRelease);
        }
    }
    CCArray* shared(CCArray* pArray, CCArray* pOther) {
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
    std::optional<unsigned int> find(CCArray* pArray, CCObject* pObj) {
        const auto find = pArray->indexOfObject(pObj);

        if (find == UINT_MAX) {
            return std::nullopt;
        }
        else {
            return find;
        }
    }
    bool contains(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj) {
        return find(pArray, pObj).has_value();
    }
    CCArray* before(CCArray* pArray, CCObject* pObj, bool pInclusive) {
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
    CCArray* before(CCArray* pArray, unsigned int pIndex, bool pInclusive) {
        if (pIndex >= pArray->count()) {
            return CCArray::createWithArray(pArray);
        }

        const auto pos = pInclusive ? pIndex : pIndex - 1;

        if (pos == UINT_MAX) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(pos + 1);

        for (int i = 0; i <= pos; i++) {
            out->addObject(pArray->objectAtIndex(i));
        }

        return out;
    }
    CCArray* after(CCArray* pArray, CCObject* pObj, bool pInclusive) {
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
    CCArray* after(CCArray* pArray, unsigned int pIndex, bool pInclusive) {
        const auto pos = pInclusive ? pIndex : pIndex + 1;
        const auto count = pArray->count();

        if (pos >= count) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(count - pos);

        for (int i = pos; i < count; i++) {
            out->addObject(pArray->objectAtIndex(i));
        }

        return out;
    }
}