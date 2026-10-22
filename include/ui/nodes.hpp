#pragma once

#include "../export.hpp"
#include "constants.hpp"
#include "setup.hpp"

namespace nwo5::ui {
    SILLY_API_DLL Setup<geode::Button> button(cocos2d::CCNode* top, geode::Function<void(geode::Button*)> callback);
    SILLY_API_DLL Setup<geode::Button> buttonSprite(geode::ZStringView name, geode::Function<void(geode::Button*)> callback, float scale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> buttonFrame(geode::ZStringView name, geode::Function<void(geode::Button*)> callback, float scale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> circleButton(cocos2d::CCNode* top, geode::Function<void(geode::Button*)> callback, geode::CircleBaseColor color = geode::CircleBaseColor::Green);
    SILLY_API_DLL Setup<geode::Button> circleButtonSprite(geode::ZStringView name, geode::Function<void(geode::Button*)> callback, geode::CircleBaseColor color = geode::CircleBaseColor::Green, float scale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> circleButtonFrame(geode::ZStringView name, geode::Function<void(geode::Button*)> callback, geode::CircleBaseColor color = geode::CircleBaseColor::Green, float scale = 1.0f);

    SILLY_API_DLL Setup<CCMenuItemToggler> toggler(cocos2d::CCNode* off, cocos2d::CCNode* on, geode::Function<void(CCMenuItemToggler*)> callback);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerBase(geode::Function<void(CCMenuItemToggler*)> callback, float scale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerSprite(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, float offScale = 1.0f, float onScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerFrame(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, float offScale = 1.0f, float onScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* off, cocos2d::CCNode* on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor = geode::CircleBaseColor::Green, geode::CircleBaseColor onColor = geode::CircleBaseColor::Green);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor = geode::CircleBaseColor::Green, geode::CircleBaseColor onColor = geode::CircleBaseColor::Green, float offScale = 1.0f, float onScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView off, geode::ZStringView on, geode::Function<void(CCMenuItemToggler*)> callback, geode::CircleBaseColor offColor = geode::CircleBaseColor::Green, geode::CircleBaseColor onColor = geode::CircleBaseColor::Green, float offScale = 1.0f, float onScale = 1.0f);

    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView font = Font::Default);
    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView text, geode::ZStringView font);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView font = Font::Default);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView text, geode::ZStringView font);

    SILLY_API_DLL Setup<geode::TextInput> input(cocos2d::CCSize size, std::optional<std::string> placeholder = std::nullopt, TextInputCallback callback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float width, float height, std::optional<std::string> placeholder = std::nullopt, TextInputCallback callback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float width, std::optional<std::string> placeholder = std::nullopt, TextInputCallback callback = {});

    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(bool ignoreAnchor);
    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(geode::Layout* layout = nullptr, bool ignoreAnchor = false);

    SILLY_API_DLL Setup<cocos2d::CCNode> dummy(geode::Layout* layout = nullptr);

    SILLY_API_DLL Setup<geode::NineSlice> nineSlice(geode::ZStringView texture, float scaleMultiplier = 1.0);

    SILLY_API_DLL Setup<cocos2d::CCSprite> sprite(geode::ZStringView texture);
    SILLY_API_DLL Setup<cocos2d::CCSprite> frame(geode::ZStringView texture);

    SILLY_API_DLL Setup<geode::AxisLayout> row();
    SILLY_API_DLL Setup<geode::AxisLayout> column();
    SILLY_API_DLL Setup<geode::AnchorLayout> anchor();

    SILLY_API_DLL Setup<geode::AxisLayoutOptions> axisOptions();
    SILLY_API_DLL Setup<geode::AnchorLayoutOptions> anchorOptions();
}