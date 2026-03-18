#pragma once

#include "editor.hpp"

namespace nwo5::editor::selection {
    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    std::vector<T*> get() {
        if (auto obj = ui()->m_selectedObject) {
            return {obj};
        }
        else {
            return geode::cocos::CCArrayExt<T>(ui()->m_selectedObjects).toVector();
        }
    }
    template<typename ImplT = cocos2d::CCArray, typename T = std::remove_pointer_t<ImplT>>
    requires std::same_as<T, cocos2d::CCArray>
    T* get(bool pCopy = false) {
        if (auto obj = ui()->m_selectedObject) {
            return cocos2d::CCArray::createWithObject(obj);
        }
        else {
            return pCopy ? cocos2d::CCArray::createWithArray(ui()->m_selectedObjects) : ui()->m_selectedObjects;
        }
    }
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    auto getExt(bool pCopy = false) {
        return geode::cocos::CCArrayExt<T*>(get(pCopy));
    } 
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    T* getFirst() {
        if (auto obj = ui()->m_selectedObject) {
            return static_cast<T*>(obj);
        }
        else if (auto objs = ui()->m_selectedObjects; objs->count()) {
            return static_cast<T*>(objs->firstObject());
        }
        else {
            return nullptr;
        }
    }
    /// get vector specializations but typeinfo_cast instead of static_cast
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    std::vector<T*> getType() {
        if constexpr (std::same_as<T, GameObject>) {
            return get<T>();
        }
            
        if (auto obj = ui()->m_selectedObject; obj && geode::cast::typeinfo_cast<T*>(obj)) {
            return {static_cast<T*>(obj)};
        }
        else {
            std::vector<T*> out;
            out.reserve(ui()->m_selectedObjects->count());

            for (auto obj : geode::cocos::CCArrayExt<T*>(ui()->m_selectedObjects)) {
                if constexpr (std::derived_from<T, EffectGameObject>) {
                    if (obj->m_classType != GameObjectClassType::Effect) {
                        continue;
                    }
                }
                else if constexpr (std::derived_from<T, EnhancedGameObject>) {
                    if (obj->m_classType != GameObjectClassType::Enhanced) {
                        continue;
                    }
                }

                if (auto casted = geode::cast::typeinfo_cast<T*>(obj)) {
                    out.push_back(casted);
                }
            }

            return out;
        }
    }

    SILLY_API_DLL bool empty();
    SILLY_API_DLL size_t count();

    SILLY_API_DLL cocos2d::CCRect bounds();
    SILLY_API_DLL cocos2d::CCPoint center(bool pIgnoreParent = false);

    /// add object to selection
    /// @param pObj obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void add(GameObject* pObj, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);
    /// add objects to selection
    /// @param pObjs obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void add(std::span<GameObject*> pObjs, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);
    /// add objects to selection
    /// @param pObjs obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void add(cocos2d::CCArray* pObjs, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);
    /// set selection to only object
    /// @param pObj obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void set(GameObject* pObj, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);
    /// set selection to only objects
    /// @param pObjs obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void set(std::span<GameObject*> pObjs, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);
    /// set selection to only objects
    /// @param pObjs obj to select
    /// @param pUndo make the selection undoable
    /// @param pUseFilter whether to check select filter
    /// @param pAlsoCheckLayers whether to also check if objects layers are selectable (editor::object::canSelectLayer)
    /// @param pApplyLinkControls if true and object selected belongs to a link group, the rest of the linked group will be selected (however robtop handles that no promises)
    SILLY_API_DLL void set(cocos2d::CCArray* pObjs, bool pUndo = false, bool pUseFilter = false, bool pAlsoCheckLayers = true, bool pApplyLinkControls = false);

    SILLY_API_DLL void clear(bool pUndo = false);
    SILLY_API_DLL void remove(GameObject* pObj, bool pUndo = false);
    SILLY_API_DLL void remove(std::span<GameObject*> pObjs, bool pUndo = false);
    SILLY_API_DLL void remove(cocos2d::CCArray* pObjs, bool pUndo = false);

    /// updates objects selection color again
    SILLY_API_DLL void repairColors(std::span<GameObject*> pObjs);
    /// updates objects selection color again
    SILLY_API_DLL void repairColors(cocos2d::CCArray* pObjs = get());
}