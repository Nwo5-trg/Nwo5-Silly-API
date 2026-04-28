#pragma once

#include "../export.hpp"
#include "constants.hpp"

namespace nwo5::ui {
    SILLY_API_DLL CCMenuItemSpriteExtra* button(cocos2d::CCNode* pTop, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL CCMenuItemSpriteExtra* button(cocos2d::CCNode* pTop, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback);
    SILLY_API_DLL CCMenuItemSpriteExtra* buttonSprite(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* buttonSprite(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* buttonFrame(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* buttonFrame(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale = 1.0f);

    SILLY_API_DLL CCMenuItemToggler* toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL CCMenuItemToggler* toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback);
    SILLY_API_DLL CCMenuItemToggler* togglerBase(cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* togglerBase(geode::Function<void(CCMenuItemToggler*)> pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL CCMenuItemToggler* circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback);
    SILLY_API_DLL CCMenuItemToggler* circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);
    SILLY_API_DLL CCMenuItemToggler* circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale = 1.0f, float pOnScale = 1.0f);

    SILLY_API_DLL cocos2d::CCLabelBMFont* label(geode::ZStringView pText = "", geode::ZStringView pFont = Font::Default);

    SILLY_API_DLL geode::TextInput* input(cocos2d::CCSize pSize, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});
    SILLY_API_DLL geode::TextInput* input(float pWidth, float pHeight, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});
    SILLY_API_DLL geode::TextInput* input(float pWidth, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback = {});

    /// no auto scale, grows axis, no cross axis
    SILLY_API_DLL geode::AxisLayout* horizontalDistrbLayout(float pGap, geode::AxisAlignment pAlignment = geode::AxisAlignment::Start);
    /// no auto scale, grows axis, no cross axis
    SILLY_API_DLL geode::AxisLayout* verticalDistrbLayout(float pGap, geode::AxisAlignment pAlignment = geode::AxisAlignment::Start);
}