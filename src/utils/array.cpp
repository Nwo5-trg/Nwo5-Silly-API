#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils::array {
    cocos2d::CCArray* copy(cocos2d::CCArray* array) {
        auto out = CCArray::createWithCapacity(array->capacity());

        for (auto obj : array->asExt()) {
            out->addObject(obj);
        }

        return out;
    }
    void clear(CCArray* array, bool release) {
        while (array->count()) {
            array->removeLastObject(release);
        }
    }
    void remove(CCArray* array, CCArray* other, bool release) {
        for (auto obj : other->asExt()) {
            array->removeObject(obj, release);
        }
    }
    CCArray* shared(CCArray* array, CCArray* other) {
        const auto size = std::max(array->count(), other->count());

        if (!size) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(std::max(array->count(), other->count()));

        for (auto obj : other->asExt()) {
            if (array->containsObject(obj)) {
                out->addObject(obj);
            }
        }

        return out;
    }
    std::optional<unsigned int> find(CCArray* array, CCObject* obj) {
        const auto find = array->indexOfObject(obj);

        if (find == UINT_MAX) {
            return std::nullopt;
        }
        else {
            return find;
        }
    }
    bool contains(cocos2d::CCArray* array, cocos2d::CCObject* obj) {
        return find(array, obj).has_value();
    }
    CCArray* before(CCArray* array, CCObject* obj, bool inclusive) {
        const auto find = array->indexOfObject(obj);

        if (find == UINT_MAX) {
            return copy(array);
        }

        const auto pos = inclusive ? find : find - 1;

        if (pos == UINT_MAX) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(pos + 1);

        for (int i = 0; i <= pos; i++) {
            out->addObject(array->objectAtIndex(i));
        }

        return out;
    }
    CCArray* before(CCArray* array, unsigned int index, bool inclusive) {
        if (index >= array->count()) {
            return copy(array);
        }

        const auto pos = inclusive ? index : index - 1;

        if (pos == UINT_MAX) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(pos + 1);

        for (int i = 0; i <= pos; i++) {
            out->addObject(array->objectAtIndex(i));
        }

        return out;
    }
    CCArray* after(CCArray* array, CCObject* obj, bool inclusive) {
        const auto find = array->indexOfObject(obj);

        if (find == UINT_MAX) {
            return copy(array);
        }

        const auto pos = inclusive ? find : find + 1;
        const auto count = array->count();

        if (pos == count) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(count - pos);

        for (int i = pos; i < count; i++) {
            out->addObject(array->objectAtIndex(i));
        }

        return out;
    }
    CCArray* after(CCArray* array, unsigned int index, bool inclusive) {
        const auto pos = inclusive ? index : index + 1;
        const auto count = array->count();

        if (pos >= count) {
            return CCArray::create();
        }

        auto out = CCArray::createWithCapacity(count - pos);

        for (int i = pos; i < count; i++) {
            out->addObject(array->objectAtIndex(i));
        }

        return out;
    }
}