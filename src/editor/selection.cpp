#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::selection {
    void add(GameObject* obj, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        if (notLoaded(LoadedType::Editor) || (useFilter && alsoCheckLayers && !editor::object::canSelectLayer(obj))) {
            return;
        }

        // technically checking twice but idec 
        if (undo && (!useFilter || ui()->canSelectObject(obj))) {
            ui()->createUndoSelectObject(false);
        }
        
        const auto ret = ui()->m_stickyControlsEnabled;
        ui()->m_stickyControlsEnabled &= applyLinkControls;

        ui()->selectObjects(CCArray::createWithObject(obj), !useFilter);

        ui()->m_stickyControlsEnabled = ret;
    }
    void add(std::span<GameObject* const> objs, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        add(CCArrayExt(objs).inner(), undo, useFilter, alsoCheckLayers);
    }
    void add(cocos2d::CCArray* objs, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        const auto checkLayers = useFilter && alsoCheckLayers;

        auto filtered = checkLayers ? CCArray::create() : objs;

        if (checkLayers) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                if (editor::object::canSelectLayer(obj)) {
                    filtered->addObject(obj);
                }
            }
        }

        if (undo) {
            ui()->createUndoSelectObject(false);
        }
        
        if (applyLinkControls) {
            ui()->selectObjects(filtered, !useFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObjects(filtered, !useFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }
    void set(GameObject* obj, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        if (notLoaded(LoadedType::Editor) || (useFilter && alsoCheckLayers && !editor::object::canSelectLayer(obj))) {
            return;
        }

        // technically checking twice but idec 
        if (undo && (!useFilter || ui()->canSelectObject(obj))) {
            ui()->createUndoSelectObject(false);
        }

        clear();
        
        const auto ret = ui()->m_stickyControlsEnabled;
        ui()->m_stickyControlsEnabled &= applyLinkControls;

        ui()->selectObjects(CCArray::createWithObject(obj), !useFilter);

        ui()->m_stickyControlsEnabled = ret;
    }
    void set(std::span<GameObject* const> objs, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        set(CCArrayExt(objs).inner(), undo, useFilter, alsoCheckLayers);
    }
    void set(cocos2d::CCArray* objs, bool undo, bool useFilter, bool alsoCheckLayers, bool applyLinkControls) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        const auto checkLayers = useFilter && alsoCheckLayers;

        auto filtered = checkLayers ? CCArray::create() : objs;

        if (checkLayers) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                if (editor::object::canSelectLayer(obj)) {
                    filtered->addObject(obj);
                }
            }
        }
        
        if (undo) {
            ui()->createUndoSelectObject(false);
        }

        clear();
        
        if (applyLinkControls) {
            ui()->selectObjects(filtered, !useFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObjects(filtered, !useFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }

    bool empty() {
        return !count();
    }
    size_t count() {
        if (notLoaded(LoadedType::Editor)) {
            return 0;
        }     
        else if (ui()->m_selectedObject) {
            return 1;
        }
        else {
            return ui()->m_selectedObjects->count();
        }
    }

    cocos2d::CCRect bounds() {
        return editor::object::bounds(get());
    }
    cocos2d::CCPoint center(bool ignoreParent) {
        return editor::object::center(get(), ignoreParent);
    }

    void clear(bool undo) {
        remove(get(), undo);
    }
    void remove(GameObject* obj, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo) {
            ui()->createUndoSelectObject(false);
        }

        obj->deselectObject();

        if (ui()->m_selectedObject == obj) {
            ui()->m_selectedObject = nullptr;
        }
        
        ui()->m_selectedObjects->removeObject(obj, false);
    }
    void remove(std::span<GameObject* const> objs, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo) {
            ui()->createUndoSelectObject(false);
        }

        for (auto obj : objs) {
            remove(obj);
        }
    }
    void remove(cocos2d::CCArray* objs, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo) {
            ui()->createUndoSelectObject(false);
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            remove(obj);
        }
    }

    void repairColors(std::span<GameObject* const> objs) {
        for (auto obj : objs) {
            if (!obj->m_isSelected) {
                continue;
            }

            obj->updateObjectEditorColor();
        }
    }
    void repairColors(cocos2d::CCArray* objs) {
        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (!obj->m_isSelected) {
                continue;
            }

            obj->updateObjectEditorColor();
        }
    }
}