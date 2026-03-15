#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    // murdering compile times to save typing like 5 characters per action :fire:

    struct SILLY_API_DLL NodeConfigBase {};
    struct SILLY_API_DLL SetNodePosition : NodeConfigBase {
        const cocos2d::CCPoint pos;

        SetNodePosition(cocos2d::CCPoint pPos)
            : pos(pPos) {}
        SetNodePosition(float pX, float pY)
            : pos(pX, pY) {}
        SetNodePosition(cocos2d::CCNode* pNode)
            : pos(pNode->getPosition()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPosition(pos);
        }
    };
    struct SILLY_API_DLL SetNodePositionX : NodeConfigBase {
        const float x;

        SetNodePositionX(float pX)
            : x(pX) {}
        SetNodePositionX(cocos2d::CCNode* pNode)
            : x(pNode->getPositionX()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPositionX(x);
        }
    };
    struct SILLY_API_DLL SetNodePositionY : NodeConfigBase {
        const float y;

        SetNodePositionY(float pY)
            : y(pY) {}
        SetNodePositionY(cocos2d::CCNode* pNode)
            : y(pNode->getPositionY()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPositionY(y);
        }
    };
    struct SILLY_API_DLL ChangeNodePosition : NodeConfigBase {
        const cocos2d::CCPoint off;

        ChangeNodePosition(cocos2d::CCPoint pOff)
            : off(pOff) {}
        ChangeNodePosition(float pX, float pY)
            : off(pX, pY) {}
        ChangeNodePosition(cocos2d::CCNode* pNode)
            : off(pNode->getPosition()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPosition(pNode->getPosition() + off);
        }
    };
    struct SILLY_API_DLL ChangeNodePositionX : NodeConfigBase {
        const float off;

        ChangeNodePositionX(float pOff)
            : off(pOff) {}
        ChangeNodePositionX(cocos2d::CCNode* pNode)
            : off(pNode->getPositionX()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPositionX(pNode->getPositionX() + off);
        }
    };
    struct SILLY_API_DLL ChangeNodePositionY : NodeConfigBase {
        const float off;

        ChangeNodePositionY(float pOff)
            : off(pOff) {}
        ChangeNodePositionY(cocos2d::CCNode* pNode)
            : off(pNode->getPositionX()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setPositionY(pNode->getPositionY() + off);
        }
    };
    struct SILLY_API_DLL SetNodeRotation : NodeConfigBase {
        const float rotation;

        SetNodeRotation(float pRotation)
            : rotation(pRotation) {}
        SetNodeRotation(cocos2d::CCNode* pNode)
            : rotation(pNode->getRotation()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setRotation(rotation);
        }
    };
    struct SILLY_API_DLL ChangeNodeRotation : NodeConfigBase {
        const float off;

        ChangeNodeRotation(float pOff)
            : off(pOff) {}
        ChangeNodeRotation(cocos2d::CCNode* pNode)
            : off(pNode->getRotation()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setRotation(pNode->getRotation() + off);
        }
    };
    struct SILLY_API_DLL SetNodeScale : NodeConfigBase {
        const bool xy;
        const cocos2d::CCSize scale;

        SetNodeScale(cocos2d::CCSize pScale)
            : scale(pScale), xy(true) {}
        SetNodeScale(float pW, float pH)
            : scale(pW, pH), xy(true) {}
        SetNodeScale(float pScale)
            : scale(pScale, pScale), xy(false) {}
        SetNodeScale(cocos2d::CCNode* pNode)
            : scale(pNode->getScaleX(), pNode->getScaleY()), xy(true) {}
        
        template<typename T>
        void apply(T* pNode) const {
            if (xy) {
                pNode->setScaleX(scale.width);
                pNode->setScaleY(scale.height);
            }
            else {
                pNode->setScale(scale.width);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeScaleX : NodeConfigBase {
        const float scale;

        SetNodeScaleX(float pScale)
            : scale(pScale) {}
        SetNodeScaleX(cocos2d::CCNode* pNode)
            : scale(pNode->getScaleX()) {}
        
        template<typename T>
        void apply(T* pNode) const {
            pNode->setScaleX(scale);

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeScaleY : NodeConfigBase {
        const float scale;

        SetNodeScaleY(float pScale)
            : scale(pScale) {}
        SetNodeScaleY(cocos2d::CCNode* pNode)
            : scale(pNode->getScaleY()) {}

        template<typename T>
        void apply(T* pNode) const {
            pNode->setScaleY(scale);

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL ChangeNodeScale : NodeConfigBase {
        const bool xy;
        const cocos2d::CCSize off;

        ChangeNodeScale(cocos2d::CCSize pOff)
            : off(pOff), xy(true) {}
        ChangeNodeScale(float pW, float pH)
            : off(pW, pH), xy(true) {}
        ChangeNodeScale(float pOff)
            : off(pOff, pOff), xy(false) {}
        ChangeNodeScale(cocos2d::CCNode* pNode)
            : off(pNode->getScaleX(), pNode->getScaleY()), xy(true) {}

        template<typename T>
        void apply(T* pNode) const {
            if (xy) {
                pNode->setScaleX(pNode->getScaleX() + off.width);
                pNode->setScaleY(pNode->getScaleY() + off.height);
            }
            else {
                pNode->setScale(pNode->getScale() + off.width);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL ChangeNodeScaleX : NodeConfigBase {
        const float off;

        ChangeNodeScaleX(float pOff)
            : off(pOff) {}
        ChangeNodeScaleX(cocos2d::CCNode* pNode)
            : off(pNode->getScaleX()) {}

        template<typename T>
        void apply(T* pNode) const {
            pNode->setScaleX(pNode->getScaleX() + off);

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL ChangeNodeScaleY : NodeConfigBase {
        const float off;

        ChangeNodeScaleY(float pOff)
            : off(pOff) {}
        ChangeNodeScaleY(cocos2d::CCNode* pNode)
            : off(pNode->getScaleY()) {}

        template<typename T>
        void apply(T* pNode) const {
            pNode->setScaleY(pNode->getScaleY() + off);

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeScaleWithSize : NodeConfigBase {
        const float size;
        const bool min;

        SetNodeScaleWithSize(float pSize, bool pMin = false)
            : size(pSize), min(pMin) {}

        template<typename T>
        void apply(T* pNode) const {
            const auto nodeSize = pNode->getContentSize();

            if (const auto origSize = min ? std::min(nodeSize.width, nodeSize.height) : std::max(nodeSize.width, nodeSize.height)) {
                pNode->setScale(size / origSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeScaleWithWidth : NodeConfigBase {
        const float width;

        SetNodeScaleWithWidth(float pSize)
            : width(pSize) {}

        template<typename T>
        void apply(T* pNode) const {
            if (const auto nodeSize = pNode->getContentWidth()) {
                pNode->setScale(width / nodeSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeScaleWithHeight : NodeConfigBase {
        const float height;

        SetNodeScaleWithHeight(float pSize)
            : height(pSize) {}
        template<typename T>
        void apply(T* pNode) const {
            if (const auto nodeSize = pNode->getContentHeight()) {
                pNode->setScale(height / nodeSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL LimitNodeScaleWithSize : NodeConfigBase {
        const float size;
        const bool min;

        LimitNodeScaleWithSize(float pSize, bool pMin = false)
            : size(pSize), min(pMin) {}

        template<typename T>
        void apply(T* pNode) const {
            const auto origSize = min 
                ? std::min(pNode->getContentWidth(), pNode->getContentHeight()) 
                : std::max(pNode->getContentWidth(), pNode->getContentHeight());
            const auto origScale = min 
                ? std::min(pNode->getScaleX(), pNode->getScaleY()) 
                : std::max(pNode->getScaleX(), pNode->getScaleY());
            
            if (origSize && origScale && origSize * origScale > size) {
                pNode->setScale(size / origSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL LimitNodeScaleWithWidth : NodeConfigBase {
        const float width;

        LimitNodeScaleWithWidth(float pWidth)
            : width(pWidth) {}

        template<typename T>
        void apply(T* pNode) const {
            const auto origSize = pNode->getContentWidth();
            const auto origScale = pNode->getScaleX();
            
            if (origSize && origScale && origSize * origScale > width) {
                pNode->setScale(width / origSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL LimitNodeScaleWithHeight : NodeConfigBase {
        const float height;

        LimitNodeScaleWithHeight(float pHeight)
            : height(pHeight) {}

        template<typename T>
        void apply(T* pNode) const {
            const auto origSize = pNode->getContentHeight();
            const auto origScale = pNode->getScaleY();
            
            if (origSize && origScale && origSize * origScale > height) {
                pNode->setScale(height / origSize);
            }

            if constexpr (std::derived_from<T, CCMenuItemSpriteExtra>) {
                pNode->m_baseScale = pNode->getScale();
            } 
        }
    };
    struct SILLY_API_DLL SetNodeSize : NodeConfigBase { 
        const cocos2d::CCSize size;

        SetNodeSize(cocos2d::CCSize pSize)
            : size(pSize) {}
        SetNodeSize(float pW, float pH)
            : size(pW, pH) {}
        SetNodeSize(cocos2d::CCNode* pNode)
            : size(pNode->getContentSize()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentSize(size);
        }
    };  
    struct SILLY_API_DLL SetNodeWidth : NodeConfigBase {
        const float width;

        SetNodeWidth(float pWidth)
            : width(pWidth) {}
        SetNodeWidth(cocos2d::CCNode* pNode)
            : width(pNode->getContentWidth()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentWidth(width);
        }
    };  
    struct SILLY_API_DLL SetNodeHeight : NodeConfigBase {
        const float height;

        SetNodeHeight(float pHeight)
            : height(pHeight) {}
        SetNodeHeight(cocos2d::CCNode* pNode)
            : height(pNode->getContentHeight()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentHeight(height);
        }
    }; 
    struct SILLY_API_DLL ChangeNodeSize : NodeConfigBase {
        const cocos2d::CCSize off;

        ChangeNodeSize(cocos2d::CCSize pOff)
            : off(pOff) {}
        ChangeNodeSize(float pW, float pH)
            : off(pW, pH) {}
        ChangeNodeSize(cocos2d::CCNode* pNode)
            : off(pNode->getContentSize()) {}

        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentSize(pNode->getContentSize() + off);
        }
    };
    struct SILLY_API_DLL ChangeNodeWidth : NodeConfigBase {
        const float off;

        ChangeNodeWidth(float pOff)
            : off(pOff) {}
        ChangeNodeWidth(cocos2d::CCNode* pNode)
            : off(pNode->getContentWidth()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentWidth(pNode->getContentWidth() + off);
        }
    };  
    struct SILLY_API_DLL ChangeNodeHeight : NodeConfigBase {
        const float off;

        ChangeNodeHeight(float pOff)
            : off(pOff) {}
        ChangeNodeHeight(cocos2d::CCNode* pNode)
            : off(pNode->getContentHeight()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setContentHeight(pNode->getContentHeight() + off);
        }
    }; 
    struct SILLY_API_DLL SetNodeAnchor : NodeConfigBase {
        const cocos2d::CCPoint anchor;

        SetNodeAnchor(cocos2d::CCPoint pAnchor)
            : anchor(pAnchor) {}
        SetNodeAnchor(float pX, float pY)
            : anchor(pX, pY) {}
        SetNodeAnchor(cocos2d::CCNode* pNode)
            : anchor(pNode->getAnchorPoint()) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setAnchorPoint(anchor);
        }
    };
    struct SILLY_API_DLL SetNodeChildren : NodeConfigBase {
        using ChildrenList = std::initializer_list<cocos2d::CCNode*>;

        const ChildrenList children;

        SetNodeChildren(ChildrenList pChildren)
            : children(pChildren) {}
        template<typename... Args>
        SetNodeChildren(Args... pArgs)
            : children(pArgs...) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            for (auto child : children) {
                pNode->addChild(child);
            }
        }
    };
    struct SILLY_API_DLL SetNodeParent : NodeConfigBase {
        cocos2d::CCNode* const parent;

        SetNodeParent(cocos2d::CCNode* pParent)
            : parent(pParent) {}

        void apply(cocos2d::CCNode* pNode) const {
            parent->addChild(pNode);
        }
    };
    struct SILLY_API_DLL SetNodeID : NodeConfigBase {
        const std::string id;

        SetNodeID(std::string_view pID)
            : id(pID) {}
        template <typename T, typename... Args>
        SetNodeID(fmt::format_string<T, Args...> pFormat, T&& pArg, Args&&... pArgs)
            : id(fmt::format(pFormat, std::forward<T>(pArg), std::forward<Args>(pArgs)...)) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setID(id);
        }
    };
    struct SILLY_API_DLL SetNodeTag : NodeConfigBase {
        const int tag;

        SetNodeTag(int pTag)
            : tag(pTag) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setTag(tag);
        }
    };
    struct SILLY_API_DLL SetNodeOrder : NodeConfigBase {
        const int order;

        SetNodeOrder(int pOrder)
            : order(pOrder) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setZOrder(order);
        }
    };
    struct SILLY_API_DLL SetNodeVisibility: NodeConfigBase {
        const bool visible;

        SetNodeVisibility(bool pVisible)
            : visible(pVisible) {}
        
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setVisible(visible);
        }
    };
    struct SILLY_API_DLL SetNodeInvisible : NodeConfigBase {
        void apply(cocos2d::CCNode* pNode) const {
            pNode->setVisible(false);
        }
    };
    struct SILLY_API_DLL SetNodeColor: NodeConfigBase {
        const cocos2d::ccColor3B color;

        SetNodeColor(cocos2d::ccColor3B pColor)
            : color(pColor) {}
        SetNodeColor(cocos2d::CCNodeRGBA* pNode)
            : color(pNode->getColor()) {}
        
        template<typename T>
        void apply(T* pNode) const {
            pNode->setColor(color);
        }
    };
    struct SILLY_API_DLL SetNodeOpacity: NodeConfigBase {
        const unsigned char opacity;

        SetNodeOpacity(unsigned char pOpacity)
            : opacity(pOpacity) {}
        SetNodeOpacity(cocos2d::CCNodeRGBA* pNode)
            : opacity(pNode->getOpacity()) {}
        
        template<typename T>
        void apply(T* pNode) const {
            pNode->setOpacity(opacity);
        }
    };

    template<typename T, typename Base = std::remove_pointer_t<T>, typename... Args>
    requires std::is_pointer_v<T> && std::derived_from<Base, cocos2d::CCNode> && (std::derived_from<Args, NodeConfigBase> && ...)
    T setupNode(T pNode, Args... pArgs) {
        if (!pNode) {
            return nullptr;
        }

        ([&] {
            pArgs.apply(pNode);
        }(), ...);

        return pNode;
    }
}