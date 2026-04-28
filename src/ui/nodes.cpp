#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    CCMenuItemSpriteExtra* button(cocos2d::CCNode* pTop, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback) {
        return CCMenuItemSpriteExtra::create(pTop, pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* button(cocos2d::CCNode* pTop, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback) {
        return CCMenuItemExt::createSpriteExtra(pTop, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* buttonSprite(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CCSprite::create(pName.c_str()), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* buttonSprite(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtraWithFilename(pName, pScale, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* buttonFrame(geode::ZStringView pName, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName(pName.c_str()), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* buttonFrame(geode::ZStringView pName, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtraWithFrameName(pName, pScale, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::create(pTop, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButton(cocos2d::CCNode* pTop, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::create(pTop, pColor), std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSprite(pName.c_str(), pScale, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButtonSprite(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::createWithSprite(pName.c_str(), pScale, pColor), std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName(pName.c_str(), pScale, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButtonFrame(geode::ZStringView pName, geode::CircleBaseColor pColor, geode::Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::createWithSpriteFrameName(pName.c_str(), pScale, pColor), std::move(pCallback));
    }

    CCMenuItemToggler* toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback) {
        return CCMenuItemToggler::create(pOff, pOn, pTarget, pCallback);
    }
    CCMenuItemToggler* toggler(cocos2d::CCNode* pOff, cocos2d::CCNode* pOn, geode::Function<void(CCMenuItemToggler*)> pCallback) {
        return CCMenuItemExt::createToggler(pOff, pOn, std::move(pCallback));
    }
    CCMenuItemToggler* togglerBase(cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemToggler::createWithStandardSprites(pTarget, pCallback, pScale);
    }
    CCMenuItemToggler* togglerBase(geode::Function<void(CCMenuItemToggler*)> pCallback, float pScale) {
        return CCMenuItemExt::createTogglerWithStandardSprites(pScale, std::move(pCallback));
    }
    CCMenuItemToggler* togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::create(pOff.c_str());
        auto on = CCSprite::create(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemToggler::create(off, on, pTarget, pCallback);
    }
    CCMenuItemToggler* togglerSprite(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::create(pOff.c_str());
        auto on = CCSprite::create(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemExt::createToggler(off, on, std::move(pCallback));
    }
    CCMenuItemToggler* togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::createWithSpriteFrameName(pOff.c_str());
        auto on = CCSprite::createWithSpriteFrameName(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemToggler::create(off, on, pTarget, pCallback);
    }
    CCMenuItemToggler* togglerFrame(geode::ZStringView pOff, geode::ZStringView pOn, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::createWithSpriteFrameName(pOff.c_str());
        auto on = CCSprite::createWithSpriteFrameName(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemExt::createToggler(off, on, std::move(pCallback));
    }
    CCMenuItemToggler* circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback) {
        return CCMenuItemToggler::create(CircleButtonSprite::create(pOff, pOffColor), CircleButtonSprite::create(pOn, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleToggler(cocos2d::CCNode* pOff, geode::CircleBaseColor pOffColor, cocos2d::CCNode* pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::create(pOff, pOffColor), CircleButtonSprite::create(pOn, pOnColor), std::move(pCallback));
    }
    CCMenuItemToggler* circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemToggler::create(CircleButtonSprite::createWithSprite(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSprite(pOn.c_str(), pOnScale, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleTogglerSprite(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSprite(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSprite(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }
    CCMenuItemToggler* circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemToggler::create(CircleButtonSprite::createWithSpriteFrameName(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSpriteFrameName(pOn.c_str(), pOnScale, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleTogglerFrame(geode::ZStringView pOff, geode::CircleBaseColor pOffColor, geode::ZStringView pOn, geode::CircleBaseColor pOnColor, geode::Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSpriteFrameName(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSpriteFrameName(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }

    cocos2d::CCLabelBMFont* label(geode::ZStringView pText, geode::ZStringView pFont) {
        return CCLabelBMFont::create(pText.c_str(), pFont.c_str());
    }

    geode::TextInput* input(cocos2d::CCSize pSize, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        const float scale = pSize.height / DEFAULT_TEXT_INPUT_HEIGHT;

        auto textInput = TextInput::create(pSize.width / scale, pPlaceholder.value());
        textInput->setCallback(std::move(pCallback));
        textInput->setString(pStartingString.value());
        textInput->setScale(scale);

        return textInput;
    }
    geode::TextInput* input(float pWidth, float pHeight, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        return input({pWidth, pHeight}, std::move(pStartingString), std::move(pPlaceholder), std::move(pCallback));
    }
    geode::TextInput* input(float pWidth, std::optional<std::string> pStartingString, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        auto textInput = TextInput::create(pWidth, pPlaceholder.value());
        textInput->setCallback(std::move(pCallback));
        textInput->setString(pStartingString.value());

        return textInput;
    }

    geode::AxisLayout* horizontalDistrbLayout(float pGap, geode::AxisAlignment pAlignment) {
        return RowLayout::create()
            ->setGap(pGap)
            ->setAxisAlignment(pAlignment)
            ->setAutoGrowAxis(true)
            ->setGrowCrossAxis(false)
            ->setAutoScale(false);

    }
    geode::AxisLayout* verticalDistrbLayout(float pGap, geode::AxisAlignment pAlignment) {
        return ColumnLayout::create()
            ->setGap(pGap)
            ->setAxisAlignment(pAlignment)
            ->setAutoGrowAxis(true)
            ->setGrowCrossAxis(false)
            ->setAutoScale(false);
    }
}