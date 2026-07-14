#pragma once

#include <Geode/ui/Button.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <Geode/ui/SliderNode.hpp>
#include "constants.hpp"
#include "utils.hpp"

namespace nwo5::ui {
    template<typename ImplNode, typename Node = std::remove_pointer_t<ImplNode>>
    requires std::derived_from<Node, cocos2d::CCNode>
    class Setup final {
    private:
        Node* m_node;

    public:
        using Type = Node;

        Setup(Node* node) 
            : m_node(node) {}

        operator Node*() const {
            return m_node;
        }

        auto get() const {
            return m_node;
        }
        auto data() const {
            return m_node;
        }

        Setup parent(cocos2d::CCNode* pNode) requires std::derived_from<Node, cocos2d::CCNode> {
            pNode->addChild(m_node);

            if (auto menu = geode::cast::typeinfo_cast<cocos2d::CCMenu*>(pNode); menu && menu->getLayout()) {
                menu->updateLayout();
            }

            return {m_node};
        }
        template<typename... Args>
        Setup children(Args... pChildren) requires std::derived_from<Node, cocos2d::CCNode> {
            (m_node->addChild(pChildren), ...);

            if constexpr (std::derived_from<Node, cocos2d::CCMenu>) {
                m_node->updateLayout();
            }

            return {m_node};
        }

        Setup pos(cocos2d::CCPoint pPos) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPosition(pPos);
            return {m_node};
        }
        Setup pos(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos({pX, pY});
        }
        Setup pos(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(pCopy->getPosition());
        }
        Setup posX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionX(pX);
            return {m_node};
        }
        Setup posX(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(pCopy->getPositionX());
        }
        Setup posY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionY(pY);
            return {m_node};
        }
        Setup posY(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(pCopy->getPositionY());
        }

        Setup move(cocos2d::CCPoint pOffset) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(m_node->getPosition() + pOffset);
        }
        Setup move(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return move({pX, pY});
        }
        Setup moveX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(m_node->getPositionX() + pX);
        }
        Setup moveY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(m_node->getPositionY() + pY);
        }

        Setup above(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionAbove(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Setup below(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionBelow(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Setup right(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionRight(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }
        Setup left(cocos2d::CCNode* pNode, float pGap = 0.0f, DirectionAlignment pAlignment = DirectionAlignment::Center) requires std::derived_from<Node, cocos2d::CCNode> {
            nwo5::ui::positionLeft(m_node, pNode, pGap, pAlignment);
            return {m_node};
        }

        Setup center() {
            if (m_node->getParent()) {
                return pos(m_node->getParent()->getContentSize() / 2);
            }
            else {
                return pos(cocos2d::CCDirector::get()->getWinSize() / 2);
            }
        }

        Setup anchor(cocos2d::CCPoint pAnchor) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setAnchorPoint(pAnchor);

            if constexpr (std::derived_from<Node, cocos2d::CCLayer> || std::derived_from<Node, cocos2d::CCMenu>) {
                m_node->ignoreAnchorPointForPosition(false);
            }

            return {m_node};
        }
        Setup anchor(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor({pX, pY});
        }
        Setup anchor(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor(pCopy->getAnchorPoint());
        }

        Setup ignoreAnchorForPos(bool pIgnore) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->ignoreAnchorPointForPosition(pIgnore);
            return {m_node};
        }

        Setup rotation(float pRotation) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setRotation(pRotation);
            return {m_node};
        }
        Setup rotation(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return rotation(pCopy->getRotation());
        }

        Setup scale(float pScale) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScale(pScale);
                m_node->updateSprite();
            }
            else {
                m_node->setScale(pScale);
            }
            return {m_node};
        }
        Setup scale(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scale(pCopy->getScale());
        }
        Setup scale(float pX, float pY) requires std::derived_from<Node, cocos2d::CCNode> {
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
        Setup scaleX(float pX) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleX(pX);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleX(pX);
            }
            return {m_node};
        }
        Setup scaleX(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleX(pCopy->getScaleX());
        }
        Setup scaleY(float pY) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleY(pY);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleY(pY);
            }
            return {m_node};
        }
        Setup scaleY(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleY(pCopy->getScaleY());
        }

        Setup scaleToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight())) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Setup scaleWidthToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto nodeSize = m_node->getContentSize();

            if (const auto origSize = m_node->getContentWidth()) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Setup scaleHeightToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto nodeSize = m_node->getContentSize();

            if (const auto origSize = m_node->getContentHeight()) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Setup limitScaleToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight());
            const auto origScale = std::max(m_node->getScaleX(), m_node->getScaleY());

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Setup limitScaleWidthToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentWidth();
                const auto origScale = m_node->getScaleX();

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }
        Setup limitScaleHeightToFit(float pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentHeight();
            const auto origScale = m_node->getScaleY();

            if (origSize && origScale && origSize * origScale > pSize) {
                return scale(pSize / origSize);
            }
            else {
                return {m_node};
            }
        }

        Setup size(cocos2d::CCSize pSize) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize(pSize);
            return {m_node};
        }
        Setup size(float pWidth, float pHeight) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize({pWidth, pHeight});
            return {m_node};
        }
        Setup size(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return size(pCopy->getContentSize());
        }

        Setup width(float pWidth) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentWidth(pWidth);
            return {m_node};
        }
        Setup width(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return width(pCopy->getContentWidth());
        }
        Setup height(float pHeight) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentHeight(pHeight);
            return {m_node};
        }
        Setup height(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return height(pCopy->getContentHeight());
        }

        Setup tag(int pTag) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setTag(pTag);
            return {m_node};
        }

        Setup id(std::string pID) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setID(pID);
            return {m_node};
        }
        template <typename T, typename... Args>
        Setup id(fmt::format_string<T, Args...> pFormat, T&& pArg, Args&&... pArgs) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setID(fmt::format(pFormat, std::forward<T>(pArg), std::forward<Args>(pArgs)...));
            return {m_node};
        }

        Setup order(int pOrder) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(pOrder);
            return {m_node};
        }
        Setup order(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(pCopy->getZOrder());
            return {m_node};
        }

        Setup visible(bool pVisible) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(pVisible);
            return {m_node};
        }
        Setup visible(cocos2d::CCNode* pCopy) requires std::derived_from<Node, cocos2d::CCNode> {
            return visible(pCopy->isVisible());
        }
        Setup hide() requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(false);
            return {m_node};
        }



        Setup flipX(bool pFlip = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                m_node->setFlipX(pFlip);
            }
            else {
                m_node->setRotationY(pFlip ? 180.0f : 0.0f);
            }
            return {m_node};
        }
        Setup flipY(bool pFlip = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                m_node->setFlipY(pFlip);
            }
            else {
                m_node->setRotationX(pFlip ? 180.0f : 0.0f);
            }
            return {m_node};
        }



        Setup color(cocos2d::ccColor3B const& pColor) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            m_node->setColor(pColor);
            return {m_node};
        }
        Setup color(Node* pCopy) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            return color(pCopy->getColor());
        }
        Setup opacity(unsigned char pOpacity) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            m_node->setOpacity(pOpacity);
            return {m_node};
        }
        Setup opacity(Node* pCopy) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            return opacity(pCopy->getOpacity());
        }


        
        Setup layout(geode::Layout* pLayout) requires std::derived_from<Node, cocos2d::CCMenu> {
            m_node->setLayout(pLayout);
            return {m_node};
        }
        Setup updateLayout() requires std::derived_from<Node, cocos2d::CCMenu> {
            m_node->updateLayout();
            return {m_node};
        }



        Setup callback(cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pSelector) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            m_node->setTarget(pTarget, pSelector);
            return {m_node};
        }
        Setup callback(geode::Function<void(Node*)> pCallback) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            geode::cocos::CCMenuItemExt::assignCallback(m_node, std::move(pCallback));
            return {m_node};
        }
        Setup callback(TextInputCallback pCallback) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCallback(std::move(pCallback));
            return {m_node};
        }
        Setup callback(geode::Button::ButtonCallback pCallback) requires std::derived_from<Node, geode::Button> {
            m_node->setActivateCallback(std::move(pCallback));
            return {m_node};
        }
        Setup callback(geode::LazySprite::Callback pCallback) requires std::derived_from<Node, geode::LazySprite> {
            m_node->setLoadCallback(pCallback);
            return {m_node};
        }
        Setup callback(geode::SliderNode::SliderCallback pCallback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setSlideCallback(pCallback);
            return {m_node};
        }

        Setup callback(bool pEnabled) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCallbackEnabled(pEnabled);
            return {m_node};
        }

        Setup callbackHold(geode::Button::ButtonCallback pCallback) requires std::derived_from<Node, geode::Button> {
            m_node->setSelectCallback(std::move(pCallback));
            return {m_node};
        }
        Setup callbackHold(geode::SliderNode::SliderCallback pCallback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setClickCallback(pCallback);
            return {m_node};
        }

        Setup callbackRelease(geode::Button::ButtonCallback pCallback) requires std::derived_from<Node, geode::Button> {
            m_node->setUnselectCallback(std::move(pCallback));
            return {m_node};
        }
        Setup callbackRelease(geode::SliderNode::SliderCallback pCallback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setReleaseCallback(pCallback);
            return {m_node};
        }


        
        Setup string(geode::ZStringView pString) requires requires { m_node->setString(""); } {
            m_node->setString(pString.c_str());
            return {m_node};
        }
        
        
        
        Setup filter(geode::ZStringView pFilter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setFilter(pFilter);
            return {m_node};
        }
        Setup filter(geode::CommonFilter pFilter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCommonFilter(pFilter);
            return {m_node};
        }
        Setup maxCharCount(std::size_t pLength) requires std::derived_from<Node, geode::TextInput> {
            m_node->setMaxCharCount(pLength);
            return {m_node};
        }
        Setup placeholder(geode::ZStringView pPlaceholder) requires std::derived_from<Node, geode::TextInput> {
            m_node->setPlaceholder(pPlaceholder);
            return {m_node};
        }



        Setup toggle(bool pOn) requires std::derived_from<Node, CCMenuItemToggler> {
            m_node->toggle(pOn);
            return {m_node};
        }



        Setup addTo(cocos2d::CCArray* pArray) {
            pArray->addObject(m_node);
        }
    };

    template<typename T>
    Setup(T*) -> Setup<T*, T>;

    template<typename T>
    auto node(Setup<T> pSetup) {
        return pSetup.get();
    }
}