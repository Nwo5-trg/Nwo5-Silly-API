#pragma once

#include "../export.hpp"
#include "constants.hpp"
#include "setup.hpp"

namespace nwo5::ui {
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> button(cocos2d::CCNode* pTop, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> button(cocos2d::CCNode* pTop, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> buttonSprite(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> buttonSprite(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> buttonFrame(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> buttonFrame(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemSpriteExtra> circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);

    SILLY_API_DLL Setup<CCMenuItemToggler> toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL Setup<CCMenuItemToggler> toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerBase(cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerBase(geode::Function<void(CCMenuItemToggler*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL Setup<CCMenuItemToggler> circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);

    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView pFont = Font::Default);
    SILLY_API_DLL Setup<geode::Label> label(geode::ZStringView pText, geode::ZStringView pFont);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView pFont = Font::Default);
    SILLY_API_DLL Setup<geode::Label> labelRich(geode::ZStringView pText, geode::ZStringView pFont);

    SILLY_API_DLL Setup<geode::TextInput> input(cocos2d::CCSize pSize, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float pWidth, float pHeight, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});
    SILLY_API_DLL Setup<geode::TextInput> input(float pWidth, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});

    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(bool pIgnoreAnchor);
    SILLY_API_DLL Setup<cocos2d::CCMenu> menu(geode::Layout* pLayout = nullptr, bool pIgnoreAnchor = false);

    SILLY_API_DLL Setup<cocos2d::CCNode> dummy(geode::Layout* pLayout = nullptr);

    SILLY_API_DLL Setup<geode::NineSlice> nineSlice(geode::ZStringView pTexture, geode::Layout* pLayout = nullptr);

    SILLY_API_DLL Setup<cocos2d::CCSprite> spr(geode::ZStringView pTexture);
    SILLY_API_DLL Setup<cocos2d::CCSprite> sprFrame(geode::ZStringView pTexture);

    SILLY_API_DLL Setup<geode::AxisLayout> row();
    SILLY_API_DLL Setup<geode::AxisLayout> column();
    SILLY_API_DLL Setup<geode::AnchorLayout> anchor();

    SILLY_API_DLL Setup<geode::AxisLayoutOptions> axisOptions();
    SILLY_API_DLL Setup<geode::AnchorLayoutOptions> anchorOptions();
}