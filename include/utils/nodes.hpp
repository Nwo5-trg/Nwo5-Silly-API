#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    struct SILLY_API_DLL GetChildQueryBase {};
    // i should prolly split this into multiple types but ill do that some other time (never)
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    struct GetChildQuery : GetChildQueryBase {
        const std::string id;
        const int index{};

        GetChildQuery()
            = default;
        GetChildQuery(int pIndex)
            : index(pIndex) {}
        GetChildQuery(std::string_view pID)
            : id(pID) {}

        cocos2d::CCNode* query(cocos2d::CCNode* pNode) {
            if (id.empty()) {
                return pNode->getChildByType<T*>(index);
            }
            else {
                if constexpr (std::same_as<T, cocos2d::CCNode>) {
                    return pNode->getChildByID(id);
                }
                else {
                    return geode::cast::typeinfo_cast<T*>(pNode->getChildByID(id));
                }
            }
        }
    };
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryID = GetChildQuery<T>;
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryIndex = GetChildQuery<T>;
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryType = GetChildQuery<T>;
    
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>, typename... Args>
    requires (std::derived_from<Args, GetChildQueryBase> && ...)
    T* getNestedChildSafe(cocos2d::CCNode* pNode, Args... pArgs) {
        if (!pNode) {
            return nullptr;
        }

        auto node = static_cast<cocos2d::CCNode*>(pNode);

        ([&] -> bool {
            return (node = pArgs.query(node));
        }() && ...);

        if constexpr (std::same_as<T, cocos2d::CCNode>) {
            return node;
        }
        else {
            return geode::cast::typeinfo_cast<T*>(node);
        }
    }

    constexpr float DEFAULT_TEXT_INPUT_HEIGHT = 30.0f;
    using TextInputCallback = geode::Function<void(const std::string&)>;

    SILLY_API_DLL geode::TextInput* createTextInput(float pWidth, float pHeight, const std::string& pPlaceholder, const std::string& pFont, TextInputCallback pCallback = [] (const std::string&) {});
    SILLY_API_DLL geode::TextInput* createTextInput(float pWidth, float pHeight, const std::string& pPlaceholder = "", TextInputCallback pCallback = [] (const std::string&) {});
    SILLY_API_DLL geode::TextInput* createTextInput(float pWidth, const std::string& pPlaceholder, const std::string& pFont, TextInputCallback pCallback = [] (const std::string&) {});
    SILLY_API_DLL geode::TextInput* createTextInput(float pWidth, const std::string& pPlaceholder = "", TextInputCallback pCallback = [] (const std::string&) {});

    SILLY_API_DLL CCMenuItemSpriteExtra* createCircleButton(const std::string& pTexture, geode::CircleBaseColor pColor, geode::CircleBaseSize pSize, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* createCircleButton(const std::string& pTexture, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* createCircleButtonFrame(const std::string& pTexture, geode::CircleBaseColor pColor, geode::CircleBaseSize pSize, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* createCircleButtonFrame(const std::string& pTexture, geode::CircleBaseColor pColor, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* createButton(const std::string& pTexture, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    SILLY_API_DLL CCMenuItemSpriteExtra* createButtonFrame(const std::string& pTexture, cocos2d::CCObject* pTarget, cocos2d::SEL_MenuHandler pCallback, float pScale = 1.0f);
    
    constexpr cocos2d::CCPoint TOP_RIGHT_ANCHOR = {1.0f, 1.0f};
    constexpr cocos2d::CCPoint TOP_CENTER_ANCHOR = {0.5f, 1.0f};
    constexpr cocos2d::CCPoint TOP_LEFT_ANCHOR = {0.0f, 1.0f};
    constexpr cocos2d::CCPoint LEFT_CENTER_ANCHOR = {0.0f, 0.5f};
    constexpr cocos2d::CCPoint BOTTOM_LEFT_ANCHOR = {0.0f, 0.0f};
    constexpr cocos2d::CCPoint BOTTOM_CENTER_ANCHOR = {0.5f, 0.0f};
    constexpr cocos2d::CCPoint BOTTOM_RIGHT_ANCHOR = {1.0f, 0.0f};
    constexpr cocos2d::CCPoint RIGHT_CENTER_ANCHOR = {1.0f, 0.5f};
    constexpr cocos2d::CCPoint CENTER_ANCHOR = {0.5f, 0.5f};
}