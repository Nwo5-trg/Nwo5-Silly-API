#pragma once

#include <Geode/ui/Button.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <Geode/ui/SliderNode.hpp>
#include <Geode/ui/Toggler.hpp>
#include "constants.hpp"

namespace nwo5::ui {
    template<typename ImplNode, std::derived_from<cocos2d::CCObject> Node = std::remove_pointer_t<ImplNode>>
    class Setup;
    
    #define $class_setup(className) \
    template<std::derived_from< className > Node> \
    struct SetupBase< className, Node >

    #define m_node static_cast<Setup<Node>*>(this)->m_node
    
    namespace impl {
        template<typename, typename>
        struct SetupBase {};
        
        $class_setup(cocos2d::CCObject) {
            Setup<Node> addTo(cocos2d::CCArray* array) {
                array->addObject(m_node);
                return m_node;
            }
        };

        $class_setup(cocos2d::CCNode) {
            Setup<Node> parent(cocos2d::CCNode *parent) {
                parent->addChild(m_node);
                parent->updateLayout();
                return m_node;
            }
            template<typename... Args>
            Setup<Node> children(Args... children) {
                (m_node->addChild(children), ...);

                m_node->updateLayout();

                return m_node;
            }

            Setup<Node> order(int order) {
                m_node->setZOrder(order);
                return m_node;
            }
            Setup<Node> order(cocos2d::CCNode* copy) {
                m_node->setZOrder(copy->getZOrder());
                return m_node;
            }

            Setup<Node> pos(cocos2d::CCPoint pos) {
                m_node->setPosition(pos);
                return m_node;
            }
            Setup<Node> pos(float x, float y) {
                return pos({x, y});
            }
            Setup<Node> pos(cocos2d::CCNode* copy) {
                return pos(copy->getPosition());
            }
            Setup<Node> posX(float x) {
                m_node->setPositionX(x);
                return m_node;
            }
            Setup<Node> posX(cocos2d::CCNode* copy) {
                return posX(copy->getPositionX());
            }
            Setup<Node> posY(float y) {
                m_node->setPositionY(y);
                return m_node;
            }
            Setup<Node> posY(cocos2d::CCNode* copy) {
                return posY(copy->getPositionY());
            }

            Setup<Node> move(cocos2d::CCPoint offset) {
                return pos(m_node->getPosition() + offset);
            }
            Setup<Node> move(float x, float y) {
                return move({x, y});
            }
            Setup<Node> moveX(float x) {
                return posX(m_node->getPositionX() + x);
            }
            Setup<Node> moveY(float y) {
                return posY(m_node->getPositionY() + y);
            }

            Setup<Node> center() {
                if (m_node->getParent()) {
                    return pos(m_node->getParent()->getContentSize() / 2);
                }
                else {
                    return pos(cocos2d::CCDirector::get()->getWinSize() / 2);
                }
            }
            
            Setup<Node> anchor(cocos2d::CCPoint anchor) {
                m_node->setAnchorPoint(anchor);

                if constexpr (std::derived_from<Node, cocos2d::CCLayer> || std::derived_from<Node, cocos2d::CCMenu>) {
                    m_node->ignoreAnchorPointForPosition(false);
                }

                return m_node;
            }
            Setup<Node> anchor(float x, float y) {
                return anchor({x, y});
            }
            Setup<Node> anchor(geode::Anchor anchor) {
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
            Setup<Node> anchor(cocos2d::CCNode* copy) {
                return anchor(copy->getAnchorPoint());
            }

            Setup<Node> ignoreAnchorForPos(bool ignore) {
                m_node->ignoreAnchorPointForPosition(ignore);
                return m_node;
            }

            Setup<Node> rotation(float rotation) {
                m_node->setRotation(rotation);
                return m_node;
            }
            Setup<Node> rotation(cocos2d::CCNode* copy) {
                return rotation(copy->getRotation());
            }

            Setup<Node> scale(float scale) {
                if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                    m_node->getNormalImage()->setScale(scale);
                    m_node->updateSprite();
                }
                else if constexpr (std::derived_from<Node, geode::Button>) {
                    auto image = m_node->getDisplayNode();
                    image->setScale(scale);
                    m_node->setContentSize(image->getScaledContentSize());
                }
                else {
                    m_node->setScale(scale);
                }
                return m_node;
            }
            Setup<Node> scale(cocos2d::CCNode* copy) {
                return scale(copy->getScale());
            }
            Setup<Node> scale(float x, float y) {
                if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                    auto image = m_node->getNormalImage();
                    image->setScaleX(x);
                    image->setScaleY(y);
                    m_node->updateSprite();
                }
                else if constexpr (std::derived_from<Node, geode::Button>) {
                    auto image = m_node->getDisplayNode();
                    image->setScaleX(x);
                    image->setScaleY(y);
                    m_node->setContentSize(image->getScaledContentSize());
                }
                else {
                    m_node->setScaleX(x);
                    m_node->setScaleY(y);
                }
                return m_node;
            }
            Setup<Node> scaleX(float x) {
                if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                    m_node->getNormalImage()->setScaleX(x);
                    m_node->updateSprite();
                }
                else if constexpr (std::derived_from<Node, geode::Button>) {
                    auto image = m_node->getDisplayNode();
                    image->setScaleX(x);
                    m_node->setContentSize(image->getScaledContentSize());
                }
                else {
                    m_node->setScaleX(x);
                }
                return m_node;
            }
            Setup<Node> scaleX(cocos2d::CCNode* copy) {
                return scaleX(copy->getScaleX());
            }
            Setup<Node> scaleY(float y) {
                if constexpr (std::derived_from<Node, CCMenuItemSpriteExtra>) {
                    m_node->getNormalImage()->setScaleY(y);
                    m_node->updateSprite();
                }
                else if constexpr (std::derived_from<Node, geode::Button>) {
                    auto image = m_node->getDisplayNode();
                    image->setScaleY(y);
                    m_node->setContentSize(image->getScaledContentSize());
                }
                else {
                    m_node->setScaleY(y);
                }
                return m_node;
            }
            Setup<Node> scaleY(cocos2d::CCNode* copy) {
                return scaleY(copy->getScaleY());
            }

            Setup<Node> scaleToFit(float size) {
                if (const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight())) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }
            Setup<Node> scaleWidthToFit(float size) {
                if (const auto origSize = m_node->getContentWidth()) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }
            Setup<Node> scaleHeightToFit(float size) {
                if (const auto origSize = m_node->getContentHeight()) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }

            Setup<Node> limitScaleToFit(float size) {
                const auto origSize = std::max(m_node->getContentWidth(), m_node->getContentHeight());
                const auto origScale = std::max(m_node->getScaleX(), m_node->getScaleY());

                if (origSize && origScale && origSize * origScale > size) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }
            Setup<Node> limitScaleWidthToFit(float size) {
                const auto origSize = m_node->getContentWidth();
                const auto origScale = m_node->getScaleX();

                if (origSize && origScale && origSize * origScale > size) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }
            Setup<Node> limitScaleHeightToFit(float size) {
                const auto origSize = m_node->getContentHeight();
                const auto origScale = m_node->getScaleY();

                if (origSize && origScale && origSize * origScale > size) {
                    return scale(size / origSize);
                }
                else {
                    return m_node;
                }
            }

            Setup<Node> stretchToFit(cocos2d::CCSize size) {
                const auto origSize = m_node->getContentSize();

                if (origSize.width && origSize.height) {
                    return scale(size.width / origSize.width, size.height / origSize.height);
                }
                return m_node;
            }
            Setup<Node> stretchToFit(float x, float y) {
                return stretchToFit({x, y});
            }
            Setup<Node> stretchToFit(float size) {
                return stretchToFit(size, size);
            }
            Setup<Node> stretchWidthToFit(float x) {
                if (const auto orig = m_node->getContentWidth()) {
                    return scaleX(x / orig);
                }
                return m_node;
            }
            Setup<Node> stretchHeightToFit(float y) {
                if (const auto orig = m_node->getContentHeight()) {
                    return scaleY(y / orig);
                }
                return m_node;
            }

            Setup<Node> size(cocos2d::CCSize size) {
                m_node->setContentSize(size);
                return m_node;
            }
            Setup<Node> size(float width, float height) {
                m_node->setContentSize({width, height});
                return m_node;
            }
            Setup<Node> size(cocos2d::CCNode* copy) {
                return size(copy->getContentSize());
            }

            Setup<Node> width(float width) {
                m_node->setContentWidth(width);
                return m_node;
            }
            Setup<Node> width(cocos2d::CCNode* copy) {
                return width(copy->getContentWidth());
            }
            Setup<Node> height(float height) {
                m_node->setContentHeight(height);
                return m_node;
            }
            Setup<Node> height(cocos2d::CCNode* copy) {
                return height(copy->getContentHeight());
            }

            Setup<Node> tag(int tag) {
                m_node->setTag(tag);
                return m_node;
            }

            template<typename T>
            Setup<Node> id(T id) {
                m_node->setID(std::string{id});
                return m_node;
            }
            template <typename T, typename... Args>
            Setup<Node> id(fmt::format_string<T, Args...> format, T&& arg, Args&&... args) {
                m_node->setID(fmt::format(format, std::forward<T>(arg), std::forward<Args>(args)...));
                return m_node;
            }

            Setup<Node> userObject(geode::ZStringView id, cocos2d::CCObject* obj) {
                m_node->setUserObject(id, obj);
                return m_node;
            }
            Setup<Node> userFlag(geode::ZStringView id, bool on = true) {
                m_node->setUserFlag(id, on);
                return m_node;
            }

            Setup<Node> visible(bool visible) {
                m_node->setVisible(visible);
                return m_node;
            }
            Setup<Node> visible(cocos2d::CCNode* copy) {
                return visible(copy->isVisible());
            }
            Setup<Node> hide() {
                m_node->setVisible(false);
                return m_node;
            }

            Setup<Node> flipX(bool flip = true) {
                if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                    m_node->setFlipX(flip);
                }
                else {
                    m_node->setRotationY(flip ? 180.0f : 0.0f);
                }
                return m_node;
            }
            Setup<Node> flipY(bool flip = true) {
                if constexpr (std::derived_from<Node, cocos2d::CCSprite>) {
                    m_node->setFlipY(flip);
                }
                else {
                    m_node->setRotationX(flip ? 180.0f : 0.0f);
                }
                return m_node;
            }

            Setup<Node> layout(geode::Layout* layout) {
                m_node->setLayout(layout);
                return m_node;
            }
            Setup<Node> updateLayout() {
                m_node->updateLayout();
                return m_node;
            }
 
            Setup<Node> options(geode::LayoutOptions* layout) {
                m_node->setLayoutOptions(layout);
                return m_node;
            }

            Setup<Node> layoutBreakLine(bool on = true) {
                if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setBreakLine(on);
                }
                else {
                    m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setBreakLine(on));
                }
                return m_node;
            }
            Setup<Node> layoutSameLine(bool on = true) {
                if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setSameLine(on);
                }
                else {
                    m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setSameLine(on));
                }
                return m_node;
            }
            Setup<Node> layoutPrevGap(float gap) {
                if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setPrevGap(gap);
                }
                else {
                    m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setPrevGap(gap));
                }
                return m_node;
            }
            Setup<Node> layoutNextGap(float gap) {
                if (auto options = geode::cast::typeinfo_cast<geode::AxisLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setNextGap(gap);
                }
                else {
                    m_node->setLayoutOptions(geode::AxisLayoutOptions::create()->setNextGap(gap));
                }
                return m_node;
            }

            Setup<Node> layoutAnchor(geode::Anchor anchor, bool setOwnAnchor = true) {
                if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setAnchor(anchor);
                }
                else {
                    m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setAnchor(anchor));
                }
                return setOwnAnchor ? SetupBase::anchor(anchor) : Setup<Node>{m_node};
            }
            Setup<Node> layoutAnchorOffset(cocos2d::CCPoint off) {
                if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setOffset(off);
                }
                else {
                    m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset(off));
                }
                return m_node;
            }
            Setup<Node> layoutAnchorOffset(float x, float y) {
                if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setOffset({x, y});
                }
                else {
                    m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({x, y}));
                }
                return m_node;
            }
            Setup<Node> layoutAnchorOffsetX(float x) {
                if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setOffset({x, options->getOffset().y});
                }
                else {
                    m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({x, 0.0f}));
                }
                return m_node;
            }
            Setup<Node> layoutAnchorOffsetY(float y) {
                if (auto options = geode::cast::typeinfo_cast<geode::AnchorLayoutOptions*>(m_node->getLayoutOptions())) {
                    options->setOffset({options->getOffset().x, y});
                }
                else {
                    m_node->setLayoutOptions(geode::AnchorLayoutOptions::create()->setOffset({0.0f, y}));
                }
                return m_node;
            }
        };

        $class_setup(cocos2d::CCRGBAProtocol) {
            Setup<Node> color(cocos2d::ccColor3B const& color) {
                m_node->setColor(color);
                return m_node;
            }
            Setup<Node> color(cocos2d::CCRGBAProtocol* copy) {
                return color(copy->getColor());
            }
            template<std::integral T>
            Setup<Node> opacity(T opacity) {
                m_node->setOpacity(opacity);
                return m_node;
            }
            Setup<Node> opacity(cocos2d::CCRGBAProtocol* copy) {
                return opacity(copy->getOpacity());
            }
        };

        $class_setup(cocos2d::CCSprite) {
            Setup<Node> textureRect(cocos2d::CCRect rect) {
                m_node->setTextureRect(rect);
                return m_node;
            }

            Setup<Node> dontDraw(bool on = true) {
                m_node->setDontDraw(on);
                return m_node;
            }
        };

        $class_setup(geode::NineSlice) {
            Setup<Node> scaleMultiplier(float multiplier) {
                m_node->setScaleMultiplier(multiplier);
                return m_node;
            }
        };

        $class_setup(cocos2d::CCBlendProtocol) {
            Setup<Node> blendFunc(cocos2d::ccBlendFunc func) {
                m_node->setBlendFunc(func);
                return m_node;
            }
        };

        $class_setup(cocos2d::CCMenuItem) {
            Setup<Node> callback(cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector) {
                m_node->setTarget(target, selector);
                return m_node;
            }
            Setup<Node> callback(geode::Function<void(Node*)> callback) {
                geode::cocos::CCMenuItemExt::assignCallback(m_node, std::move(callback));
                return m_node;
            }

            Setup<Node> enabled(bool on = true) {
                m_node->setEnabled(on);
                return m_node;
            }
        };

        $class_setup(geode::Button) {
            Setup<Node> callback(geode::Button::ButtonCallback callback) {
                m_node->setActivateCallback(std::move(callback));
                return m_node;
            }
            Setup<Node> callbackSelect(geode::Button::ButtonCallback callback) {
                m_node->setSelectCallback(std::move(callback));
                return m_node;
            }
            Setup<Node> callbackUnselect(geode::Button::ButtonCallback callback) {
                m_node->setUnselectCallback(std::move(callback));
                return m_node;
            }

            Setup<Node> enabled(bool on = true) {
                m_node->setEnabled(on);
                return m_node;
            }
        };

        $class_setup(geode::LazySprite) {
            Setup<Node> callback(geode::LazySprite::Callback callback) {
                m_node->setLoadCallback(std::move(callback));
                return m_node;
            }
        };

        $class_setup(geode::SliderNode) {
            Setup<Node> callback(geode::SliderNode::SliderCallback callback) {
                m_node->setSlideCallback(std::move(callback));
                return m_node;
            }
            Setup<Node> callbackSelect(geode::SliderNode::SliderCallback callback) {
                m_node->setClickCallback(std::move(callback));
                return m_node;
            }

            Setup<Node> callbackUnselect(geode::SliderNode::SliderCallback callback) {
                m_node->setReleaseCallback(std::move(callback));
                return m_node;
            }
        };

        $class_setup(geode::TextInput) {
            Setup<Node> callback(TextInputCallback callback) {
                m_node->setCallback(std::move(callback));
                return m_node;
            }
            Setup<Node> enterClickedCallback(TextInputCallback callback) {
                m_node->setEnterCallback(std::move(callback));
                return m_node;
            }
            Setup<Node> focusCallback(geode::Function<void(geode::TextInput::FocusState state)> callback) {
                m_node->setFocusCallback(std::move(callback));
                return m_node;
            }

            Setup<Node> string(geode::ZStringView text) {
                m_node->setString(text);
                return m_node;
            }

            Setup<Node> filter(geode::ZStringView filter) {
                m_node->setFilter(filter);
                return m_node;
            }
            Setup<Node> filter(geode::CommonFilter filter) {
                m_node->setCommonFilter(filter);
                return m_node;
            }

            Setup<Node> maxCharCount(std::size_t length) {
                m_node->setMaxCharCount(length);
                return m_node;
            }

            Setup<Node> alignment(geode::Label::Alignment alignment) {
                m_node->setAlignment(alignment);
                return m_node;
            }

            Setup<Node> placeholder(geode::ZStringView placeholder) {
                m_node->setPlaceholder(placeholder);
                return m_node;
            }
            Setup<Node> placeholderColor(cocos2d::ccColor4B color) {
                m_node->setPlaceholderColor(color);
                return m_node;
            }

            Setup<Node> selection(int start, int end) {
                m_node->setSelection(start, end);
                return m_node;
            }
            Setup<Node> selectionColor(cocos2d::ccColor4B color) {
                m_node->setSelectionColor(color);
                return m_node;
            }

            Setup<Node> cursorPos(int pos) {
                m_node->setCursorPos(pos);
                return m_node;
            }
            Setup<Node> caretColor(cocos2d::ccColor4B color) {
                m_node->setCaretColor(color);
                return m_node;
            }

            Setup<Node> padding(cocos2d::CCPoint padding) {
                m_node->setPadding(padding);
                return m_node;
            }

            Setup<Node> numeric(bool on = true) {
                m_node->setNumericMode(on);
                return m_node;
            }
            
            Setup<Node> enabled(bool on = true) {
                m_node->setEnabled(on);
                return m_node;
            }

            Setup<Node> multiline(bool on = true) {
                m_node->setMultiline(on);
                return m_node;
            }
            Setup<Node> wrap(bool on = true) {
                m_node->setWrap(on);
                return m_node;
            }

            Setup<Node> fontScale(float scale) {
                m_node->setFontScale(scale);
                return m_node;
            }

            Setup<Node> label(geode::ZStringView label) {
                m_node->setLabel(label);
                return m_node;
            }

            Setup<Node> overflow(bool on = true) {
                m_node->setOverflowMode(on ? geode::TextInput::OverflowMode::Clip : geode::TextInput::OverflowMode::Scale);
                return m_node;
            }

            Setup<Node> focus(bool on = true) {
                if (on) {
                    m_node->focus();
                }
                else {
                    m_node->unfocus();
                }
                return m_node;
            }
        };

        $class_setup(geode::Label) {
            Setup<Node> text(geode::ZStringView string, bool validate = true) {
                m_node->setText(string);
                
                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }
            Setup<Node> string(geode::ZStringView string, bool validate = true) {
                m_node->setText(string);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            } 

            Setup<Node> alignment(geode::Label::Alignment alignment, bool validate = true) {
                m_node->setAlignment(alignment);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }

            Setup<Node> kerning(float kerning, bool validate = true) {
                m_node->setExtraKerning(kerning);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }

            Setup<Node> maxWidth(float width, bool validate = true) {
                m_node->setMaxWidth(width);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }
            Setup<Node> fitBox(cocos2d::CCSize box, float maxScale, bool validate = true) {
                m_node->setFitBox(box, maxScale);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }

            Setup<Node> lineSpacing(float spacing, bool validate = true) {
                m_node->setLineSpacing(spacing);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }

            Setup<Node> breakWords(bool on = true, bool validate = true) {
                m_node->setBreakWords(on);

                if (validate) {
                    m_node->validate();
                }

                return m_node;
            }
        };

        $class_setup(cocos2d::CCLabelProtocol) {
            Setup<Node> text(geode::ZStringView string) {
                m_node->setString(string);

                return m_node;
            }
            Setup<Node> string(geode::ZStringView string) {
                m_node->setString(string);

                return m_node;
            } 
        };

        $class_setup(geode::Toggler) {
            Setup<Node> callback(geode::Toggler::ToggleCallback callback) {
                m_node->setToggleCallback(std::move(callback));
                return m_node;
            }

            Setup<Node> toggle(bool on, bool callback = false) {
                m_node->setToggled(on, callback);
                return m_node;
            }
        };

        $class_setup(geode::AxisLayout) {
            Setup<Node> gap(float gap) {
                m_node->setGap(gap);
                return m_node;
            }

            Setup<Node> alignment(Alignment alignment) {
                m_node->setAxisAlignment(alignment);
                return m_node;
            }
            Setup<Node> crossAlignment(Alignment alignment) {
                m_node->setCrossAxisAlignment(alignment);
                m_node->setGrowCrossAxis(true);
                return m_node;
            }
            Setup<Node> crossLineAlignment(Alignment alignment) {
                m_node->setCrossAxisLineAlignment(alignment);
                return m_node;
            }

            Setup<Node> row() {
                m_node->setAxis(geode::Axis::Row);
                return m_node;
            }
            Setup<Node> column() {
                m_node->setAxis(geode::Axis::Column);
                return m_node;
            }

            Setup<Node> cross(bool on = true) {
                m_node->setGrowCrossAxis(on);
                return m_node;
            }

            Setup<Node> autoScale(bool on = true) {
                m_node->setAutoScale(on);
                return m_node;
            }

            Setup<Node> ignoreInvisible(bool on = true) {
                m_node->ignoreInvisibleChildren(on);
                return m_node;
            }

            Setup<Node> padding(geode::Padding padding) {
                m_node->setPadding(padding);
                return m_node;
            }

            template<typename T = bool>
            requires std::is_arithmetic_v<T>
            Setup<Node> grow(T min = true) {
                if constexpr (std::same_as<T, bool>) {
                    m_node->setAutoGrowAxis(min == true ? std::optional<float>{0.0f} : std::nullopt);
                }
                else {
                    m_node->setAutoGrowAxis(min);
                }
                return m_node;
            }

            Setup<Node> reverse(bool on = true) {
                m_node->setAxisReverse(on);
                return m_node;
            }
            Setup<Node> crossReverse(bool on = true) {
                m_node->setCrossAxisReverse(on);
                return m_node;
            }

            Setup<Node> crossOverflow(bool on = true) {
                m_node->setCrossAxisOverflow(on);
                return m_node;
            }

            Setup<Node> boundBox(bool on = true) {
                m_node->useBoundingBox(on);
                return m_node;
            }
        };

        $class_setup(geode::AxisLayoutOptions) {
            Setup<Node> prevGap(float gap) {
                m_node->setPrevGap(gap);
                return m_node;
            }
            Setup<Node> nextGap(float gap) {
                m_node->setNextGap(gap);
                return m_node;
            }

            Setup<Node> crossAlignment(Alignment alignment) {
                m_node->setCrossAxisAlignment(alignment);
                return m_node;
            }

            Setup<Node> crossLineAlignment(Alignment alignment) {
                m_node->setCrossAxisLineAlignment(alignment);
                return m_node;
            }
            
            Setup<Node> autoScale(bool on = true) {
                m_node->setAutoScale(on);
                return m_node;
            }
            Setup<Node> relativeScale(float scale) {
                m_node->setRelativeScale(scale);
                return m_node;
            }

            Setup<Node> breakLine(bool on = true) {
                m_node->setBreakLine(on);
                return m_node;
            }
            Setup<Node> sameLine(bool on = true) {
                m_node->setSameLine(on);
                return m_node;
            }

            Setup<Node> scalePriority(int priority) {
                m_node->setScalePriority(priority);
                return m_node;
            }
        };

        $class_setup(geode::AnchorLayoutOptions) {
            Setup<Node> anchor(geode::Anchor anchor) {
                m_node->setAnchor(anchor);
                return m_node;
            }
            Setup<Node> anchorOffset(cocos2d::CCPoint off) {
                m_node->setOffset(off);
                return m_node;
            }
            Setup<Node> anchorOffset(float x, float y) {
                m_node->setOffset({x, y});
                return m_node;
            }
            Setup<Node> anchorOffsetX(float x) {
                m_node->setOffset({x, 0.0f});
                return m_node;
            }
            Setup<Node> anchorOffsetY(float y) {
                m_node->setOffset({0.0f, y});
                return m_node;
            }
        };

        // geode should totally merge my pr fr fr
        // $class_setup(geode::ButtonBackgroundSprite) {
        //     Setup<Node> nodeAlignment(geode::ButtonBackgroundSprite::NodeAlignment alignment) {
        //         m_node->setNodeAlignment(alignment);
        //         return m_node;
        //     }

        //     Setup<Node> string(geode::ZStringView text) {
        //         m_node->setString(text.c_str());
        //         return m_node;
        //     }
        //     Setup<Node> font(geode::ZStringView font) {
        //         m_node->setFont(font);
        //         return m_node;
        //     }

        //     Setup<Node> labelOffset(float offset) {
        //         m_node->setLabelOffset(offset);
        //         return m_node;
        //     }

        //     Setup<Node> labelScale(float scale) {
        //         m_node->setLabelScale(scale);
        //         return m_node;
        //     }
        //     Setup<Node> nodeScale(float scale) {
        //         m_node->setNodeScale(scale);
        //         return m_node;
        //     }

        //     Setup<Node> absoluteWidth(std::optional<float> width) {
        //         m_node->setWidth(width);
        //         return m_node;
        //     }
        //     Setup<Node> minWidth(float width) {
        //         m_node->setMinWidth(width);
        //         return m_node;
        //     }
        //     Setup<Node> maxWidth(float width) {
        //         m_node->setMaxWidth(width);
        //         return m_node;
        //     }
        //     Setup<Node> absoluteHeight(std::optional<float> height) {
        //         m_node->setHeight(height);
        //         return m_node;
        //     }
        //     Setup<Node> minHeight(float height) {
        //         m_node->setMinHeight(height);
        //         return m_node;
        //     }
        //     Setup<Node> maxHeight(float height) {
        //         m_node->setMaxHeight(height);
        //         return m_node;
        //     }
        //     Setup<Node> absoluteSize(cocos2d::CCSize size) {
        //         m_node->setWidth(size.width);
        //         m_node->setHeight(size.height);
        //         return m_node;
        //     }
        //     Setup<Node> absoluteSize(float x, float y) {
        //         m_node->setWidth(x);
        //         m_node->setHeight(y);
        //         return m_node;
        //     }

        //     Setup<Node> padding(const geode::Padding& padding) {
        //         m_node->setPadding(padding);
        //         return m_node;
        //     }
        //     Setup<Node> gap(float gap) {
        //         m_node->setGap(gap);
        //         return m_node;
        //     }
        //     Setup<Node> lineAlignment(geode::CrossAxisAlignment alignment) {
        //         m_node->setLineAlignment(alignment);
        //         return m_node;
        //     }
        // };
    }

    #undef m_node
    #undef $class_setup

    template<typename ImplNode, std::derived_from<cocos2d::CCObject> Node>
    class Setup final
        : public impl::SetupBase<cocos2d::CCObject, Node>,
          public impl::SetupBase<cocos2d::CCNode, Node>,
          public impl::SetupBase<cocos2d::CCRGBAProtocol, Node>,
          public impl::SetupBase<cocos2d::CCSprite, Node>,
          public impl::SetupBase<geode::NineSlice, Node>,
          public impl::SetupBase<cocos2d::CCBlendProtocol, Node>,
          public impl::SetupBase<cocos2d::CCMenuItem, Node>,
          public impl::SetupBase<geode::Button, Node>,
          public impl::SetupBase<geode::LazySprite, Node>,
          public impl::SetupBase<geode::SliderNode, Node>,
          public impl::SetupBase<geode::TextInput, Node>,
          public impl::SetupBase<geode::Label, Node>,
          public impl::SetupBase<cocos2d::CCLabelProtocol, Node>,
          public impl::SetupBase<geode::Toggler, Node>,
          public impl::SetupBase<geode::AxisLayout, Node>,
          public impl::SetupBase<geode::AxisLayoutOptions, Node>,
          public impl::SetupBase<geode::AnchorLayoutOptions, Node>
    {
    protected:
        Node* m_node;

        template <typename, typename>
        friend class impl::SetupBase;

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
    };

    template<typename T>
    Setup(T*) -> Setup<T*, T>;
}