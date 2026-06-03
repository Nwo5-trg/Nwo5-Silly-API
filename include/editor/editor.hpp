#pragma once

#include "../export.hpp"

namespace nwo5::editor {
    namespace impl {
        SILLY_API_DLL void createUndoObject(UndoCommand pCommand);
        SILLY_API_DLL void toggleMoveObject(bool pMove);
        SILLY_API_DLL EditorUI* getEditorUI();
    }

    /// get editorui and optionally reinterpret_cast it
    template<typename ImplT = EditorUI, typename T = std::remove_pointer_t<ImplT>>
    auto ui() {
        return reinterpret_cast<T*>(impl::getEditorUI());
    };
    /// get leveleditorlayer and optionally reinterpret_cast it
    template<typename ImplT = LevelEditorLayer, typename T = std::remove_pointer_t<ImplT>>
    auto layer() {
        static const auto manager = GameManager::get();
        return reinterpret_cast<T*>(manager->m_levelEditorLayer);
    }

    enum class LoadedType {
        /// editorlayer initialized
        Editor,
        /// editorlayer (valid right before init starts)
        EditorValid,
        /// editorui initialized
        UI,
        /// editorui (right before init starts)
        UIValid
    };
    
    /// check LoadedType docs
    SILLY_API_DLL bool loaded(LoadedType pType = LoadedType::Editor);
    /// same as !loaded()
    SILLY_API_DLL bool notLoaded(LoadedType pType = LoadedType::Editor);

    /// call pretty much every editor update function (e.g. updating ui buttons, obj info label)
    SILLY_API_DLL void update(bool pUpdateControls = true, bool pOtherwiseDeactivateControls = false);

    /// get editor soom
    /// @returns editor zoom
    SILLY_API_DLL float zoom();
    /// center of editor in objectlayer position
    /// @param pToolbar whether to account for toolbarheight
    /// @returns center
    SILLY_API_DLL cocos2d::CCPoint center(bool pToolbar = true);
    /// size of visible objectlayer
    /// @param pToolbar whether to account for toolbarheight
    /// @returns size
    SILLY_API_DLL cocos2d::CCSize size(bool pToolbar = true);
    
    /// move editor to position (objectlayer position)
    SILLY_API_DLL void move(cocos2d::CCPoint pPos);

    /// LevelEditorLayer::m_playbackMode == PlaybackMode::Playing
    SILLY_API_DLL bool isPlaytesting();
    /// LevelEditorLayer::m_playbackMode
    SILLY_API_DLL PlaybackMode playbackMode();

    SILLY_API_DLL void activateRotationControl(bool pRefresh = true);
    SILLY_API_DLL void activateScaleControl(bool pXY, bool pRefresh = true);
    SILLY_API_DLL void activateTransformControl(bool pRefresh = true);

    /// get current layer
    /// @returns current layer or editor::constants::ALL_LAYERS if editor not loaded
    SILLY_API_DLL int currentLayer();
    /// get if layer is selectable
    SILLY_API_DLL bool layerSelectable(int pLayer = currentLayer(), bool pIgnoreLocked = false);
    SILLY_API_DLL bool layerLocked(int pLayer = currentLayer());
    SILLY_API_DLL void setLayer(int pLayer);
    SILLY_API_DLL void lockLayer(int pLayer, bool pLock);

    /// saves current level
    SILLY_API_DLL void save();

    /// get next free group
    /// @param pOffset search starts from this gid, clamped from 1-9999
    /// @note only accounts for target gid and center gid rn, ill do like sequence/advrand checks and stuff l8r
    /// @returns next free gid or 0 if all 9999 groups are used
    SILLY_API_DLL int nextFreeGroup(int pOffset = 1, bool pCheckTargetGroups = false);

    namespace impl {
        struct SILLY_API_DLL EditTabButton {
            using SpriteFunc = geode::Function<cocos2d::CCSprite*() const>;
            using Callback = geode::CopyableFunction<void(CCMenuItemSpriteExtra*)>;

            std::string key;
            int prio;

            float scale;
            SpriteFunc spriteFunc;
            Callback callback;
        };
    }

    /// register an edit tab button 
    /// use literally wherever that runs before editorui init (or atleast before setupmovemenu)
    /// if registered multiple times does nothing
    /// @param pSprite sprite
    /// @param pKey identify the edit tab button with this (u should use _spr prefix if u want any hope of mod compatibility btw sowwy not sowwy)
    /// @param pScale sprite scale
    /// @param pPrio priority, priority in the negtives will move past robtop editor buttons,
    /// @param pCallback callback
    /// @returns if the button was registered
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
    /// @note for other buttons use node ids
    /// @note will prolly get rewritten later i js cant b fucked rn
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
    /// registers button if condition is true, unregisters if condition is false
    /// useful for buttons enabled by setting
    template<typename... Args>
    void conditionallyRegister(bool pCondition, std::string pSprite, std::string pKey, Args&&... pArgs) {
        if (pCondition) {
            registerEditTabButton(std::move(pSprite), std::move(pKey), std::forward<Args>(pArgs)...);
        }
        else {
            unregisterEditTabButton(pKey);
        }
    }
    /// registers button if condition is true, unregisters if condition is false
    /// useful for buttons enabled by setting
    template<typename... Args>
    void conditionallyRegisterFrame(bool pCondition, std::string pSprite, std::string pKey, Args&&... pArgs) {
        if (pCondition) {
            registerEditTabButtonFrame(std::move(pSprite), std::move(pKey), std::forward<Args>(pArgs)...);
        }
        else {
            unregisterEditTabButton(pKey);
        }
    }
    SILLY_API_DLL void updateEditorTabButtons();

    constexpr cocos2d::CCPoint AUTO_CENTER{std::numeric_limits<float>::max() - 1.0f, std::numeric_limits<float>::max() - 1.0f};
}