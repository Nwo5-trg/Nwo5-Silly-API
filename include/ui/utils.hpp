#pragma once

#include "../export.hpp"
#include "setup.hpp"

namespace nwo5::ui {
    /// @returns pos of node
    inline cocos2d::CCPoint pos(cocos2d::CCNode* node) {
        return node ? node->getPosition() : cocos2d::CCPointZero;
    }
    /// @returns x pos of node
    inline float x(cocos2d::CCNode* node) {
        return node ? node->getPositionX() : 0.0f;
    }
    /// @returns y pos of node
    inline float y(cocos2d::CCNode* node) {
        return node ? node->getPositionY() : 0.0f;
    }

    /// @returns content size of node
    inline cocos2d::CCSize size(cocos2d::CCNode* node) {
        return node ? node->getContentSize() : cocos2d::CCSizeZero;
    }
    /// @returns content width of node
    inline float w(cocos2d::CCNode* node) {
        return node ? node->getContentWidth() : 0.0f;
    }
    /// @returns content height of node
    inline float h(cocos2d::CCNode* node) {
        return node ? node->getContentHeight() : 0.0f;
    }
    /// @returns scaled content size of node
    inline cocos2d::CCSize ssize(cocos2d::CCNode* node) {
        return node ? node->getScaledContentSize() : cocos2d::CCSizeZero;
    }
    /// @returns scaled content width of node
    inline float sw(cocos2d::CCNode* node) {
        return node ? node->getScaledContentWidth() : 0.0f;
    }
    /// @returns scaled content height of node
    inline float sh(cocos2d::CCNode* node) {
        return node ? node->getScaledContentHeight() : 0.0f;
    }

    inline cocos2d::CCPoint top(cocos2d::CCNode* node) {
        return {x(node), y(node) + sh(node) / 2};
    }
    inline cocos2d::CCPoint bottom(cocos2d::CCNode* node) {
        return {x(node), y(node) - sh(node) / 2};
    }
    inline cocos2d::CCPoint right(cocos2d::CCNode* node) {
        return {x(node) + sw(node) / 2, y(node)};
    }
    inline cocos2d::CCPoint left(cocos2d::CCNode* node) {
        return {x(node) - sw(node) / 2, y(node)};
    }
    inline cocos2d::CCPoint topRight(cocos2d::CCNode* node) {
        return {x(node) + sw(node) / 2, y(node) + sh(node) / 2};
    }
    inline cocos2d::CCPoint topLeft(cocos2d::CCNode* node) {
        return {x(node) - sw(node) / 2, y(node) + sh(node) / 2};
    }
    inline cocos2d::CCPoint bottomRight(cocos2d::CCNode* node) {
        return {x(node) + sw(node) / 2, y(node) - sh(node) / 2};
    }
    inline cocos2d::CCPoint bottomLeft(cocos2d::CCNode* node) {
        return {x(node) - sw(node) / 2, y(node) - sh(node) / 2};
    }

    inline cocos2d::CCPoint mid(cocos2d::CCNode* node, cocos2d::CCNode* otherNode) {
        return (pos(node) + pos(otherNode)) / 2;
    }
    inline float midX(cocos2d::CCNode* node, cocos2d::CCNode* otherNode) {
        return (x(node) + x(otherNode)) / 2;
    }
    inline float midY(cocos2d::CCNode* node, cocos2d::CCNode* otherNode) {
        return (y(node) + y(otherNode)) / 2;
    }

    inline cocos2d::CCSize winSize() {
        static auto director = cocos2d::CCDirector::get();
        return director->getWinSize();
    }
    inline float winWidth() {
        return winSize().width;
    }
    inline float winHeight() {
        return winSize().height;
    }

    template<typename T>
    auto node(Setup<T> setup) {
        return setup.get();
    }
}