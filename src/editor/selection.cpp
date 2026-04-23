#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::selection {
    void add(GameObject* pObj, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        if (notLoaded() || (pUseFilter && pAlsoCheckLayers && !editor::object::canSelectLayer(pObj))) {
            return;
        }

        // technically checking twice but idec 
        if (pUndo && (!pUseFilter || ui()->canSelectObject(pObj))) {
            ui()->createUndoSelectObject(false);
        }
        
        if (pApplyLinkControls) {
            ui()->selectObject(pObj, !pUseFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObject(pObj, !pUseFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }
    void add(std::span<GameObject*> pObjs, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        add(CCArrayExt(pObjs).inner(), pUndo, pUseFilter, pAlsoCheckLayers);
    }
    void add(cocos2d::CCArray* pObjs, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        if (notLoaded()) {
            return;
        }
        
        const auto checkLayers = pUseFilter && pAlsoCheckLayers;

        auto objs = checkLayers ? CCArray::create() : pObjs;

        if (checkLayers) {
            for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
                if (editor::object::canSelectLayer(obj)) {
                    objs->addObject(obj);
                }
            }
        }

        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }
        
        if (pApplyLinkControls) {
            ui()->selectObjects(objs, !pUseFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObjects(objs, !pUseFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }
    void set(GameObject* pObj, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        if (notLoaded() || (pUseFilter && pAlsoCheckLayers && !editor::object::canSelectLayer(pObj))) {
            return;
        }

        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }
        
        clear();
        
        if (pApplyLinkControls) {
            ui()->selectObject(pObj, !pUseFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObject(pObj, !pUseFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }
    void set(std::span<GameObject*> pObjs, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        set(CCArrayExt(pObjs).inner(), pUndo, pUseFilter, pAlsoCheckLayers);
    }
    void set(cocos2d::CCArray* pObjs, bool pUndo, bool pUseFilter, bool pAlsoCheckLayers, bool pApplyLinkControls) {
        if (notLoaded()) {
            return;
        }
        
        const auto checkLayers = pUseFilter && pAlsoCheckLayers;

        auto objs = checkLayers ? CCArray::create() : pObjs;

        if (checkLayers) {
            for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
                if (editor::object::canSelectLayer(obj)) {
                    objs->addObject(obj);
                }
            }
        }
        
        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }

        clear();
        
        if (pApplyLinkControls) {
            ui()->selectObjects(objs, !pUseFilter);
        }
        else {
            const auto ret = ui()->m_stickyControlsEnabled;
            ui()->m_stickyControlsEnabled = false;

            ui()->selectObjects(objs, !pUseFilter);

            ui()->m_stickyControlsEnabled = ret;
        }
    }

    bool empty() {
        return !count();
    }
    size_t count() {
        if (notLoaded()) {
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
    cocos2d::CCPoint center(bool pIgnoreParent) {
        return editor::object::center(get(), pIgnoreParent);
    }

    void clear(bool pUndo) {
        remove(get(), pUndo);
    }
    void remove(GameObject* pObj, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }

        pObj->deselectObject();

        if (ui()->m_selectedObject == pObj) {
            ui()->m_selectedObject = nullptr;
        }
        
        ui()->m_selectedObjects->removeObject(pObj, false);
    }
    void remove(std::span<GameObject*> pObjs, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }

        for (auto obj : pObjs) {
            remove(obj);
        }
    }
    void remove(cocos2d::CCArray* pObjs, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo) {
            ui()->createUndoSelectObject(false);
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            remove(obj);
        }
    }

    void repairColors(std::span<GameObject*> pObjs) {
        for (auto obj : pObjs) {
            if (!obj->m_isSelected) {
                continue;
            }

            obj->updateObjectEditorColor();
        }
    }
    void repairColors(cocos2d::CCArray* pObjs) {
        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            if (!obj->m_isSelected) {
                continue;
            }

            obj->updateObjectEditorColor();
        }
    }
}