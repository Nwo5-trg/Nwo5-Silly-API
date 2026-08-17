#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    CCPoint pos(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getPosition() : CCPointZero;
    }
    float x(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getPositionX() : 0.0f;
    }
    float y(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getPositionY() : 0.0f;
    }

    CCSize size(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getContentSize() : CCSizeZero;
    }
    float w(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getContentWidth() : 0.0f;
    }
    float h(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getContentHeight() : 0.0f;
    }
    CCSize ssize(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScaledContentSize() : CCSizeZero;
    }
    float sw(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScaledContentWidth() : 0.0f;
    }
    float sh(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScaledContentHeight() : 0.0f;
    }

    float scale(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScale() : 1.0f;
    }
    float sx(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScaleX() : 1.0f;
    }
    float sy(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getScaleY() : 1.0f;
    }

    CCPoint anchor(cocos2d::CCNode* pNode) {
        return pNode ? pNode->getAnchorPoint() : CENTER_ANCHOR;
    }
}