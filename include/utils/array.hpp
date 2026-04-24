#pragma 

#include "../export.hpp"

namespace nwo5::utils::array {
    using ArrayIndex = unsigned int;

    SILLY_API_DLL cocos2d::CCArray* copy(cocos2d::CCArray* pArray);
    SILLY_API_DLL void clear(cocos2d::CCArray* pArray, bool pRelease = false);
    SILLY_API_DLL void remove(cocos2d::CCArray* pArray, cocos2d::CCArray* pOther, bool pRelease = false);
    SILLY_API_DLL cocos2d::CCArray* shared(cocos2d::CCArray* pArray, cocos2d::CCArray* pOther);
    SILLY_API_DLL std::optional<ArrayIndex> find(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj);
    template<typename Condition>
    std::optional<ArrayIndex> find(cocos2d::CCArray* pArray, Condition pCondition) {
        const auto size = pArray->count();

        for (ArrayIndex i = 0; i < size; i++) {
            if (pCondition(pArray->objectAtIndex(i))) {
                return i;
            }
        }

        return std::nullopt;
    }
    SILLY_API_DLL bool contains(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj);
    template<typename Condition>
    bool contains(cocos2d::CCArray* pArray, Condition pCondition) {
        return find(pArray, std::forward(pCondition)).has_value();
    }
    SILLY_API_DLL cocos2d::CCArray* before(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj, bool pInclusive = true);
    SILLY_API_DLL cocos2d::CCArray* before(cocos2d::CCArray* pArray, ArrayIndex pIndex, bool pInclusive = true);
    SILLY_API_DLL cocos2d::CCArray* after(cocos2d::CCArray* pArray, cocos2d::CCObject* pObj, bool pInclusive = true);
    SILLY_API_DLL cocos2d::CCArray* after(cocos2d::CCArray* pArray, ArrayIndex pIndex, bool pInclusive = true);
}