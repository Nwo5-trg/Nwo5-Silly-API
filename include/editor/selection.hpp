#pragma once

#include "editor.hpp"

namespace nwo5::editor::selection {
    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    std::vector<T*> get() {
        if (notLoaded()) {
            return std::vector<T*>{};
        }
        
        if (auto obj = ui()->m_selectedObject) {
            return std::vector<T*>{obj};
        }
        else {
            return geode::cocos::CCArrayExt<T>(ui()->getSelectedObjects()).toVector();
        }
    }
    template<typename ImplT = cocos2d::CCArray, typename T = std::remove_pointer_t<ImplT>>
    requires std::same_as<T, cocos2d::CCArray>
    T* get() {
        if (notLoaded()) {
            return cocos2d::CCArray::create();
        }

        if (ui()->m_selectedObject) {
            return cocos2d::CCArray::createWithObject(ui()->m_selectedObject);
        }
        else {
            auto out = cocos2d::CCArray::createWithCapacity(ui()->m_selectedObjects->capacity());

            for (auto obj : geode::cocos::CCArrayExt(ui()->m_selectedObjects)) {
                out->addObject(obj);
            }

            return out;
        }
    }
    template<typename T = GameObject*>
    auto getExt() {
        return geode::cocos::CCArrayExt<T>(get());
    } 
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    T* getFirst() {
        if (notLoaded()) {
            return nullptr;
        }
        else if (auto obj = ui()->m_selectedObject) {
            return static_cast<T*>(obj);
        }
        else if (auto objs = ui()->m_selectedObjects; objs && objs->count()) {
            return static_cast<T*>(objs->firstObject());
        }
        else {
            return nullptr;
        }
    }
    
    SILLY_API_DLL bool empty();
    SILLY_API_DLL size_t count();

    SILLY_API_DLL cocos2d::CCRect bounds();
    SILLY_API_DLL cocos2d::CCPoint center(bool ignoreParent = false);

    /// add object to selection
    /// @param obj obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void add(GameObject* obj, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);
    /// add objects to selection
    /// @param objs obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void add(std::span<GameObject* const> objs, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);
    /// add objects to selection
    /// @param objs obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void add(cocos2d::CCArray* objs, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);
    /// set selection to only object
    /// @param obj obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void set(GameObject* obj, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);
    /// set selection to only objects
    /// @param objs obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void set(std::span<GameObject* const> objs, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);
    /// set selection to only objects
    /// @param objs obj to select
    /// @param undo make the selection undoable
    /// @param useFilter whether to check select filter
    /// @param alsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param applyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (if link groups are enabled, however robtop handles that no promises)
    SILLY_API_DLL void set(cocos2d::CCArray* objs, bool undo = false, bool useFilter = false, bool alsoCheckLayers = true, bool applyLinkControls = false);

    SILLY_API_DLL void clear(bool undo = false);
    SILLY_API_DLL void remove(GameObject* obj, bool undo = false);
    SILLY_API_DLL void remove(std::span<GameObject* const> objs, bool undo = false);
    SILLY_API_DLL void remove(cocos2d::CCArray* objs, bool undo = false);

    /// updates objects selection color again
    SILLY_API_DLL void repairColors(std::span<GameObject* const> objs);
    /// updates objects selection color again
    SILLY_API_DLL void repairColors(cocos2d::CCArray* objs = get());
}