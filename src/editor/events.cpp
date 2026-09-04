#include <editor/include.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor {
    static auto& touchCreating() {
        static bool val = false;
        return val;
    }

    class $modify(EditorUI) {
        static void onModify(auto& pSelf) {
            (void)pSelf.setHookPriorityPre("EditorUI::deselectAll", Priority::First);
            (void)pSelf.setHookPriorityPre("EditorUI::deselectObject", Priority::First);
            (void)pSelf.setHookPriorityPre("EditorUI::selectObject", Priority::First);
            (void)pSelf.setHookPriorityPre("EditorUI::selectObjects", Priority::First);
        }

        void deselectAll() {
            auto oldSelection = editor::selection::get();

            EditorUI::deselectAll();

            ObjectsDeselectedEvent().send(oldSelection);
        }

        void deselectObject(GameObject* object) {
            EditorUI::deselectObject(object);

            ObjectsDeselectedEvent().send(CCArray::createWithObject(object));
        }

        void selectObject(GameObject* object, bool ignoreFilter) {
            auto oldSelection = editor::selection::get();

            EditorUI::selectObject(object, ignoreFilter);

            if (oldSelection->count()) {
                ObjectsDeselectedEvent().send(oldSelection);
            }
            if (editor::selection::count()) {
                ObjectsSelectedEvent().send(editor::selection::get());
            }

            return;
        }

        void selectObjects(CCArray* objects, bool ignoreFilter) {
            auto oldSelection = editor::selection::get();

            EditorUI::selectObjects(objects, ignoreFilter);

            if (editor::selection::count()) {
                auto array = editor::selection::get();

                utils::array::remove(array, oldSelection);

                if (array->count()) {
                    ObjectsSelectedEvent().send(array);
                }
            }
        }

        void onCreate() {
            touchCreating() = true;

            EditorUI::onCreate();

            touchCreating() = false;
        }
    };

    class $modify(LevelEditorLayer) {
        struct Fields {
            std::optional<size_t> lastObjectCount = std::nullopt;
        };

        static void onModify(auto& pSelf) {
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::updateEditor", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::createObject", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::createObjectsFromString", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::removeObject", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::removeAllObjectsOfType", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::onPlaytest", Priority::First);
            (void)pSelf.setHookPriorityPre("LevelEditorLayer::onStopPlaytest", Priority::First);
        }

        void updateEditor(float dt) {
            LevelEditorLayer::updateEditor(dt);

            auto fields = m_fields.self();

            if (!fields->lastObjectCount.has_value() || fields->lastObjectCount.value() != m_objects->count()) {
                ObjectsChangedEvent().send();

                fields->lastObjectCount = m_objects->count();
            }
        }

        GameObject* createObject(int key, CCPoint position, bool noUndo) {
            auto ret = LevelEditorLayer::createObject(key, position, noUndo);

            if (ret) {
                ObjectsCreatedEvent(touchCreating()).send(CCArray::createWithObject(ret));
            }

            return ret;
        }

        CCArray* createObjectsFromString(const gd::string& str, bool noUndo, bool noLimit) {
            auto ret = LevelEditorLayer::createObjectsFromString(str, noUndo, noLimit);

            if (ret) {
                ObjectsCreatedEvent(touchCreating()).send(nwo5::utils::array::copy(ret));
            }

            return ret;
        }

        void removeObject(GameObject* object, bool noUndo) {
            ObjectsDeletedEvent().send(CCArray::createWithObject(object));

            LevelEditorLayer::removeObject(object, noUndo);
        }

        #ifdef GEODE_IS_DESKTOP
            void removeAllObjectsOfType(int objectID) {
                auto out = CCArray::createWithCapacity(m_objects->count());

                for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
                    if (obj->m_objectID == objectID) {
                        out->addObject(obj);
                    }
                }

                ObjectsDeletedEvent().send(out);

                LevelEditorLayer::removeAllObjectsOfType(objectID);
            }
        #endif

        void onPlaytest() {
            OnPlaytestEvent(true).send();

            LevelEditorLayer::onPlaytest();
        }

        void onStopPlaytest() {
            OnPlaytestEvent(false).send();
            
            LevelEditorLayer::onStopPlaytest();
        }
    };
}