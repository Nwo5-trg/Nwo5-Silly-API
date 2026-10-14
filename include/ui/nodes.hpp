#pragma once

#include "../export.hpp"
#include "constants.hpp"
#include "setup.hpp"

namespace nwo5::ui {
    SILLY_API_DLL Setup<geode::Button> button(cocos2d::CCNode* pTop, geode::Function<void(geode::Button*)> pCallback);
    SILLY_API_DLL Setup<geode::Button> buttonSprite(geode::ZStringView pName, geode::Function<void(geode::Button*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> buttonFrame(geode::ZStringView pName, geode::Function<void(geode::Button*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> circleButton(cocos2d::CCNode* pTop, geode::Function<void(geode::Button*)> pCallback, geode::CircleBaseColor pColor = geode::CircleBaseColor::Green);
    SILLY_API_DLL Setup<geode::Button> circleButtonSprite(geode::ZStringView pName, geode::Function<void(geode::Button*)> pCallback, geode::CircleBaseColor pColor = geode::CircleBaseColor::Green, float pScale = 1.0f);
    SILLY_API_DLL Setup<geode::Button> circleButtonFrame(geode::ZStringView pName, geode::Function<void(geode::Button*)> pCallback, geode::CircleBaseColor pColor = geode::CircleBaseColor::Green, float pScale = 1.0f);

    SILLY_API_DLL Setup<CCMenuItemToggler> toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerBase(geode::Function<void(CCMenuItemToggler*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor = geode::CircleBaseColor::Green, geode::CircleBaseColor pOnColor = geode::CircleBaseColor::Green);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor = geode::CircleBaseColor::Green, geode::CircleBaseColor pOnColor = geode::CircleBaseColor::Green, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, geode::CircleBaseColor pOffColor = geode::CircleBaseColor::Green, geode::CircleBaseColor pOnColor = geode::CircleBaseColor::Green, float pOffScale = 1.0f, float pOnScale = 1.0f);

    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView pFont = Font::Default);
    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView pText, geode::ZStringView pFont);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView pFont = Font::Default);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView pText, geode::ZStringView pFont);

    SILLY_API_DLL Setup<geode::TextInput> input(cocos2d::CCSize pSize, std::optional<std::string> pPlaceholder = std::nullopt, TextInputCallback pCallback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float pWidth, float pHeight, std::optional<std::string> pPlaceholder = std::nullopt, TextInputCallback pCallback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float pWidth, std::optional<std::string> pPlaceholder = std::nullopt, TextInputCallback pCallback = {});

    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(bool pIgnoreAnchor);
    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(geode::Layout* pLayout = nullptr, bool pIgnoreAnchor = false);

    SILLY_API_DLL Setup<cocos2d::CCNode> dummy(geode::Layout* pLayout = nullptr);

    SILLY_API_DLL Setup<geode::NineSlice> nineSlice(geode::ZStringView pTexture, float pScaleMultiplier = 1.0);

    SILLY_API_DLL Setup<cocos2d::CCSprite> sprite(geode::ZStringView pTexture);
    SILLY_API_DLL Setup<cocos2d::CCSprite> frame(geode::ZStringView pTexture);

    SILLY_API_DLL Setup<geode::AxisLayout> row();
    SILLY_API_DLL Setup<geode::AxisLayout> column();
    SILLY_API_DLL Setup<geode::AnchorLayout> anchor();

    SILLY_API_DLL Setup<geode::AxisLayoutOptions> axisOptions();
    SILLY_API_DLL Setup<geode::AnchorLayoutOptions> anchorOptions();
}