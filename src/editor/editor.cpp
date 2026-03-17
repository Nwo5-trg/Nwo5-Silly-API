#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor {
    EditorUI* ui() {
        static const auto manager = GameManager::get();
        return manager->m_levelEditorLayer->m_editorUI;
    };
    LevelEditorLayer* layer() {
        static const auto manager = GameManager::get();
        return manager->m_levelEditorLayer;
    }

    bool loaded() {
        return layer();
    }

    void update(bool pUpdateControls, bool pOtherwiseDeactivateControls) {
        auto editor = ui();

        editor->updateButtons();
        editor->updateObjectInfoLabel();
        editor->updateGridNodeSize();
        editor->tryUpdateTimeMarkers();
        editor->updateStickyControls();
        
        if (pUpdateControls) {
            if (auto control = editor->m_rotationControl; control && control->isVisible()) {
                activateRotationControl();
            }
            if (auto control = editor->m_scaleControl; control && control->isVisible()) {
                activateScaleControl(!control->m_scaleLabel->isVisible());
            }
            if (auto control = editor->m_transformControl; control && control->isVisible()) {
                activateTransformControl();
            }
        }
        else if (pOtherwiseDeactivateControls) {
            editor->deactivateRotationControl();
            editor->deactivateScaleControl();
            editor->deactivateTransformControl();
        }
    }

    float zoom() {
        return layer()->m_objectLayer->getScale();
    }
    cocos2d::CCPoint center() {
        return CCPoint{
            (CCDirector::get()->getWinSize() / 2) - CCPoint{
                layer()->m_objectLayer->getPositionX(), 
                layer()->m_objectLayer->getPositionY() - ui()->m_toolbarHeight / 2
            }
         } / zoom();
    }

    void activateRotationControl(bool pRefresh) {
        if (!ui()->m_rotationControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateRotationControl();
        }
        else if (ui()->m_rotationControl->isVisible()) {
            return;
        }

        ui()->activateRotationControl(nullptr);
    }
    void activateScaleControl(bool pXY, bool pRefresh) {
        if (!ui()->m_scaleControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateScaleControl();
        }
        else if (ui()->m_scaleControl->isVisible()) {
            return;
        }

        auto obj = CCNode::create();
        obj->setTag(pXY ? 30 : 29);

        ui()->activateScaleControl(obj);
    }
    void activateTransformControl(bool pRefresh) {
        if (!ui()->m_transformControl) {
            return;
        }

        if (pRefresh) {
            ui()->deactivateTransformControl();
        }
        else if (ui()->m_transformControl->isVisible()) {
            return;
        }

        ui()->activateTransformControl(nullptr);
    }

    int currentLayer() {
        return layer()->m_currentLayer;
    }
    bool layerSelectable(int pLayer, bool pIgnoreLocked) {
        if (pLayer > editor::constants::MAX_LAYERS || (!pIgnoreLocked && layerLocked(pLayer))) {
            return false;
        }

        const auto layer = currentLayer();

        return layer == editor::constants::ALL_LAYERS || layer == pLayer;
    }
    bool layerLocked(int pLayer) {
        return layer()->isLayerLocked(pLayer);
    }
    void setLayer(int pLayer) {
        if (pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS) {
            return;
        }

        layer()->m_currentLayer = pLayer;
        // its fucking crazy to me that robtop calls layers "groups" internally :sob:
        ui()->updateGroupIDLabel();
    }
    void lockLayer(int pLayer) {
        if (pLayer > editor::constants::MAX_LAYERS || pLayer < editor::constants::ALL_LAYERS) {
            return;
        }

        const auto ret = currentLayer();

        layer()->m_currentLayer = pLayer;
        ui()->onLockLayer(nullptr);

        layer()->m_currentLayer = ret;
    }
    
    namespace impl {
        int nextFreeGroupFast(int pOffset) {
            pOffset = std::clamp(pOffset, 1, 9999);

            auto keys = layer()->m_groupDict->allKeys();

            if (!keys->count()) {
                return pOffset;
            }

            std::set<int> usedGroups;

            for (auto key : CCArrayExt<CCInteger*>(keys)) {
                usedGroups.insert(key->getValue());
            }

            for (auto it = usedGroups.lower_bound(pOffset); it != usedGroups.end(); it++) {
                if (*it == pOffset) {
                    pOffset++;
                } 
                else {
                    return pOffset;
                }
            }
            
            return pOffset > constants::MAX_GROUPS ? 0 : pOffset;
        }
    }
    int nextFreeGroup(int pOffset, bool pCheckTargetGroups) {
        if (!pCheckTargetGroups) {
            return impl::nextFreeGroupFast(pOffset);
        }

        pOffset = std::clamp(pOffset, 1, 9999);

        auto objs = editor::object::getAll();

        if (!objs->count()) {
            return pOffset;
        }

        std::set<int> usedGroups;

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (obj->m_groups) {
                for (const auto group : *obj->m_groups) {
                    if (group) {
                        usedGroups.insert(group);
                    }
                }
            }

            if (obj->m_isTrigger) {
                if (const auto group = static_cast<EffectGameObject*>(obj)->m_targetGroupID) {
                    usedGroups.insert(group);
                }
                if (const auto group = static_cast<EffectGameObject*>(obj)->m_centerGroupID) {
                    usedGroups.insert(group);
                }
            }
        }

        for (auto it = usedGroups.lower_bound(pOffset); it != usedGroups.end(); it++) {
            if (*it == pOffset) {
                pOffset++;
            } 
            else {
                return pOffset;
            }
        }
        
        return pOffset > constants::MAX_GROUPS ? 0 : pOffset;
    }

    namespace impl {
        void createUndoObject(UndoCommand pCommand) {
            ui()->createUndoObject(pCommand, false);
        }
    }
}