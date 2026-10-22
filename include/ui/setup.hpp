#pragma once

#include <Geode/ui/Button.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <Geode/ui/SliderNode.hpp>
#include "constants.hpp"

namespace nwo5::ui {
    template<typename ImplNode, typename Node = std::remove_pointer_t<ImplNode>>
    requires std::derived_from<Node, cocos2d::CCObject>
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

        auto operator*() const {
            return m_node;
        }

        auto get() const {
            return m_node;
        }
        auto data() const {
            return m_node;
        }
        auto unwrap() const {
            return m_node;
        }





        Setup parent(cocos2d::CCNode* node) requires std::derived_from<Node, cocos2d::CCNode> {
            node->addChild(m_node);
            node->updateLayout();

            return m_node;
        }
        template<typename... Args>
        Setup children(Args... children) requires std::derived_from<Node, cocos2d::CCNode> {
            (m_node->addChild(children), ...);

            m_node->updateLayout();

            return m_node;
        }

        Setup order(int order) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(order);
            return m_node;
        }
        Setup order(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setZOrder(copy->getZOrder());
            return m_node;
        }





        Setup pos(cocos2d::CCPoint pos) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPosition(pos);
            return m_node;
        }
        Setup pos(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos({x, y});
        }
        Setup pos(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(copy->getPosition());
        }
        Setup posX(float x) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionX(x);
            return m_node;
        }
        Setup posX(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(copy->getPositionX());
        }
        Setup posY(float y) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setPositionY(y);
            return m_node;
        }
        Setup posY(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(copy->getPositionY());
        }

        Setup move(cocos2d::CCPoint offset) requires std::derived_from<Node, cocos2d::CCNode> {
            return pos(m_node->getPosition() + offset);
        }
        Setup move(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            return move({x, y});
        }
        Setup moveX(float x) requires std::derived_from<Node, cocos2d::CCNode> {
            return posX(m_node->getPositionX() + x);
        }
        Setup moveY(float y) requires std::derived_from<Node, cocos2d::CCNode> {
            return posY(m_node->getPositionY() + y);
        }

        Setup center() {
            if (m_node->getParent()) {
                return pos(m_node->getParent()->getContentSize() / 2);
            }
            else {
                return pos(cocos2d::CCDirector::get()->getWinSize() / 2);
            }
        }




        
        Setup anchor(cocos2d::CCPoint anchor) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setAnchorPoint(anchor);

            if constexpr (std::derived_from<Node, cocos2d::CCLayer> || std::derived_from<Node, cocos2d::CCMenu>) {
                m_node->ignoreAnchorPointForPosition(false);
            }

            return m_node;
        }
        Setup anchor(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor({x, y});
        }
        Setup anchor(geode::Anchor anchor) requires std::derived_from<Node, cocos2d::CCNode> {
            auto out = CENTER_ANCHOR;
            switch (anchor) {
                case geode::Anchor::TopLeft: {
                    out = TOP_LEFT_ANCHOR;
                break; }
                case geode::Anchor::Top: {
                    out = TOP_CENTER_ANCHOR;
                break; }
                case geode::Anchor::TopRight: {
                    out = TOP_RIGHT_ANCHOR;
                break; }
                case geode::Anchor::Right: {
                    out = RIGHT_CENTER_ANCHOR;
                break; }
                case geode::Anchor::BottomRight: {
                    out = BOTTOM_RIGHT_ANCHOR;
                break; }
                case geode::Anchor::Bottom: {
                    out = BOTTOM_CENTER_ANCHOR;
                break; }
                case geode::Anchor::BottomLeft: {
                    out = BOTTOM_LEFT_ANCHOR;
                break; }
                case geode::Anchor::Left: {
                    out = LEFT_CENTER_ANCHOR;
                break; }
                default: {};
            }
            m_node->setAnchorPoint(out);

            if constexpr (std::derived_from<Node, cocos2d::CCLayer> || std::derived_from<Node, cocos2d::CCMenu>) {
                m_node->ignoreAnchorPointForPosition(false);
            }

            return m_node;
        }
        Setup anchor(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return anchor(copy->getAnchorPoint());
        }

        Setup ignoreAnchorForPos(bool ignore) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->ignoreAnchorPointForPosition(ignore);
            return m_node;
        }





        Setup rotation(float rotation) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setRotation(rotation);
            return m_node;
        }
        Setup rotation(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return rotation(copy->getRotation());
        }





        Setup scale(float scale) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScale(scale);
                m_node->updateSprite();
            }
            else {
                m_node->setScale(scale);
            }
            return m_node;
        }
        Setup scale(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scale(copy->getScale());
        }
        Setup scale(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                auto image = m_node->getNormalImage();
                image->setScaleX(x);
                image->setScaleY(y);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleX(x);
                m_node->setScaleY(y);
            }
            return m_node;
        }
        Setup scaleX(float x) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleX(x);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleX(x);
            }
            return m_node;
        }
        Setup scaleX(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleX(copy->getScaleX());
        }
        Setup scaleY(float y) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                m_node->getNormalImage()->setScaleY(y);
                m_node->updateSprite();
            }
            else {
                m_node->setScaleY(y);
            }
            return m_node;
        }
        Setup scaleY(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return scaleY(copy->getScaleY());
        }

        Setup scaleToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight())) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }
        Setup scaleWidthToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto origSize = m_node->getContentWidth()) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }
        Setup scaleHeightToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto origSize = m_node->getContentHeight()) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }

        Setup limitScaleToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight());
            const auto origScale = std::max(m_node->getScaleX(), m_node->getScaleY());

            if (origSize && origScale && origSize * origScale > size) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }
        Setup limitScaleWidthToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentWidth();
            const auto origScale = m_node->getScaleX();

            if (origSize && origScale && origSize * origScale > size) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }
        Setup limitScaleHeightToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentHeight();
            const auto origScale = m_node->getScaleY();

            if (origSize && origScale && origSize * origScale > size) {
                return scale(size / origSize);
            }
            else {
                return m_node;
            }
        }

        Setup stretchToFit(cocos2d::CCSize size) requires std::derived_from<Node, cocos2d::CCNode> {
            const auto origSize = m_node->getContentSize();

            if (origSize.width && origSize.height) {
                return scale(size.width / origSize.width, size.height / origSize.height);
            }
            return m_node;
        }
        Setup stretchToFit(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            return stretchToFit({x, y});
        }
        Setup stretchToFit(float size) requires std::derived_from<Node, cocos2d::CCNode> {
            return stretchToFit(size, size);
        }
        Setup stretchWidthToFit(float x) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto orig = m_node->getContentWidth()) {
                return scaleX(x / orig);
            }
            return m_node;
        }
        Setup stretchHeightToFit(float y) requires std::derived_from<Node, cocos2d::CCNode> {
            if (const auto orig = m_node->getContentHeight()) {
                return scaleY(y / orig);
            }
            return m_node;
        }





        Setup size(cocos2d::CCSize size) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize(size);
            return m_node;
        }
        Setup size(float width, float height) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentSize({width, height});
            return m_node;
        }
        Setup size(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return size(copy->getContentSize());
        }

        Setup width(float width) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentWidth(width);
            return m_node;
        }
        Setup width(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return width(copy->getContentWidth());
        }
        Setup height(float height) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setContentHeight(height);
            return m_node;
        }
        Setup height(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return height(copy->getContentHeight());
        }





        Setup tag(int tag) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setTag(tag);
            return m_node;
        }

        template<typename T>
        Setup id(T id) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setID(std::string{id});
            return m_node;
        }
        template <typename T, typename... Args>
        Setup id(fmt::format_string<T, Args...> format, T&& arg, Args&&... args) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setID(fmt::format(format, std::forward<T>(arg), std::forward<Args>(args)...));
            return m_node;
        }

        Setup userObject(geode::ZStringView id, cocos2d::CCObject* obj) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setUserObject(id, obj);
            return m_node;
        }
        Setup userFlag(geode::ZStringView id, bool on = true) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setUserFlag(id, on);
            return m_node;
        }





        Setup visible(bool visible) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(visible);
            return m_node;
        }
        Setup visible(cocos2d::CCNode* copy) requires std::derived_from<Node, cocos2d::CCNode> {
            return visible(copy->isVisible());
        }
        Setup hide() requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setVisible(false);
            return m_node;
        }





        Setup flipX(bool flip = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                m_node->setFlipX(flip);
            }
            else {
                m_node->setRotationY(flip ? 180.0f : 0.0f);
            }
            return m_node;
        }
        Setup flipY(bool flip = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                m_node->setFlipY(flip);
            }
            else {
                m_node->setRotationX(flip ? 180.0f : 0.0f);
            }
            return m_node;
        }





        Setup layout(geode::Layout* layout) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setLayout(layout);
            return m_node;
        }
        Setup updateLayout() requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->updateLayout();
            return m_node;
        }




        
        Setup options(geode::LayoutOptions* layout) requires std::derived_from<Node, cocos2d::CCNode> {
            m_node->setLayoutOptions(layout);
            return m_node;
        }

        Setup layoutBreakLine(bool on = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setBreakLine(on);
            }
            else {
                m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setBreakLine(on));
            }
            return m_node;
        }
        Setup layoutSameLine(bool on = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setSameLine(on);
            }
            else {
                m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setSameLine(on));
            }
            return m_node;
        }
        Setup layoutPrevGap(float gap) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setPrevGap(gap);
            }
            else {
                m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setPrevGap(gap));
            }
            return m_node;
        }
        Setup layoutNextGap(float gap) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setNextGap(gap);
            }
            else {
                m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setNextGap(gap));
            }
            return m_node;
        }

        Setup layoutAnchor(geode::Anchor anchor, bool setOwnAnchor = true) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setAnchor(anchor);
            }
            else {
                m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setAnchor(anchor));
            }
            return setOwnAnchor ? Setup::anchor(anchor) : Setup{m_node};
        }
        Setup layoutAnchorOffset(cocos2d::CCPoint off) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setOffset(off);
            }
            else {
                m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset(off));
            }
            return m_node;
        }
        Setup layoutAnchorOffset(float x, float y) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setOffset({x, y});
            }
            else {
                m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({x, y}));
            }
            return m_node;
        }
        Setup layoutAnchorOffsetX(float x) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setOffset({x, options->getOffset().y});
            }
            else {
                m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({x, 0.0f}));
            }
            return m_node;
        }
        Setup layoutAnchorOffsetY(float y) requires std::derived_from<Node, cocos2d::CCNode> {
            if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                options->setOffset({options->getOffset().x, y});
            }
            else {
                m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({0.0f, y}));
            }
            return m_node;
        }





        Setup color(cocos2d::ccColor3B const& color) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            m_node->setColor(color);
            return m_node;
        }
        Setup color(cocos2d::CCRGBAProtocol* copy) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            return color(copy->getColor());
        }
        template<std::integral T>
        Setup opacity(T opacity) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            m_node->setOpacity(opacity);
            return m_node;
        }
        Setup opacity(cocos2d::CCRGBAProtocol* copy) requires std::derived_from<Node, cocos2d::CCRGBAProtocol> {
            return opacity(copy->getOpacity());
        }





        Setup textureRect(cocos2d::CCRect rect) requires std::derived_from<Node, cocos2d::CCSprite> {
            m_node->setTextureRect(rect);
            return m_node;
        }





        Setup scaleMultiplier(float multiplier) requires std::derived_from<Node, geode::NineSlice> {
            m_node->setScaleMultiplier(multiplier);
            return m_node;
        }





        Setup blendFunc(cocos2d::ccBlendFunc func) requires std::derived_from<Node, cocos2d::CCBlendProtocol> {
            m_node->setBlendFunc(func);
            return m_node;
        }





        Setup callback(cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            m_node->setTarget(target, selector);
            return m_node;
        }
        Setup callback(geode::Function<void(Node*)> callback) requires std::derived_from<Node, cocos2d::CCMenuItem> {
            geode::cocos::CCMenuItemExt::assignCallback(m_node, std::move(callback));
            return m_node;
        }
        Setup callback(geode::Button::ButtonCallback callback) requires std::derived_from<Node, geode::Button> {
            m_node->setActivateCallback(std::move(callback));
            return m_node;
        }
        Setup callback(geode::LazySprite::Callback callback) requires std::derived_from<Node, geode::LazySprite> {
            m_node->setLoadCallback(std::move(callback));
            return m_node;
        }
        Setup callback(geode::SliderNode::SliderCallback callback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setSlideCallback(std::move(callback));
            return m_node;
        }
        Setup callback(TextInputCallback callback) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCallback(std::move(callback));
            return m_node;
        }

        Setup callbackSelect(geode::Button::ButtonCallback callback) requires std::derived_from<Node, geode::Button> {
            m_node->setSelectCallback(std::move(callback));
            return m_node;
        }
        Setup callbackSelect(geode::SliderNode::SliderCallback callback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setClickCallback(std::move(callback));
            return m_node;
        }

        Setup callbackUnselect(geode::Button::ButtonCallback callback) requires std::derived_from<Node, geode::Button> {
            m_node->setUnselectCallback(std::move(callback));
            return m_node;
        }
        Setup callbackUnselect(geode::SliderNode::SliderCallback callback) requires std::derived_from<Node, geode::SliderNode> {
            m_node->setReleaseCallback(std::move(callback));
            return m_node;
        }

        Setup callback(bool enabled) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCallbackEnabled(std::move(enabled));
            return m_node;
        }




        
        Setup text(geode::ZStringView string, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setText(string);
            
            if (validate) {
                m_node->validate();
            }

            return m_node;
        }
        Setup text(geode::ZStringView string) requires (!std::derived_from<Node, geode::Label>) && requires { m_node->setString(""); } {
            m_node->setString(string.c_str());
            
            return m_node;
        }
        Setup string(geode::ZStringView string, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setText(string);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        } 
        Setup string(geode::ZStringView string) requires (!std::derived_from<Node, geode::Label>) && requires { m_node->setString(""); } {
            m_node->setString(string.c_str());

            return m_node;
        }

        Setup alignment(geode::Label::Alignment alignment, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setAlignment(alignment);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }
        Setup alignment(cocos2d::CCTextAlignment alignment) requires std::derived_from<Node, cocos2d::CCLabelBMFont> {
            m_node->setAlignment(alignment);
            return m_node;
        }

        Setup kerning(float kerning, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setExtraKerning(kerning);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }
        Setup kerning(float kerning, bool validate = true) requires std::derived_from<Node, cocos2d::CCLabelBMFont> {
            m_node->setExtraKerning(kerning);
            return m_node;
        }

        Setup maxWidth(float width, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setMaxWidth(width);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }
        Setup fitBox(cocos2d::CCSize box, float maxScale, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setFitBox(box, maxScale);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }

        Setup lineSpacing(float spacing, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setLineSpacing(spacing);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }

        Setup breakWords(bool on = true, bool validate = true) requires std::derived_from<Node, geode::Label> {
            m_node->setBreakWords(on);

            if (validate) {
                m_node->validate();
            }

            return m_node;
        }
        
        
        


        Setup filter(geode::ZStringView filter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setFilter(filter);
            return m_node;
        }
        Setup filter(geode::CommonFilter filter) requires std::derived_from<Node, geode::TextInput> {
            m_node->setCommonFilter(filter);
            return m_node;
        }

        Setup maxCharCount(std::size_t length) requires std::derived_from<Node, geode::TextInput> {
            m_node->setMaxCharCount(length);
            return m_node;
        }

        Setup placeholder(geode::ZStringView placeholder) requires std::derived_from<Node, geode::TextInput> {
            m_node->setPlaceholder(placeholder);
            return m_node;
        }





        Setup toggle(bool on) requires std::derived_from<Node, CCMenuItemToggler> {
            m_node->toggle(on);
            return m_node;
        }



        

        Setup gap(float gap) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setGap(gap);
            return m_node;
        }

        Setup alignment(Alignment alignment) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setAxisAlignment(alignment);
            return m_node;
        }
        Setup crossAlignment(Alignment alignment) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setCrossAxisAlignment(alignment);
            m_node->setGrowCrossAxis(true);
            return m_node;
        }
        Setup crossLineAlignment(Alignment alignment) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setCrossAxisLineAlignment(alignment);
            return m_node;
        }

        Setup row() requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setAxis(geode::Axis::Row);
            return m_node;
        }
        Setup column() requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setAxis(geode::Axis::Column);
            return m_node;
        }

        Setup cross(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setGrowCrossAxis(on);
            return m_node;
        }

        Setup autoScale(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setAutoScale(on);
            return m_node;
        }

        Setup ignoreInvisible(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->ignoreInvisibleChildren(on);
            return m_node;
        }

        Setup padding(geode::Padding padding) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setPadding(padding);
            return m_node;
        }

        template<typename T = bool>
        requires std::is_arithmetic_v<T>
        Setup grow(T min = true) requires std::derived_from<Node, geode::AxisLayout> {
            if constexpr (std::same_as<T, bool>) {
                m_node->setAutoGrowAxis(min == true ? std::optional<float>{0.0f} : std::nullopt);
            }
            else {
                m_node->setAutoGrowAxis(min);
            }
            return m_node;
        }

        Setup reverse(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setAxisReverse(on);
            return m_node;
        }
        Setup crossReverse(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setCrossAxisReverse(on);
            return m_node;
        }

        Setup crossOverflow(bool on = true) requires std::derived_from<Node, geode::AxisLayout> {
            m_node->setCrossAxisOverflow(on);
            return m_node;
        }





        Setup prevGap(float gap) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setPrevGap(gap);
            return m_node;
        }
        Setup nextGap(float gap) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setNextGap(gap);
            return m_node;
        }

        Setup crossAlignment(Alignment alignment) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setCrossAxisAlignment(alignment);
            return m_node;
        }

        Setup crossLineAlignment(Alignment alignment) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setCrossAxisLineAlignment(alignment);
            return m_node;
        }
        
        Setup autoScale(bool on = true) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setAutoScale(on);
            return m_node;
        }
        Setup relativeScale(float scale) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setRelativeScale(scale);
            return m_node;
        }

        Setup breakLine(bool on = true) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setBreakLine(on);
            return m_node;
        }
        Setup sameLine(bool on = true) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setSameLine(on);
            return m_node;
        }

        Setup scalePriority(int priority) requires std::derived_from<Node, geode::AxisLayoutOptions> {
            m_node->setScalePriority(priority);
            return m_node;
        }





        Setup anchor(geode::Anchor anchor) requires std::derived_from<Node, geode::AnchorLayoutOptions> {
            m_node->setAnchor(anchor);
            return m_node;
        }
        Setup offset(cocos2d::CCPoint off) requires std::derived_from<Node, geode::AnchorLayoutOptions> {
            m_node->setOffset(off);
            return m_node;
        }
        Setup offset(float x, float y) requires std::derived_from<Node, geode::AnchorLayoutOptions> {
            m_node->setOffset({x, y});
            return m_node;
        }
        Setup offsetX(float x) requires std::derived_from<Node, geode::AnchorLayoutOptions> {
            m_node->setOffset({x, m_node->getOffset().y});
            return m_node;
        }
        Setup offsetY(float y) requires std::derived_from<Node, geode::AnchorLayoutOptions> {
            m_node->setOffset({m_node->getOffset().x, y});
            return m_node;
        }





        Setup addTo(cocos2d::CCArray* array) {
            array->addObject(m_node);
            return m_node;
        }
    };

    template<typename T>
    Setup(T*) -> Setup<T*, T>;
}