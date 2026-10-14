#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    CCPoint pos(CCNode* pNode) {
        return pNode ? pNode->getPosition() : CCPointZero;
    }
    float x(CCNode* pNode) {
        return pNode ? pNode->getPositionX() : 0.0f;
    }
    float y(CCNode* pNode) {
        return pNode ? pNode->getPositionY() : 0.0f;
    }

    CCSize size(CCNode* pNode) {
        return pNode ? pNode->getContentSize() : CCSizeZero;
    }
    float w(CCNode* pNode) {
        return pNode ? pNode->getContentWidth() : 0.0f;
    }
    float h(CCNode* pNode) {
        return pNode ? pNode->getContentHeight() : 0.0f;
    }
    CCSize ssize(CCNode* pNode) {
        return pNode ? pNode->getScaledContentSize() : CCSizeZero;
    }
    float sw(CCNode* pNode) {
        return pNode ? pNode->getScaledContentWidth() : 0.0f;
    }
    float sh(CCNode* pNode) {
        return pNode ? pNode->getScaledContentHeight() : 0.0f;
    }

    CCSize winSize() {
        static auto director = CCDirector::get();
        return director->getWinSize();
    }
    float winWidth() {
        return winSize().width;
    }
    float winHeight() {
        return winSize().height;
    }

    CCPoint anchor(CCNode* pNode) {
        return pNode ? pNode->getAnchorPoint() : CENTER_ANCHOR;
    }
}