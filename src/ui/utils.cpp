#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    cocos2d::CCSize winSize() {
        static auto director = CCDirector::get();
        return director->getWinSize();
    }
    float winWidth() {
        return winSize().width;
    }
    float winHeight() {
        return winSize().height;
    }

    // cocos2d::CCRect bounds(cocos2d::CCNode* pNode) {

    // }
    // cocos2d::CCRect bounds(cocos2d::CCArray* pNodes) {

    // }
    // cocos2d::CCRect bounds(std::span<const cocos2d::CCNode*> pNodes) {

    // }
    // cocos2d::CCRect realBounds(cocos2d::CCNode* pNode, std::span<const cocos2d::CCNode*> pExclude) {

    // }
    // cocos2d::CCRect realBounds(cocos2d::CCArray* pNodes, std::span<const cocos2d::CCNode*> pExclude) {

    // }
    // cocos2d::CCRect realBounds(std::span<const cocos2d::CCNode*> pNodes, std::span<const cocos2d::CCNode*> pExclude) {

    // }
    // CCRect nodesBounds(std::span<CCNode* const> pNodes) {
    //     if (pNodes.empty()) {
    //         return CCRectZero;
    //     }

    //     CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
    //     CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

    //     for (auto obj : pNodes) {
    //         const auto rect = obj->boundingBox();

    //         min.x = std::min(min.x, rect.origin.x);
    //         min.y = std::min(min.y, rect.origin.y);
    //         max.x = std::max(max.x, rect.origin.x + rect.size.width);
    //         max.y = std::max(max.y, rect.origin.y + rect.size.height);
    //     }

    //     return {min, {max.x - min.x, max.y - min.y}};
    // }
}