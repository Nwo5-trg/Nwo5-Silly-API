#pragma once

#include "../export.hpp"

namespace nwo5::utils::array {
    using ArrayIndex = unsigned int;

    SILLY_API_DLL cocos2d::CCArray* copy(cocos2d::CCArray* array);
    SILLY_API_DLL void clear(cocos2d::CCArray* array, bool release = false);
    SILLY_API_DLL void remove(cocos2d::CCArray* array, cocos2d::CCArray* other, bool release = false);
    SILLY_API_DLL cocos2d::CCArray* shared(cocos2d::CCArray* array, cocos2d::CCArray* other);
    SILLY_API_DLL std::optional<ArrayIndex> find(cocos2d::CCArray* array, cocos2d::CCObject* obj);
    template<typename ImplT = cocos2d::CCObject, typename T = std::remove_pointer_t<ImplT>, std::predicate<T*> Condition>
    std::optional<ArrayIndex> find(cocos2d::CCArray* array, Condition&& condition) {
        const auto size = array->count();

        for (ArrayIndex i = 0; i < size; i++) {
            if (condition(static_cast<T*>(array->objectAtIndex(i)))) {
                return i;
            }
        }

        return std::nullopt;
    }
    SILLY_API_DLL bool contains(cocos2d::CCArray* array, cocos2d::CCObject* obj);
    template<typename ImplT = cocos2d::CCObject, typename T = std::remove_pointer_t<ImplT>, std::predicate<T*> Condition>
    bool contains(cocos2d::CCArray* array, Condition&& condition) {
        return find(array, std::forward<Condition>(condition)).has_value();
    }
    SILLY_API_DLL cocos2d::CCArray* before(cocos2d::CCArray* array, cocos2d::CCObject* obj, bool inclusive = true);
    SILLY_API_DLL cocos2d::CCArray* before(cocos2d::CCArray* array, ArrayIndex index, bool inclusive = true);
    SILLY_API_DLL cocos2d::CCArray* after(cocos2d::CCArray* array, cocos2d::CCObject* obj, bool inclusive = true);
    SILLY_API_DLL cocos2d::CCArray* after(cocos2d::CCArray* array, ArrayIndex index, bool inclusive = true);
}