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

    Setup<geode::Toggler> toggler(CCNode* off, CCNode* on, Function<void(geode::Toggler*, bool)> callback) {
        return Toggler::create(off, on, std::move(callback));
    }
    Setup<geode::Toggler> togglerBase(Function<void(geode::Toggler*, bool)> callback, float scale) {
        return Toggler::createWithStandardSprites(scale, std::move(callback));
    }
    Setup<geode::Toggler> togglerSprite(ZStringView off, ZStringView on, Function<void(geode::Toggler*, bool)> callback, float offScale, float onScale) {
        return Toggler::create(ui::sprite(off).scale(offScale), ui::sprite(on).scale(onScale), std::move(callback));
    }
    Setup<geode::Toggler> togglerFrame(ZStringView off, ZStringView on, Function<void(geode::Toggler*, bool)> callback, float offScale, float onScale) {
        return Toggler::create(ui::frame(off).scale(offScale), ui::frame(on).scale(onScale), std::move(callback));
    }
    Setup<geode::Toggler> circleToggler(cocos2d::CCNode* off, cocos2d::CCNode* on, geode::Function<void(geode::Toggler*, bool)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor) {
        return Toggler::create(CircleButtonSprite::create(off, offColor), CircleButtonSprite::create(on, onColor), std::move(callback));
    }
    Setup<geode::Toggler> circleTogglerSprite(geode::ZStringView off, geode::ZStringView on, geode::Function<void(geode::Toggler*, bool)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor, float offScale, float onScale) {
        return Toggler::create(CircleButtonSprite::createWithSprite(off.c_str(), offScale, offColor), CircleButtonSprite::createWithSprite(on.c_str(), onScale, onColor), std::move(callback));
    }
    Setup<geode::Toggler> circleTogglerFrame(geode::ZStringView off, geode::ZStringView on, geode::Function<void(geode::Toggler*, bool)> callback, geode::CircleBaseColor offColor, geode::CircleBaseColor onColor, float offScale, float onScale) {
        return Toggler::create(CircleButtonSprite::createWithSpriteFrameName(off.c_str(), offScale, offColor), CircleButtonSprite::createWithSpriteFrameName(on.c_str(), onScale, onColor), std::move(callback));
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

    Setup<TextInput> input(CCSize size, std::optional<std::string> placeholder, TextInputCallback callback, ZStringView font) {
        auto input = TextInput::create(size, placeholder.value_or(""), font);
        input->setCallback(std::move(callback));
        return input;
    }
    Setup<TextInput> input(float width, float height, std::optional<std::string> placeholder, TextInputCallback callback, ZStringView font) {
        return input({width, height}, std::move(placeholder), std::move(callback), font);
    }
    Setup<TextInput> input(float width, std::optional<std::string> placeholder, TextInputCallback callback, ZStringView font) {
        auto input = TextInput::create(width, placeholder.value_or(""), font);
        input->setCallback(std::move(callback));
        return input;
    }
    Setup<TextInput> inputMultiline(CCSize size, std::optional<std::string> placeholder, TextInputCallback callback, ZStringView font) {
        auto input = TextInput::createMultiline(size, placeholder.value_or(""), font);
        input->setCallback(std::move(callback));
        return input;
    }
    Setup<TextInput> inputMultiline(float width, float height, std::optional<std::string> placeholder, TextInputCallback callback, ZStringView font) {
        return inputMultiline({width, height}, std::move(placeholder), std::move(callback), font);
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

    // Setup<geode::ButtonBackgroundSprite> buttonSprite(geode::ZStringView text, geode::ZStringView font, geode::ZStringView background) {
    //     return geode::ButtonBackgroundSprite::create(text, font, background);
    // }
    // Setup<geode::ButtonBackgroundSprite> buttonSprite(cocos2d::CCNode* node, geode::ZStringView background) {
    //     return geode::ButtonBackgroundSprite::createWithNode(node, background);
    // }
    // Setup<geode::ButtonBackgroundSprite> buttonSprite(cocos2d::CCNode* node, geode::ZStringView text, geode::ZStringView font, geode::ZStringView background) {
    //     return geode::ButtonBackgroundSprite::createWithNodeLabel(node, text, font, background);
    // }
}