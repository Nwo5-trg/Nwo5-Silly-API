#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    Setup<Button> button(CCNode* pTop, Function<void(Button*)> pCallback) {
        return Button::createWithNode(pTop, std::move(pCallback));
    }
    Setup<Button> buttonSprite(ZStringView pName, Function<void(Button*)> pCallback, float pScale) {
        return Button::createWithNode(ui::sprite(pName).scale(pScale), std::move(pCallback));
    }
    Setup<Button> buttonFrame(ZStringView pName, Function<void(Button*)> pCallback, float pScale) {
        return Button::createWithNode(ui::frame(pName).scale(pScale), std::move(pCallback));
    }
    Setup<Button> circleButton(CCNode* pTop, CircleBaseColor pColor, Function<void(Button*)> pCallback) {
        return Button::createWithNode(CircleButtonSprite::create(pTop, pColor), std::move(pCallback));
    }
    Setup<Button> circleButtonSprite(ZStringView pName, CircleBaseColor pColor, Function<void(Button*)> pCallback, float pScale) {
        return Button::createWithNode(CircleButtonSprite::createWithSprite(pName.c_str(), pScale, pColor), std::move(pCallback));
    }
    Setup<Button> Button(ZStringView pName, CircleBaseColor pColor, Function<void(Button*)> pCallback, float pScale) {
        return Button::createWithNode(CircleButtonSprite::createWithSpriteFrameName(pName.c_str(), pScale, pColor), std::move(pCallback));
    }

    Setup<CCMenuItemToggler> toggler(CCNode* pOff, CCNode* pOn, Function<void(CCMenuItemToggler*)> pCallback) {
        return CCMenuItemExt::createToggler(pOff, pOn, std::move(pCallback));
    }
    Setup<CCMenuItemToggler> togglerBase(Function<void(CCMenuItemToggler*)> pCallback, float pScale) {
        return CCMenuItemExt::createTogglerWithStandardSprites(pScale, std::move(pCallback));
    }
    Setup<CCMenuItemToggler> togglerSprite(ZStringView pOff, ZStringView pOn, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(ui::sprite(pOff.c_str()).scale(pOffScale), ui::sprite(pOn.c_str()).scale(pOnScale), std::move(pCallback));
    }
    Setup<CCMenuItemToggler> togglerFrame(ZStringView pOff, ZStringView pOn, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(ui::frame(pOff.c_str()).scale(pOffScale), ui::frame(pOn.c_str()).scale(pOnScale), std::move(pCallback));
    }
    Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor, geode::CircleBaseColor pOnColor) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::create(pOff, pOffColor), CircleButtonSprite::create(pOn, pOnColor), std::move(pCallback));
    }
    Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor, geode::CircleBaseColor pOnColor, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSprite(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSprite(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }
    Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor, geode::CircleBaseColor pOnColor, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSpriteFrameName(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSpriteFrameName(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }

    Setup<Label> label(ZStringView pFont) {
        return Label::create(pFont);
    }
    Setup<Label> label(ZStringView pText, ZStringView pFont) {
        return Label::create(pText, pFont);
    }
    Setup<Label> labelRich(ZStringView pFont) {
        return Label::createRich("", pFont);
    }
    Setup<Label> labelRich(ZStringView pText, ZStringView pFont) {
        return Label::createRich(pText, pFont);
    }

    Setup<TextInput> input(CCSize pSize, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        const std::string str = pPlaceholder.value_or("");
        const float scale = pSize.height / DEFAULT_TEXT_INPUT_HEIGHT;

        auto textInput = TextInput::create(pSize.width / scale, str);
        textInput->setCallback(std::move(pCallback));
        textInput->setScale(scale);

        return textInput;
    }
    Setup<TextInput> input(float pWidth, float pHeight, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        return input({pWidth, pHeight}, std::move(pPlaceholder), std::move(pCallback));
    }
    Setup<TextInput> input(float pWidth, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        const std::string str = pPlaceholder.value_or("");

        auto textInput = TextInput::create(pWidth, str);
        textInput->setCallback(std::move(pCallback));

        return textInput;
    }

    Setup<CCMenu> menu(bool pIgnoreAnchor) {
        auto node = CCMenu::create();
        
        node->ignoreAnchorPointForPosition(pIgnoreAnchor);

        return node;
    }
    Setup<CCMenu> menu(Layout* pLayout, bool pIgnoreAnchor) {
        auto node = CCMenu::create();

        if (pLayout) {
            node->setLayout(pLayout, false);
        }

        node->ignoreAnchorPointForPosition(pIgnoreAnchor);

        return node;
    }

    Setup<CCNode> dummy(Layout* pLayout) {
        auto node = CCNode::create();

        if (pLayout) {
            node->setLayout(pLayout);
        }

        return node;
    }

    Setup<NineSlice> nineSlice(ZStringView pTexture, float pScaleMultiplier) {
        auto node = NineSlice::create(pTexture);

        node->setScaleMultiplier(pScaleMultiplier);

        return node;
    }

    Setup<CCSprite> sprite(ZStringView pTexture) {
        return CCSprite::create(pTexture.c_str());
    }
    Setup<CCSprite> frame(ZStringView pTexture) {
        return CCSprite::createWithSpriteFrameName(pTexture.c_str());
    }

    Setup<AxisLayout> row() {
        return RowLayout::create();
    }
    Setup<AxisLayout> column() {
        return ColumnLayout::create();
    }
    Setup<AnchorLayout> anchor() {
        return AnchorLayout::create();
    }

    Setup<AxisLayoutOptions> axisOptions() {
        return AxisLayoutOptions::create();
    }
    Setup<AnchorLayoutOptions> anchorOptions() {
        return AnchorLayoutOptions::create();
    }
}