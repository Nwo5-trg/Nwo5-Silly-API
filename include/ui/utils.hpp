#pragma once

#include "../export.hpp"
#include "setup.hpp"

namespace nwo5::ui {
    /// @returns content size of node
    SILLY_API_DLL cocos2d::CCPoint pos(cocos2d::CCNode* pNode);
    /// @returns x position of node
    SILLY_API_DLL float x(cocos2d::CCNode* pNode);
    /// @returns y position of node
    SILLY_API_DLL float y(cocos2d::CCNode* pNode);

    /// @returns content size of node
    SILLY_API_DLL cocos2d::CCSize size(cocos2d::CCNode* pNode);
    /// @returns content width of node
    SILLY_API_DLL float w(cocos2d::CCNode* pNode);
    /// @returns content height of node
    SILLY_API_DLL float h(cocos2d::CCNode* pNode);
    /// @returns scaled content size of node
    SILLY_API_DLL cocos2d::CCSize ssize(cocos2d::CCNode* pNode);
    /// @returns scaled content width of node
    SILLY_API_DLL float sw(cocos2d::CCNode* pNode);
    /// @returns scaled content height of node
    SILLY_API_DLL float sh(cocos2d::CCNode* pNode);

    SILLY_API_DLL cocos2d::CCSize winSize();
    SILLY_API_DLL float winWidth();
    SILLY_API_DLL float winHeight();

    template<typename T>
    auto node(Setup<T> pSetup) {
        return pSetup.get();
    }
}