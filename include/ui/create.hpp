#pragma once

#include "constants.hpp"
#include "utils.hpp"

namespace nwo5::ui {
    template<typename ImplNode, typename Node = std::remove_pointer_t<ImplNode>>
    requires std::derived_from<Node, cocos2d::CCNode>
    class Create final {
    private:
        Node* m_node;

    public:
        using Type = Node;

        template<typename T>
        requires std::derived_from<T, Node>
        operator Node* const() const {
            return m_node;
        }

        auto get() const {
            return m_node;
        }
        auto data() const {
            return m_node;
        }

        Create parent(cocos2d::CCNode* pNode) requires std::derived_from<Node, cocos2d::CCNode> {
            pNode->addChild(m_node);
            return {m_node};
        }
        template<typename... Args>
        Create children(Args... pChildren) requires std::derived_from<Node, cocos2d::CCNode> {
            (m_node->addChild(pChildren), ...);

            if constexpr (std::derived_from<Node, cocos2d::CCMenu>) {
                m_node->updateLayout();
            }

            return {m_node};
        }

        Create pos(cocos2d::CCPoint pPos) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPosition(pPos);
            return {m_node};
        }
        Create pos(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos({pX, pY});
        }
        Create pos(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(pCopy->getPosition());
        }
        Create posX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionX(pX);
            return {m_node};
        }
        Create posX(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(pCopy->getPositionX());
        }
        Create posY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionY(pY);
            return {m_node};
        }
        Create posY(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(pCopy->getPositionY());
        }

        Create move(cocos2d::CCPoint pOffset) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(m_node->getPosition() + pOffset);
        }
        Create move(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return move({pX, pY});
        }
        Create moveX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(m_node->getPositionX() + pX);
        }
        Create moveY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(m_node->getPositionY() + pY);
        }

        Create above(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionAbove(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Create below(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionBelow(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Create right(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionRight(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Create left(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionLeft(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }

        Create center() {
            if (m_node->getParent()) {
                return pos(m_node->getParent()->getContentSize() / 2);
            }
            else {
                return pos(cocos2d::CCDirector::get()->getWinSize() / 2);
            }
        }

        Create anchor(cocos2d::CCPoint pAnchor) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setAnchorPoint(pAnchor);
            return {m_node};
        }
        Create anchor(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor({pX, pY});
        }
         Create anchor(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor(pCopy->getAnchorPoint());
        }

        Create rotation(float pRotation) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setRotation(pRotation);
            return {m_node};
        }
        Create rotation(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return rotation(pCopy->getRotation());
        }

        Create scale(float pScale) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScale(pScale);
                m_node->updateSprite();
            }
            else {
                m_node->setScale(pScale);
            }
            return {m_node};
        }
        Create scale(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scale(pCopy->getScale());
        }
        Create scale(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                auto image = m_node->getNormalImage();
                image->setScaleX(pX);
                image->setScaleY(pY);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleX(pX);
                m_node->setScaleY(pY);
            }
            return {m_node};
        }
        Create scaleX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleX(pX);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleX(pX);
            }
            return {m_node};
        }
        Create scaleX(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleX(pCopy->getScaleX());
        }
        Create scaleY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleY(pY);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleY(pY);
            }
            return {m_node};
        }
        Create scaleY(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleY(pCopy->getScaleY());
        }

        Create scaleToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight())) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Create scaleWidthToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto nodeSize = m_node->getContentSize();

            if (const auto origSize = m_node->getContentWidth()) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Create scaleHeightToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto nodeSize = m_node->getContentSize();

            if (const auto origSize = m_node->getContentHeight()) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Create limitScaleToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight());
            const auto origScale = std::max(m_node->getScaleX(), m_node->getScaleY());

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Create limitScaleWidthToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentWidth();
                const auto origScale = m_node->getScaleX();

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Create limitScaleHeightToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentHeight();
            const auto origScale = m_node->getScaleY();

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }

        Create size(cocos2d::CCSize pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize(pSize);
            return {m_node};
        }
        Create size(float pWidth, float pHeight) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize({pWidth, pHeight});
            return {m_node};
        }
        Create size(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return size(pCopy->getContentSize());
        }

        Create width(float pWidth) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentWidth(pWidth);
            return {m_node};
        }
        Create width(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return width(pCopy->getContentWidth());
        }
        Create height(float pHeight) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentHeight(pHeight);
            return {m_node};
        }
        Create height(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return height(pCopy->getContentHeight());
        }

        Create tag(int pTag) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setTag(pTag);
            return {m_node};
        }

        Create id(std::string_view pID) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setID(pID);
            return {m_node};
        }
        template <typename T, typename... Args>
        Create id(fmt::format_string<T, Args...> pFormat, T&& pArg, Args&&... pArgs) requires std::derived_from<T, cocos2d::CCNode> {
            m_node->setID(fmt::format(pFormat, std::forward<T>(pArg), std::forward<Args>(pArgs)...));
            return {m_node};
        }

        Create order(int pOrder) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(pOrder);
            return {m_node};
        }
        Create order(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(pCopy->getZOrder());
            return {m_node};
        }

        Create visible(bool pVisible) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(pVisible);
            return {m_node};
        }
        Create visible(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return visible(pCopy->isVisible());
        }
        Create hide() requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(false);
            return {m_node};
        }



        Create color(cocos2d::ccColor3B const& pColor) requires std::derived_from<Node, cocos2d::CCNodeRGBA> {
            m_node->setColor(pColor);
            return {m_node};
        }
        Create color(cocos2d::CCNodeRGBA* pCopy) requires std::derived_from<Node, cocos2d::CCNodeRGBA> {
            return color(pCopy->getColor());
        }
        Create opacity(unsigned char pOpacity) requires std::derived_from<Node, cocos2d::CCNodeRGBA> {
            m_node->setOpacity(pOpacity);
            return {m_node};
        }
        Create opacity(cocos2d::CCNodeRGBA* pCopy) requires std::derived_from<Node, cocos2d::CCNodeRGBA> {
            return opacity(pCopy->getOpacity());
        }



        Create flipX(bool pFlip) requires std::derived_from<Node, cocos2d::CCSprite> {
            m_node->setFlipX(pFlip);
            return {m_node};
        }
        Create flipY(bool pFlip) requires std::derived_from<Node, cocos2d::CCSprite> {
            m_node->setFlipY(pFlip);
            return {m_node};
        }


        
        Create layout(geode::Layout* pLayout) requires std::derived_from<Node, cocos2d::CCMenu> {
            m_node->setLayout(pLayout);
            return {m_node};
        }
        Create updateLayout() requires std::derived_from<Node, cocos2d::CCMenu> {
            m_node->updateLayout();
            return {m_node};
        }



        Create callback(cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pSelector) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            m_node->setTarget(pTarget, pSelector);
            return {m_node};
        }
        Create callback(geode::Function<void(Node*)> pCallback) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            geode::cocos::CCMenuItemExt::assignCallback(m_node, std::move(pCallback));
            return {m_node};
        }
        Create callback(TextInputCallback pCallback) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCallback(std::move(pCallback));
            return {m_node};
        }


        
        Create string(geode::ZStringView pString) requires requires { m_node->setString(""); } {
            m_node->setString(pString.c_str());
            return {m_node};
        }
        
        
        
        Create filter(geode::ZStringView pFilter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setFilter(pFilter);
            return {m_node};
        }
        Create filter(geode::CommonFilter pFilter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCommonFilter(pFilter);
            return {m_node};
        }
        Create maxCharCount(std::size_t pLength) requires std::derived_from<Node, geode::TextInput> {
            m_node->setMaxCharCount(pLength);
            return {m_node};
        }
        Create placeholder(geode::ZStringView pPlaceholder) requires std::derived_from<Node, geode::TextInput> {
            m_node->setPlaceholder(pPlaceholder);
            return {m_node};
        }
    };

    template<typename T>
    auto node(Create<T> pCreate) {
        return pCreate.get();
    }
}