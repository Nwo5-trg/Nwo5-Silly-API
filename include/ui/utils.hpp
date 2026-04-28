#pragma once

#include "../export.hpp"

namespace nwo5::ui {
    enum class DirectionAlignment {
        Start,
        Center,
        End
    };

    SILLY_API_DLL void positionAbove(cocos2d::CCNode* pTarget, cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center);
    SILLY_API_DLL void positionBelow(cocos2d::CCNode* pTarget, cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center);
    SILLY_API_DLL void positionRight(cocos2d::CCNode* pTarget, cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center);
    SILLY_API_DLL void positionLeft(cocos2d::CCNode* pTarget, cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center);

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