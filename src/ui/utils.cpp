#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    void positionAbove(CCNode* pTarget, CCNode* pNode, float pGap, DirectionAlignment pAlignment) {
        const auto nodeRect = pNode->boundingBox();
        const auto targetRect = pTarget->boundingBox();

        const CCPoint nodePos = nodeRect.origin;
        CCPoint targetPos{0.0f, nodePos.y + nodeRect.size.height + pGap};

        if (pAlignment == DirectionAlignment::Start) {
            targetPos.x = nodePos.x;
        }
        else if (pAlignment == DirectionAlignment::End) {
            targetPos.x = nodePos.x + nodeRect.size.width - targetRect.size.width;
        }
        else {
            targetPos.x = nodePos.x + (nodeRect.size.width / 2) - (targetRect.size.width / 2);
        }

        pTarget->setPosition(targetPos + pTarget->getAnchorPoint() * targetRect.size);
    }
    void positionBelow(CCNode* pTarget, CCNode* pNode, float pGap, DirectionAlignment pAlignment) {
        const auto nodeRect = pNode->boundingBox();
        const auto targetRect = pTarget->boundingBox();

        const CCPoint nodePos = nodeRect.origin;
        CCPoint targetPos{0.0f, nodePos.y - targetRect.size.height - pGap};

        if (pAlignment == DirectionAlignment::Start) {
            targetPos.x = nodePos.x;
        }
        else if (pAlignment == DirectionAlignment::End) {
            targetPos.x = nodePos.x + nodeRect.size.width - targetRect.size.width;
        }
        else {
            targetPos.x = nodePos.x + (nodeRect.size.width / 2) - (targetRect.size.width / 2);
        }

        pTarget->setPosition(targetPos + pTarget->getAnchorPoint() * targetRect.size);
    }
    void positionRight(CCNode* pTarget, CCNode* pNode, float pGap, DirectionAlignment pAlignment) {
        const auto nodeRect = pNode->boundingBox();
        const auto targetRect = pTarget->boundingBox();

        const CCPoint nodePos = nodeRect.origin;
        CCPoint targetPos{nodePos.x + nodeRect.size.width + pGap, 0.0f};

        if (pAlignment == DirectionAlignment::Start) {
            targetPos.y = nodePos.y;
        }
        else if (pAlignment == DirectionAlignment::End) {
            targetPos.y = nodePos.y + nodeRect.size.height - targetRect.size.height;
        }
        else {
            targetPos.y = nodePos.y + (nodeRect.size.height / 2) - (targetRect.size.height / 2);
        }

        pTarget->setPosition(targetPos + pTarget->getAnchorPoint() * targetRect.size);
    }
    void positionLeft(CCNode* pTarget, CCNode* pNode, float pGap, DirectionAlignment pAlignment) {
        const auto nodeRect = pNode->boundingBox();
        const auto targetRect = pTarget->boundingBox();

        const CCPoint nodePos = nodeRect.origin;
        CCPoint targetPos{nodePos.x - targetRect.size.width - pGap, 0.0f};

        if (pAlignment == DirectionAlignment::Start) {
            targetPos.y = nodePos.y;
        }
        else if (pAlignment == DirectionAlignment::End) {
            targetPos.y = nodePos.y + nodeRect.size.height - targetRect.size.height;
        }
        else {
            targetPos.y = nodePos.y + (nodeRect.size.height / 2) - (targetRect.size.height / 2);
        }

        pTarget->setPosition(targetPos + pTarget->getAnchorPoint() * targetRect.size);
    }

    cocos2d::CCRect nodesBounds(cocos2d::CCArray* pNodes) {
        if (!pNodes || !pNodes->count()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<CCNode*>(pNodes)) {
            const auto rect = obj->boundingBox();

            min.x = std::min(min.x, rect.origin.x);
            min.y = std::min(min.y, rect.origin.y);
            max.x = std::max(max.x, rect.origin.x + rect.size.width);
            max.y = std::max(max.y, rect.origin.y + rect.size.height);
        }

        return {min, {max.x - min.x, max.y - min.y}};
    }
    cocos2d::CCRect nodesBounds(std::span<cocos2d::CCNode* const> pNodes) {
        if (pNodes.empty()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : pNodes) {
            const auto rect = obj->boundingBox();

            min.x = std::min(min.x, rect.origin.x);
            min.y = std::min(min.y, rect.origin.y);
            max.x = std::max(max.x, rect.origin.x + rect.size.width);
            max.y = std::max(max.y, rect.origin.y + rect.size.height);
        }

        return {min, {max.x - min.x, max.y - min.y}};
    }
    cocos2d::CCSize nodesSize(cocos2d::CCArray* pNodes) {
        return nodesBounds(pNodes).size;
    }
    cocos2d::CCSize nodesSize(std::span<cocos2d::CCNode* const> pNodes) {
        return nodesBounds(pNodes).size;
    }
}