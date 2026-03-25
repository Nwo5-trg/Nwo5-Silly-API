#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    namespace impl {
        struct EditTabButton {
            using SpriteFunc = geode::Function<cocos2d::CCSprite*() const>;
            using Callback = geode::CopyableFunction<void(CCMenuItemSpriteExtra*)>;

            std::string key;
            int prio;

            float scale;
            SpriteFunc spriteFunc;
            Callback callback;
        };

        SILLY_API_DLL void createUndoObject(UndoCommand pCommand);
        SILLY_API_DLL void toggleMoveObject(bool pMove);
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
    /// @param pKey identify the edit tab button with this (u should use _spr prefix if u want any hope of mod compatibility btw sowwy not sowwy)
    /// @param pScale sprite scale
    /// @param pPrio priority, priority in the negtives will move past robtop editor buttons,
    /// @param pCallback callback
    /// @returns if the button was registered for the first time
    SILLY_API_DLL bool registerEditTabButton(impl::EditTabButton::SpriteFunc pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, std::string pKey, int pPrio, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButton(std::string pSprite, std::string pKey, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, float pScale, int pPrio, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, int pPrio, impl::EditTabButton::Callback pCallback);
    SILLY_API_DLL bool registerEditTabButtonFrame(std::string pSprite, std::string pKey, impl::EditTabButton::Callback pCallback);
    /// unregister an edit tab button
    /// use literally wherever that runs before editorui init (or atleast before setupmovemenu)
    /// completely unregisters a button if it was registered in same mod
    /// otherwise if its a robtop button or button added by another mod will just be made invisible and omitted from buttonarray
    /// @param pKey will remove edit tab button with this key
    /// @param pRestore only matters for other modded buttons/robtop buttons, remove button from remove list
    /// @note for robtop buttons use their node ids
    /// @returns if the button was unregistered/restored
    SILLY_API_DLL bool unregisterEditTabButton(const std::string& pKey, bool pRestore = false);
    /// get if a button is registered
    /// @param pKey edit tab button
    /// @returns basically just checks if the edit tab button is visible and usable
    SILLY_API_DLL bool isEditTabButtonRegistered(const std::string& pKey);
    /// get an edit tab button
    /// @param pKey key of button to get
    /// @note for robtop buttons use their node ids
    /// @returns button or searches for a button with the node id pKey (totally safely and totally doesnt just do a nodebyidrecursive call on editbuttonbar)
    SILLY_API_DLL CCMenuItemSpriteExtra* getEditTabButton(const std::string& pKey);
    /// toggle an edit tab button
    /// @param pKey of button to toggle
    /// @note for robtop buttons use their node ids
    SILLY_API_DLL void toggleEditTabButton(const std::string& pKey, bool pOn);

    constexpr cocos2d::CCPoint AUTO_CENTER{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
}