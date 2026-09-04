#pragma once

#include "../export.hpp"

namespace nwo5::ui {
    SILLY_API_DLL cocos2d::CCRect nodesBounds(cocos2d::CCArray* pNodes);
    SILLY_API_DLL cocos2d::CCRect nodesBounds(std::span<cocos2d::CCNode* const> pNodes);
    template<typename... Args>
    cocos2d::CCRect nodesBounds(Args... pArgs) {
        return nodesBounds(geode::cocos::CCArrayExt(pArgs...).inner());
    } 
    SILLY_API_DLL cocos2d::CCSize nodesSize(cocos2d::CCArray* pNodes);
    SILLY_API_DLL cocos2d::CCSize nodesSize(std::span<cocos2d::CCNode* const> pNodes);
    template<typename... Args>
    cocos2d::CCSize nodesSize(Args... pArgs) {
        return nodesSize(geode::cocos::CCArrayExt(pArgs...).inner());
    } 
}