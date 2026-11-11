#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    Setup<Button> button(CCNode* top, Function<void(Button*)> callback) {
        return Button::createWithNode(top, std::move(callback));
    }
    Setup<Button> buttonSprite(ZStringView name, Function<void(Button*)> callback, float scale) {
        return Button::createWithNode(ui::sprite(name).scale(scale), std::move(callback));
    }
    Setup<Button> buttonFrame(ZStringView name, Function<void(Button*)> callback, float scale) {
        return Button::createWithNode(ui::frame(name).scale(scale), std::move(callback));
    }
    Setup<Button> circleButton(CCNode* top, CircleBaseColor color, Function<void(Button*)> callback) {
        return Button::createWithNode(CircleButtonSprite::create(top, color), std::move(callback));
    }
    Setup<Button> circleButtonSprite(ZStringView name, CircleBaseColor color, Function<void(Button*)> callback, float scale) {
        return Button::createWithNode(CircleButtonSprite::createWithSprite(name.c_str(), scale, color), std::move(callback));
    }
    Setup<Button> circleButtonFrame(ZStringView name, CircleBaseColor color, Function<void(Button*)> callback, float scale) {
        return Button::createWithNode(CircleButtonSprite::createWithSpriteFrameName(name.c_str(), scale, color), std::move(callback));
    }

    Setup<CCMenuItemToggler> toggler(CCNode* off, CCNode* on, Function<void(CCMenuItemToggler*)> callback) {
        return CCMenuItemExt::createToggler(off, on, std::move(callback));
    }
    Setup<CCMenuItemToggler> togglerBase(Function<void(CCMenuItemToggler*)> callback, float scale) {
        return CCMenuItemExt::createTogglerWithStandardSprites(scale, std::move(callback));
    }
    Setup<CCMenuItemToggler> togglerSprite(ZStringView off, ZStringView on, Function<void(CCMenuItemToggler*)> callback, float offScale, float onScale) {
        return CCMenuItemExt::createToggler(ui::sprite(off.c_str()).scale(offScale), ui::sprite(on.c_str()).scale(onScale), std::move(callback));
    }
    Setup<CCMenuItemToggler> togglerFrame(ZStringView off, ZStringView on, Function<void(CCMenuItemToggler*)> callback, float offScale, float onScale) {
        return CCMenuItemExt::createToggler(ui::frame(off.c_str()).scale(offScale), ui::frame(on.c_str()).scale(onScale), std::move(callback));
    }
    Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* off, cocos2d::CCNode* on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::create(off, offColor), CircleButtonSprite::create(on, onColor), std::move(callback));
    }
    Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor, float offScale, float onScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSprite(off.c_str(), offScale, offColor), CircleButtonSprite::createWithSprite(on.c_str(), onScale, onColor), std::move(callback));
    }
    Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor, float offScale, float onScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSpriteFrameName(off.c_str(), offScale, offColor), CircleButtonSprite::createWithSpriteFrameName(on.c_str(), onScale, onColor), std::move(callback));
    }

    Setup<Label> label(ZStringView font) {
        return Label::create(font);
    }
    Setup<Label> label(ZStringView text, ZStringView font) {
        return Label::create(text, font);
    }
    Setup<Label> labelRich(ZStringView font) {
        return Label::createRich("", font);
    }
    Setup<Label> labelRich(ZStringView text, ZStringView font) {
        return Label::createRich(text, font);
    }

    Setup<TextInput> input(CCSize size, std::optional<std::string> placeholder, TextInputCallback callback) {
        const std::string str = placeholder.value_or("");
        const float scale = size.height / DEFAULT_TEXT_INPUT_HEIGHT;

        auto textInput = TextInput::create(size.width / scale, str);
        textInput->setCallback(std::move(callback));
        textInput->setScale(scale);

        return textInput;
    }
    Setup<TextInput> input(float width, float height, std::optional<std::string> placeholder, TextInputCallback callback) {
        return input({width, height}, std::move(placeholder), std::move(callback));
    }
    Setup<TextInput> input(float width, std::optional<std::string> placeholder, TextInputCallback callback) {
        const std::string str = placeholder.value_or("");

        auto textInput = TextInput::create(width, str);
        textInput->setCallback(std::move(callback));

        return textInput;
    }

    Setup<CCMenu> menu(bool ignoreAnchor) {
        auto node = CCMenu::create();
        
        node->ignoreAnchorPointForPosition(ignoreAnchor);

        return node;
    }
    Setup<CCMenu> menu(Layout* layout, bool ignoreAnchor) {
        auto node = CCMenu::create();

        if (layout) {
            node->setLayout(layout, false);
        }

        node->ignoreAnchorPointForPosition(ignoreAnchor);

        return node;
    }

    Setup<CCNode> dummy(Layout* layout) {
        auto node = CCNode::create();

        if (layout) {
            node->setLayout(layout);
        }

        return node;
    }

    Setup<NineSlice> nineSlice(ZStringView texture, float scaleMultiplier) {
        auto node = NineSlice::create(texture);

        node->setScaleMultiplier(scaleMultiplier);

        return node;
    }

    Setup<CCSprite> sprite(ZStringView texture) {
        return CCSprite::create(texture.c_str());
    }
    Setup<CCSprite> frame(ZStringView texture) {
        return CCSprite::createWithSpriteFrameName(texture.c_str());
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