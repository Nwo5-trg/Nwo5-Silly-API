#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    namespace impl {
        struct EditTabButton {
            using SpriteFunc = geode::Function<cocos2d::CCSprite*() const>;

            std::string key;
            int prio;

            float scale;
            SpriteFunc spriteFunc;
            cocos2d::SEL_MenuHandler callback;
        };

        SILLY_API_DLL int nextFreeGroupFast(int pOffset = 1);
        SILLY_API_DLL void createUndoObject(UndoCommand pCommand);
        SILLY_API_DLL void toggleMoveObject(bool pMove);
        SILLY_API_DLL CCMenuItemSpriteExtra* createEditTabButton(const EditTabButton& pButton);
    }

    /// get editorui and optionally reinterpret_cast it
    template<typename ImplT = EditorUI, typename T = std::remove_pointer_t<ImplT>>
    auto ui() {
        static const auto manager = GameManager::get();
        return reinterpret_cast<T*>(manager->m_levelEditorLayer->m_editorUI);
    };
    /// get leveleditorlayer and optionally reinterpret_cast it
    template<typename ImplT = LevelEditorLayer, typename T = std::remove_pointer_t<ImplT>>
    auto layer() {
        static const auto manager = GameManager::get();
        return reinterpret_cast<T*>(manager->m_levelEditorLayer);
    }
    
    SILLY_API_DLL bool loaded();

    SILLY_API_DLL void update(bool pUpdateControls = true, bool pOtherwiseDeactivateControls = false);

    SILLY_API_DLL float zoom();
    SILLY_API_DLL cocos2d::CCPoint center();

    SILLY_API_DLL void activateRotationControl(bool pRefresh = true);
    SILLY_API_DLL void activateScaleControl(bool pXY, bool pRefresh = true);
    SILLY_API_DLL void activateTransformControl(bool pRefresh = true);

    SILLY_API_DLL int currentLayer();
    SILLY_API_DLL bool layerSelectable(int pLayer, bool pIgnoreLocked = false);
    SILLY_API_DLL bool layerLocked(int pLayer);
    SILLY_API_DLL void setLayer(int pLayer);
    SILLY_API_DLL void lockLayer(int pLayer = currentLayer());

    /// get next free group
    /// @param pOffset search starts from this gid, clamped from 1-9999
    /// @note only accounts for target gid and center gid rn, ill do like sequence/advrand checks and stuff l8r
    /// @returns next free gid or 0 if all 9999 groups are used
    SILLY_API_DLL int nextFreeGroup(int pOffset = 1, bool pCheckTargetGroups = false);

    /// register an edit tab button 
    /// use literally wherever that runs before editorui init (or atleast before setupmovemenu)
    /// if registered multiple times does nothing
    /// @param pSprite sprite
    /// @param pKey identify the edit tab button with this, in overloads this is sprite name
    /// @param pScale sprite scale
    /// @param pPrio priority, priority in the negtives will move past vanilla editor buttons,
    /// @param pCallback callback
    /// @returns if the button was registered for the first time
    SILLY_API_DLL bool registerEditTabButton(impl::EditTabButton::SpriteFunc pSprite, std::string pKey, float pScale, int pPrio, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, float pScale, int pPrio, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, int pPrio, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, float pScale, int pPrio, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, int pPrio, cocos2d::SEL_MenuHandler pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, cocos2d::SEL_MenuHandler pCallback);
    /// unregister an edit tab button
    /// use literally wherever that runs before editorui init (or atleast before setupmovemenu)
    /// @param pKey will remove edit tab button with this key
    /// @param pRestore only matters for robtop buttons, remove button from remove queue
    /// @note for vanilla buttons use their node ids
    /// @returns if the button was unregistered
    SILLY_API_DLL bool unregisterEditTabButton(const std::string& pKey, bool pRestore = false);
    /// get an edit tab button
    /// @param pKey key of button to get
    /// @note for vanilla buttons use their node ids
    /// @note I AM NOT RESPONSIBLE FOR SHIT CRASHING WHEN FW ROBTOP BUTTONS
    /// @returns button or nullptr
    SILLY_API_DLL CCMenuItemSpriteExtra* getEditTabButton(const std::string& pKey);
    /// toggle an edit tab button
    /// @param pKey of button to toggle
    /// @note for vanilla buttons use their node ids
    SILLY_API_DLL void toggleEditTabButton(const std::string& pKey, bool pOn);

    constexpr cocos2d::CCPoint AUTO_CENTER{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
}