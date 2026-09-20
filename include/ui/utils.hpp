#pragma once

#include "../export.hpp"

namespace nwo5::ui {
    SILLY_API_DLL cocos2d::CCSize winSize();
    SILLY_API_DLL float winWidth();
    SILLY_API_DLL float winHeight();

    // /// @returns pNode->boundingBox();
    // SILLY_API_DLL cocos2d::CCRect bounds(cocos2d::CCNode* pNode);
    // /// @returns pNode->boundingBox() but min/max for all the nodes
    // SILLY_API_DLL cocos2d::CCRect bounds(cocos2d::CCArray* pNodes);
    // /// @returns pNode->boundingBox() but min/max for all the nodes
    // SILLY_API_DLL cocos2d::CCRect bounds(std::span<const cocos2d::CCNode*> pNodes);
    // /// (try to) find a nodes bounds recursively
    // /// @param pExclude if a child node is in this span, exclude it
    // /// @returns bounds in node space
    // SILLY_API_DLL cocos2d::CCRect realBounds(cocos2d::CCNode* pNode, std::span<const cocos2d::CCNode*> pExclude = {});
    // /// (try to) find node(s) bounds recursively
    // /// @param pExclude if a child node is in this span, exclude it
    // /// @returns bounds in node space
    // SILLY_API_DLL cocos2d::CCRect realBounds(cocos2d::CCArray* pNodes, std::span<const cocos2d::CCNode*> pExclude = {});
    // /// (try to) find node(s) bounds recursively
    // /// @param pExclude if a child node is in this span, exclude it
    // /// @returns bounds in node space
    // SILLY_API_DLL cocos2d::CCRect realBounds(std::span<const cocos2d::CCNode*> pNodes, std::span<const cocos2d::CCNode*> pExclude = {});
}