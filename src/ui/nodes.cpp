#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    CCMenuItemSpriteExtra* button(CCNode* pTop, CCObject* pTarget, SEL_MenuHandler pCallback) {
        return CCMenuItemSpriteExtra::create(pTop, pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* button(CCNode* pTop, Function<void(CCMenuItemSpriteExtra*)> pCallback) {
        return CCMenuItemExt::createSpriteExtra(pTop, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* buttonSprite(ZStringView pName, CCObject* pTarget, SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CCSprite::create(pName.c_str()), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* buttonSprite(ZStringView pName, Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtraWithFilename(pName, pScale, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* buttonFrame(ZStringView pName, CCObject* pTarget, SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName(pName.c_str()), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* buttonFrame(ZStringView pName, Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtraWithFrameName(pName, pScale, std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButton(CCNode* pTop, CircleBaseColor pColor, CCObject* pTarget, SEL_MenuHandler pCallback) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::create(pTop, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButton(CCNode* pTop, CircleBaseColor pColor, Function<void(CCMenuItemSpriteExtra*)> pCallback) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::create(pTop, pColor), std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButtonSprite(ZStringView pName, CircleBaseColor pColor, CCObject* pTarget, SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSprite(pName.c_str(), pScale, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButtonSprite(ZStringView pName, CircleBaseColor pColor, Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::createWithSprite(pName.c_str(), pScale, pColor), std::move(pCallback));
    }
    CCMenuItemSpriteExtra* circleButtonFrame(ZStringView pName, CircleBaseColor pColor, CCObject* pTarget, SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemSpriteExtra::create(CircleButtonSprite::createWithSpriteFrameName(pName.c_str(), pScale, pColor), pTarget, pCallback);
    }
    CCMenuItemSpriteExtra* circleButtonFrame(ZStringView pName, CircleBaseColor pColor, Function<void(CCMenuItemSpriteExtra*)> pCallback, float pScale) {
        return CCMenuItemExt::createSpriteExtra(CircleButtonSprite::createWithSpriteFrameName(pName.c_str(), pScale, pColor), std::move(pCallback));
    }

    CCMenuItemToggler* toggler(CCNode* pOff, CCNode* pOn, CCObject* pTarget, SEL_MenuHandler pCallback) {
        return CCMenuItemToggler::create(pOff, pOn, pTarget, pCallback);
    }
    CCMenuItemToggler* toggler(CCNode* pOff, CCNode* pOn, Function<void(CCMenuItemToggler*)> pCallback) {
        return CCMenuItemExt::createToggler(pOff, pOn, std::move(pCallback));
    }
    CCMenuItemToggler* togglerBase(CCObject* pTarget, SEL_MenuHandler pCallback, float pScale) {
        return CCMenuItemToggler::createWithStandardSprites(pTarget, pCallback, pScale);
    }
    CCMenuItemToggler* togglerBase(Function<void(CCMenuItemToggler*)> pCallback, float pScale) {
        return CCMenuItemExt::createTogglerWithStandardSprites(pScale, std::move(pCallback));
    }
    CCMenuItemToggler* togglerSprite(ZStringView pOff, ZStringView pOn, CCObject* pTarget, SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::create(pOff.c_str());
        auto on = CCSprite::create(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemToggler::create(off, on, pTarget, pCallback);
    }
    CCMenuItemToggler* togglerSprite(ZStringView pOff, ZStringView pOn, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::create(pOff.c_str());
        auto on = CCSprite::create(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemExt::createToggler(off, on, std::move(pCallback));
    }
    CCMenuItemToggler* togglerFrame(ZStringView pOff, ZStringView pOn, CCObject* pTarget, SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::createWithSpriteFrameName(pOff.c_str());
        auto on = CCSprite::createWithSpriteFrameName(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemToggler::create(off, on, pTarget, pCallback);
    }
    CCMenuItemToggler* togglerFrame(ZStringView pOff, ZStringView pOn, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        auto off = CCSprite::createWithSpriteFrameName(pOff.c_str());
        auto on = CCSprite::createWithSpriteFrameName(pOn.c_str());
        off->setScale(pOffScale);
        on->setScale(pOnScale);
        return CCMenuItemExt::createToggler(off, on, std::move(pCallback));
    }
    CCMenuItemToggler* circleToggler(CCNode* pOff, CircleBaseColor pOffColor, CCNode* pOn, CircleBaseColor pOnColor, CCObject* pTarget, SEL_MenuHandler pCallback) {
        return CCMenuItemToggler::create(CircleButtonSprite::create(pOff, pOffColor), CircleButtonSprite::create(pOn, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleToggler(CCNode* pOff, CircleBaseColor pOffColor, CCNode* pOn, CircleBaseColor pOnColor, Function<void(CCMenuItemToggler*)> pCallback) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::create(pOff, pOffColor), CircleButtonSprite::create(pOn, pOnColor), std::move(pCallback));
    }
    CCMenuItemToggler* circleTogglerSprite(ZStringView pOff, CircleBaseColor pOffColor, ZStringView pOn, CircleBaseColor pOnColor, CCObject* pTarget, SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemToggler::create(CircleButtonSprite::createWithSprite(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSprite(pOn.c_str(), pOnScale, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleTogglerSprite(ZStringView pOff, CircleBaseColor pOffColor, ZStringView pOn, CircleBaseColor pOnColor, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSprite(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSprite(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }
    CCMenuItemToggler* circleTogglerFrame(ZStringView pOff, CircleBaseColor pOffColor, ZStringView pOn, CircleBaseColor pOnColor, CCObject* pTarget, SEL_MenuHandler pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemToggler::create(CircleButtonSprite::createWithSpriteFrameName(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSpriteFrameName(pOn.c_str(), pOnScale, pOnColor), pTarget, pCallback);
    }
    CCMenuItemToggler* circleTogglerFrame(ZStringView pOff, CircleBaseColor pOffColor, ZStringView pOn, CircleBaseColor pOnColor, Function<void(CCMenuItemToggler*)> pCallback, float pOffScale, float pOnScale) {
        return CCMenuItemExt::createToggler(CircleButtonSprite::createWithSpriteFrameName(pOff.c_str(), pOffScale, pOffColor), CircleButtonSprite::createWithSpriteFrameName(pOn.c_str(), pOnScale, pOnColor), std::move(pCallback));
    }

    CCLabelBMFont* label(ZStringView pText, ZStringView pFont) {
        return CCLabelBMFont::create(pText.c_str(), pFont.c_str());
    }

    TextInput* input(CCSize pSize, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        const float scale = pSize.height / DEFAULT_TEXT_INPUT_HEIGHT;

        auto textInput = TextInput::create(pSize.width / scale, pPlaceholder.value_or(""));
        textInput->setCallback(std::move(pCallback));
        textInput->setScale(scale);

        return textInput;
    }
    TextInput* input(float pWidth, float pHeight, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        return input({pWidth, pHeight}, std::move(pPlaceholder), std::move(pCallback));
    }
    TextInput* input(float pWidth, std::optional<std::string> pPlaceholder, TextInputCallback pCallback) {
        auto textInput = TextInput::create(pWidth, pPlaceholder.value());
        textInput->setCallback(std::move(pCallback));

        return textInput;
    }

    CCMenu* menu(AxisLayout* pLayout) {
        auto node = CCMenu::create();

        if (pLayout) {
            node->setLayout(pLayout, false);
        }

        return node;
    }

    AxisLayout* horizontalDistrbLayout(float pGap, AxisAlignment pAlignment) {
        return RowLayout::create()
            ->setGap(pGap)
            ->setAxisAlignment(pAlignment)
            ->setAutoGrowAxis(true)
            ->setGrowCrossAxis(false)
            ->setAutoScale(false);

    }
    AxisLayout* verticalDistrbLayout(float pGap, AxisAlignment pAlignment) {
        return ColumnLayout::create()
            ->setGap(pGap)
            ->setAxisAlignment(pAlignment)
            ->setAutoGrowAxis(true)
            ->setGrowCrossAxis(false)
            ->setAutoScale(false);
    }
}