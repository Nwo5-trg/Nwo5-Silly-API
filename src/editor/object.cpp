#include <editor/include.hpp>
#include <utils/include.hpp>
#include <ranges>

using namespace geode::prelude;

namespace nwo5::editor::object {
    namespace impl {
        GameObject* createObject(int id, CCPoint pos, bool undo, bool setup) {
            if (notLoaded(LoadedType::EditorValid)) {
                return nullptr;
            }
            
            if (setup) {
                return editor::layer()->createObject(id, pos, !undo);
            }
            else {
                auto arr = editor::layer()->createObjectsFromString(fmt::format("1,{},2,{},3,{}", id, pos.x, pos.y), !undo, true);

                return arr ? static_cast<GameObject*>(arr->firstObject()) : nullptr;
            }
        }
        GameObject* createObject(int id, CCPoint pos, geode::ZStringView args, bool undo) {
            auto arr = editor::layer()->createObjectsFromString(
                fmt::format(
                    "1,{},2,{},3,{},{}", id, pos.x, pos.y, args.view().starts_with(',') ? args.view().substr(1) : args.view()
                ), !undo, true
            );

            return arr ? static_cast<GameObject*>(arr->firstObject()) : nullptr;
        }
        GameObject* createObject(geode::ZStringView str, bool undo) {
            auto arr = editor::layer()->createObjectsFromString(str, !undo, true);

            return arr ? static_cast<GameObject*>(arr->firstObject()) : nullptr;
        }
        CCArray* createObjects(geode::ZStringView str, bool undo) {
            return editor::layer()->createObjectsFromString(str, !undo, true);
        }
    }

    std::string string(GameObject* obj) {
        return loaded(LoadedType::EditorValid) ? std::string(obj->getSaveString(editor::layer())) : "";
    }
    std::string string(std::span<GameObject* const> objs) {
        if (notLoaded(LoadedType::EditorValid) || objs.empty()) {
            return "";
        }

        return string::join(
            // fuck pipe operator all my homies hate pipe operator
            /// girl stfu stop trying to make the code uglier cuz u wanna b special
            objs 
                | std::views::transform([] (GameObject* obj) {
                    return std::string(obj->getSaveString(editor::layer()));
                })
                | std::ranges::to<std::vector>(),
            ";"
        );
    }
    std::string string(CCArray* objs) {
        if (notLoaded(LoadedType::EditorValid) || !objs->count()) {
            return "";
        }

        auto ext = CCArrayExt<GameObject*>(objs);

        return string::join(
            ext
                | std::views::transform([] (GameObject* obj) {
                    return std::string(obj->getSaveString(editor::layer()));
                })
                | std::ranges::to<std::vector>(),
                ";"
        );
    }

    void remove(GameObject* obj, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }

        editor::selection::remove(obj);

        editor::layer()->removeObject(obj, !undo);
    }
    void remove(std::span<GameObject* const> objs, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo && !objs.empty()) {
            editor::layer()->addToUndoList(UndoObject::createWithArray(CCArrayExt(objs).inner(), UndoCommand::DeleteMulti), false);
        }

        editor::selection::remove(objs);

        for (auto obj : objs) {
            editor::layer()->removeObject(obj, true);
        }
    }
    void remove(CCArray* objs, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo && objs->count()) {
            editor::layer()->addToUndoList(UndoObject::createWithArray(objs, UndoCommand::DeleteMulti), false);
        }

        editor::selection::remove(objs);

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            editor::layer()->removeObject(obj, true);
        }
    }

    std::vector<int> groups(GameObject* obj) {
        std::vector<int> out;

        if (!obj->m_groups) {
            return out;
        }

        for (const auto group : *obj->m_groups) {
            if (group) {
                out.push_back(group);
            }
        }

        return out;
    }
    std::vector<int> groups(std::span<GameObject* const> objs, bool sort) {
        std::unordered_set<int> groups;

        for (auto obj : objs) {
            if (!obj->m_groups) {
                continue;
            }

            for (const auto group : *obj->m_groups) {
                if (group) {
                    groups.insert(group);
                }
            }
        }

        std::vector<int> out = {groups.begin(), groups.end()};

        if (sort) {
            std::ranges::sort(out);
        }

        return out;
    }
    std::vector<int> groups(CCArray* objs, bool sort) {
        std::unordered_set<int> groups;

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (!obj->m_groups) {
                continue;
            }

            for (const auto group : *obj->m_groups) {
                if (group) {
                    groups.insert(group);
                }
            }
        }

        std::vector<int> out = {groups.begin(), groups.end()};

        if (sort) {
            std::ranges::sort(out);
        }

        return out;
    }

    bool hasGroups(GameObject* obj) {
        if (!obj->m_groups) {
            return false;
        }

        for (const auto group : *obj->m_groups) {
            if (group) {
                return true;
            }
        }

        return false;
    }
    bool hasGroup(GameObject* obj, int group) {
        if (!group) {
            return true;
        }
        else {
            return obj->m_groups && std::ranges::contains(*obj->m_groups, group);
        }
    }

    bool sharesGroup(std::span<GameObject* const> objs, int group) {
        if (objs.empty()) {
            return false;
        }

        for (auto obj : objs) {
            if (!hasGroup(obj, group)) {
                return false;
            }
        }

        return true;
    }
    bool sharesGroup(CCArray* objs, int group) {
        if (!objs->count()) {
            return false;
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (!hasGroup(obj, group)) {
                return false;
            }
        }

        return true;
    }
    std::vector<int> sharedGroups(std::span<GameObject* const> objs, bool sort) {
        if (objs.empty()) {
            return {};
        }

        std::vector<int> shared = groups(objs.front());

        std::erase_if(shared, [&] (int group) {
            return !sharesGroup(objs, group);
        });

        if (sort) {
            std::ranges::sort(shared);
        }

        return shared;
    }
    std::vector<int> sharedGroups(CCArray* objs, bool sort) {
        if (!objs || !objs->count()) {
            return {};
        }

        std::vector<int> shared = groups(static_cast<GameObject*>(objs->firstObject()));

        std::erase_if(shared, [&] (int group) {
            return !sharesGroup(objs, group);
        });

        if (sort) {
            std::ranges::sort(shared);
        }

        return shared;
    }

    void addGroup(GameObject* obj, int group) {
        if (loaded(LoadedType::Editor)) {
            const auto res = obj->addToGroup(group);

            if (res == 1) {
                editor::layer()->addToGroup(obj, group, false);
            }
        }
    }
    void addGroup(std::span<GameObject* const> objs, int group) {
        if (loaded(LoadedType::Editor)) {
            for (auto obj : objs) {
                const auto res = obj->addToGroup(group);

                if (res == 1) {
                    editor::layer()->addToGroup(obj, group, false);
                }
            }
        }
    }
    void addGroup(CCArray* objs, int group) {
        if (loaded(LoadedType::Editor)) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                const auto res = obj->addToGroup(group);

                if (res == 1) {
                    editor::layer()->addToGroup(obj, group, false);
                }
            }
        }
    }
    void removeGroup(GameObject* obj, int group) {
        if (loaded(LoadedType::Editor)) {
            obj->removeFromGroup(group);
            editor::layer()->removeFromGroup(obj, group);
        }
    }
    void removeGroup(std::span<GameObject* const> objs, int group) {
        if (loaded(LoadedType::Editor)) {
            for (auto obj : objs) {
                obj->removeFromGroup(group);
                editor::layer()->removeFromGroup(obj, group);
            }
        }
    }
    void removeGroup(CCArray* objs, int group) {
        if (loaded(LoadedType::Editor)) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                obj->removeFromGroup(group);
                editor::layer()->removeFromGroup(obj, group);
            }
        }
    }

    bool hasParent(int group) {
        return groupParent(group);
    }
    bool hasParent(std::span<GameObject* const> objs, int group) {
        auto parent = groupParent(group);

        if (!parent) {
            return false;
        }

        return std::ranges::contains(objs, parent);
    }
    bool hasParent(CCArray* objs, int group) {
        auto parent = groupParent(group);

        if (!parent) {
            return false;
        }

        return objs->containsObject(parent);
    }

    std::optional<int> baseColor(GameObject* obj) {
        auto col = obj->m_baseColor;

        if (!col) {
            return std::nullopt;
        }

        return col->m_colorID ? col->m_colorID : col->m_defaultColorID;
    }
    void setBaseColor(GameObject* obj, int color) {
        auto col = obj->m_baseColor;

        if (!col) {
            return;
        }

        if (color == 0) {
            int defaultId = std::clamp(col->m_defaultColorID, 0, 1101);
            col->m_defaultColorID = defaultId;
            col->m_colorID = 0;
        }
        else {
            col->m_colorID = std::clamp(color, 0, 1101);
        }

        obj->m_updateParents = true;
    }
    std::optional<int> detailColor(GameObject* obj) {
        auto col = obj->m_detailColor;

        if (!col) {
            return std::nullopt;
        }

        return col->m_colorID ? col->m_colorID : col->m_defaultColorID;
    }
    void setDetailColor(GameObject* obj, int color) {
       auto col = obj->m_detailColor;

        if (!col) {
            return;
        }

        if (color == 0) {
            int defaultId = std::clamp(col->m_defaultColorID, 0, 1101);
            col->m_defaultColorID = defaultId;
            col->m_colorID = 0;
        }
        else {
            col->m_colorID = std::clamp(color, 0, 1101);
        }

        obj->m_updateParents = true;
    }
    bool hasColor(GameObject* obj, int color, bool primary) {
        auto col = primary ? obj->m_baseColor : obj->m_detailColor;

        return col && color == (col->m_colorID ? col->m_colorID : col->m_defaultColorID);
    }

    int id(GameObject* obj) {
        return obj->m_objectID;
    }
    std::vector<int> ids(std::span<GameObject* const> objs, bool sort) {
        if (objs.empty()) {
            return {};
        }

        std::unordered_set<int> ids;

        for (auto obj : objs) {
            ids.insert(obj->m_objectID);
        }

       std::vector<int> out = {ids.begin(), ids.end()};

        if (sort) {
            std::ranges::sort(out);
        }

        return out;
    }
    std::vector<int> ids(CCArray* objs, bool sort) {
        if (!objs->count()) {
            return {};
        }

        std::unordered_set<int> ids;

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            ids.insert(obj->m_objectID);
        }

        std::vector<int> out = {ids.begin(), ids.end()};

        if (sort) {
            std::ranges::sort(out);
        }

        return out;
    }

    int layer(GameObject* obj) {
        return obj->m_editorLayer;
    }
    void setLayer(GameObject* obj, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            obj->m_editorLayer = layer;
        }
    }
    void setLayer(std::span<GameObject* const> objs, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            for (auto obj : objs) {
                obj->m_editorLayer = layer;
            }
        }
    }
    void setLayer(CCArray* objs, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                obj->m_editorLayer = layer;
            }
        }
    }
    int layer2(GameObject* obj) {
        return obj->m_editorLayer2;
    }
    void setLayer2(GameObject* obj, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            obj->m_editorLayer2 = layer;
        }
    }
    void setLayer2(std::span<GameObject* const> objs, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            for (auto obj : objs) {
                obj->m_editorLayer2 = layer;
            }
        }
    }
    void setLayer2(CCArray* objs, int layer) {
        if (layer >= 0 && layer <= editor::constants::MAX_LAYERS) {
            for (auto obj : CCArrayExt<GameObject*>(objs)) {
                obj->m_editorLayer2 = layer;
            }
        }
    }

    bool canSelectLayer(GameObject* obj, bool ignoreLocked) {
        return editor::layerSelectable(obj->m_editorLayer, ignoreLocked) || (obj->m_editorLayer2 && editor::layerSelectable(obj->m_editorLayer2, ignoreLocked));
    }

    int zOrder(GameObject* obj) {
        return obj->m_zOrder;
    }
    void setZOrder(GameObject* obj, int order) {
        obj->m_zOrder = order;
        obj->m_updateParents = true;
    }
    void setZOrder(std::span<GameObject* const> objs, int order) {
        for (auto obj : objs) {
            obj->m_zOrder = order;
            obj->m_updateParents = true;
        }
    }
    void setZOrder(CCArray* objs, int order) {
        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            obj->m_zOrder = order;
            obj->m_updateParents = true;
        }
    }

    CCRect bounds(GameObject* obj, bool contentSize) {
        if (contentSize) {
            const auto size = obj->getScaledContentSize();
            return {obj->getRealPosition() - size / 2, size};
        }
        else {
            const auto grid = size(obj);
            return {obj->getRealPosition() - grid, CCSize{grid, grid}};
        }
    }
    CCRect bounds(std::span<GameObject* const> objs, bool addSize) {
        if (objs.empty()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : objs) {
            const auto pos = obj->getRealPosition();
            const auto size = addSize ? obj->getScaledContentSize() / 2 : CCSizeZero;

            min.x = std::min(min.x, pos.x - size.width);
            min.y = std::min(min.y, pos.y - size.height);
            max.x = std::max(max.x, pos.x + size.width);
            max.y = std::max(max.y, pos.y + size.height);
        }

        return {min, max - min};
    }
    CCRect bounds(CCArray* objs, bool addSize) {
        if (!objs->count()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            const auto pos = obj->getRealPosition();
            const auto size = addSize ? obj->getScaledContentSize() / 2 : CCSizeZero;

            min.x = std::min(min.x, pos.x - size.width);
            min.y = std::min(min.y, pos.y - size.height);
            max.x = std::max(max.x, pos.x + size.width);
            max.y = std::max(max.y, pos.y + size.height);
        }

        return {min, max - min};
    }
    CCPoint center(std::span<GameObject* const> objs, bool ignoreParent) {
        if (objs.empty()) {
            return CCPointZero;
        }

        if (!ignoreParent) {
            if (notLoaded(LoadedType::Editor)) {
                return CCPointZero;
            }
            
            return editor::ui()->getGroupCenter(CCArrayExt(objs).inner(), false);
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : objs) {
            const auto pos = obj->getRealPosition();

            min.x = std::min(min.x, pos.x);
            min.y = std::min(min.y, pos.y);
            max.x = std::max(max.x, pos.x);
            max.y = std::max(max.y, pos.y);
        }

        return (min + max) / 2;
    }
    CCPoint center(CCArray* objs, bool ignoreParent) {
        if (!objs->count()) {
            return CCPointZero;
        }

        if (!ignoreParent) {
            if (notLoaded(LoadedType::Editor)) {
                return CCPointZero;
            }

            return editor::ui()->getGroupCenter(objs, false);
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            const auto pos = obj->getRealPosition();

            min.x = std::min(min.x, pos.x);
            min.y = std::min(min.y, pos.y);
            max.x = std::max(max.x, pos.x);
            max.y = std::max(max.y, pos.y);
        }

        return (min + max) / 2;
    }

    void cluster(std::vector<std::vector<GameObject*>>& out, std::span<GameObject* const> objs, float clusterSize) {
        static std::vector<GameObject*> queue;
        static std::unordered_map<GameObject*, int> map;
        
        queue.clear();
        map.clear();

        for (auto obj : objs) {
            if (map.contains(obj)) {
                continue;
            }

            const int currentClusterIndex = out.size();
            out.emplace_back();
            auto& currentCluster = out.back();

            queue.clear();
            queue.push_back(obj);
            map[obj] = currentClusterIndex;

            while (!queue.empty()) {
                auto currentObj = queue.back();
                const auto pos = currentObj->getRealPosition();
                queue.pop_back();
                currentCluster.push_back(currentObj);

                for (auto neighbour : objs) {
                    if (map.find(neighbour) != map.end()) {
                        continue;
                    }

                    const auto neighbourPos = neighbour->getRealPosition();

                    if (std::abs(pos.x - neighbourPos.x) <= clusterSize && std::abs(pos.y - neighbourPos.y) <= clusterSize) {
                        map[neighbour] = currentClusterIndex;
                        queue.push_back(neighbour);
                    }
                }
            }
        }
    }
    void cluster(std::vector<std::vector<GameObject*>>& out, CCArray* objs, float clusterSize) {
        static std::vector<GameObject*> queue;
        static std::unordered_map<GameObject*, int> map;
        
        queue.clear();
        map.clear();

        auto ext = objs->asExt<GameObject*>();

        for (auto obj : ext) {
            if (map.contains(obj)) {
                continue;
            }

            const int currentClusterIndex = out.size();
            out.emplace_back();
            auto& currentCluster = out.back();

            queue.clear();
            queue.push_back(obj);
            map[obj] = currentClusterIndex;

            while (!queue.empty()) {
                auto currentObj = queue.back();
                const auto pos = currentObj->getRealPosition();
                queue.pop_back();
                currentCluster.push_back(currentObj);

                for (auto neighbour : ext) {
                    if (map.find(neighbour) != map.end()) {
                        continue;
                    }

                    const auto neighbourPos = neighbour->getRealPosition();

                    if (std::abs(pos.x - neighbourPos.x) <= clusterSize && std::abs(pos.y - neighbourPos.y) <= clusterSize) {
                        map[neighbour] = currentClusterIndex;
                        queue.push_back(neighbour);
                    }
                }
            }
        }
    }
    std::vector<std::vector<GameObject*>> cluster(std::span<GameObject* const> objs, float clusterSize) {
        std::vector<std::vector<GameObject*>> out;

        cluster(out, objs, clusterSize);
        
        return out;
    }
    std::vector<std::vector<GameObject*>> cluster(CCArray* objs, float clusterSize) {
        std::vector<std::vector<GameObject*>> out;

        cluster(out, objs, clusterSize);
        
        return out;
    }

    float size(GameObject* obj) {
        return size(id(obj)); 
    }
    float size(int id) {
        return ObjectToolbox::sharedState()->gridNodeSizeForKey(id); 
    }

    void move(GameObject* obj, CCPoint to, bool undo) {
        moveBy(obj, to - obj->getRealPosition());
    }
    void move(std::span<GameObject* const> objs, CCPoint to, bool undo, std::optional<CCPoint> center) {
        moveBy(objs, to - center.value_or(object::center(objs)));
    }
    void move(CCArray* objs, CCPoint to, bool undo, std::optional<CCPoint> center) {
        moveBy(objs, to - center.value_or(object::center(objs)));
    }
    void moveBy(GameObject* obj, CCPoint off, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        ui()->moveObject(obj, off);
    }
    void moveBy(std::span<GameObject* const> objs, CCPoint off, bool undo) {
        if (notLoaded(LoadedType::Editor) || objs.empty()) {
            return;
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : objs) {
            ui()->moveObject(obj, off);
        }
    }
    void moveBy(CCArray* objs, CCPoint off, bool undo) {
        if (notLoaded(LoadedType::Editor) || !objs->count()) {
            return;
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            ui()->moveObject(obj, off);
        }
    }

    void rotate(GameObject* obj, float to, GameObject* base, bool undo, std::optional<CCPoint> center, bool move) {
        rotateBy(obj, to - base->getObjectRotation(), undo, center, move);
    }
    void rotate(std::span<GameObject* const> objs, float to, GameObject* base, bool undo, std::optional<CCPoint> center, bool move) {
        rotateBy(objs, to - base->getObjectRotation(), undo, center, move);
    }
    void rotate(CCArray* objs, float to, GameObject* base, bool undo, std::optional<CCPoint> center, bool move) {
        rotateBy(objs, to - base->getObjectRotation(), undo, center, move);
    }
    void rotateBy(GameObject* obj, float to, bool undo, std::optional<CCPoint> center, bool move) {
        rotateBy(CCArray::createWithObject(obj), to, undo, center, move);
    }
    void rotateBy(std::span<GameObject* const> objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        rotateBy(CCArrayExt(objs).inner(), to, undo, center, move);
    }
    void rotateBy(CCArray* objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || !objs->count()) {
            return;
        }

        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        // i dont wanna rewrite rotate logic so for now the better edit way™ will have to do
        ui()->rotateObjects(objs, to, center.value(), !move);
    }

    void scale(GameObject* obj, float x, float y, bool undo) {
        scaleBy(obj, x / (obj->m_scaleX ? obj->m_scaleX : 1.0f), y / (obj->m_scaleY ? obj->m_scaleY : 1.0f), undo);
    }
    void scale(GameObject* obj, float to, bool undo) {
        const float maxScale = std::max(obj->m_scaleX, obj->m_scaleY);

        if (!maxScale) {
            return;
        }

        const auto mod = to / maxScale;

        scaleBy(obj, mod, mod, undo);
    }
    void scaleX(GameObject* obj, float to, bool undo) {
        const float maxScale = obj->m_scaleX;

        if (!maxScale) {
            return;
        }

        scaleXBy(obj, to / maxScale, undo);
    }
    void scaleY(GameObject* obj, float to, bool undo) {
        const float maxScale = obj->m_scaleY;

        if (!maxScale) {
            return;
        }

        scaleYBy(obj, to / maxScale, undo);
    }
    void scale(std::span<GameObject* const> objs, float x, float y, bool undo, std::optional<CCPoint> center, bool move) {
        CCPoint maxScale = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : objs) {
            maxScale.x = std::max(maxScale.x, obj->m_scaleX);
            maxScale.y = std::max(maxScale.y, obj->m_scaleY);
        }

        scaleBy(objs, x / (maxScale.x ? maxScale.x : 1.0f), y / (maxScale.y ? maxScale.y : 1.0f), undo, center, move);
    }
    void scale(std::span<GameObject* const> objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : objs) {
            maxScale = std::max(maxScale, std::max(obj->m_scaleX, obj->m_scaleY));
        }

        if (!maxScale) {
            return;
        }

        const auto mod = to / maxScale;

        scaleBy(objs, mod, mod, undo, center, move);
    }
    void scaleX(std::span<GameObject* const> objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : objs) {
            maxScale = std::max(maxScale, obj->m_scaleX);
        }

        if (!maxScale) {
            return;
        }

        scaleXBy(objs, to / maxScale, undo, center, move);
    }
    void scaleY(std::span<GameObject* const> objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : objs) {
            maxScale = std::max(maxScale, obj->m_scaleY);
        }

        if (!maxScale) {
            return;
        }

        scaleYBy(objs, to / maxScale, undo, center, move);
    }
    void scale(CCArray* objs, float x, float y, bool undo, std::optional<CCPoint> center, bool move) {
        CCPoint maxScale = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            maxScale.x = std::max(maxScale.x, obj->m_scaleX);
            maxScale.y = std::max(maxScale.y, obj->m_scaleY);
        }

        scaleBy(objs, x / (maxScale.x ? maxScale.x : 1.0f), y / (maxScale.y ? maxScale.y : 1.0f), undo, center, move);
    }
    void scale(CCArray* objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            maxScale = std::max(maxScale, std::max(obj->m_scaleX, obj->m_scaleY));
        }

        if (!maxScale) {
            return;
        }

        const auto mod = to / maxScale;

        scaleBy(objs, mod, mod, undo, center, move);
    }
    void scaleX(CCArray* objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            maxScale = std::max(maxScale, obj->m_scaleX);
        }

        if (!maxScale) {
            return;
        }

        scaleXBy(objs, to / maxScale, undo, center, move);
    }
    void scaleY(CCArray* objs, float to, bool undo, std::optional<CCPoint> center, bool move) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            maxScale = std::max(maxScale, obj->m_scaleY);
        }

        if (!maxScale) {
            return;
        }

        scaleYBy(objs, to / maxScale, undo, center, move);
    }
    void scaleBy(GameObject* obj, float x, float y, bool undo) {
        if (notLoaded(LoadedType::Editor)) {
            return;
        }
        
        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        if (x != 1.0f) {
            obj->updateCustomScaleX(obj->m_scaleX * x);
        }
        if (y != 1.0f) {
            obj->updateCustomScaleY(obj->m_scaleY * y);
        }
    }
    void scaleBy(GameObject* obj, float mod, bool undo) {
        scaleBy(obj, mod, mod, undo);
    }
    void scaleXBy(GameObject* obj, float mod, bool undo) {
        if (notLoaded(LoadedType::Editor) || !mod || mod == 1.0f) {
            return;
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        obj->updateCustomScaleX(obj->m_scaleX * mod);
    }
    void scaleYBy(GameObject* obj, float mod, bool undo) {
        if (notLoaded(LoadedType::Editor) || !mod || mod == 1.0f) {
            return;
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        obj->updateCustomScaleY(obj->m_scaleY * mod);
    }
    void scaleBy(std::span<GameObject* const> objs, float x, float y, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || objs.empty()) {
            return;
        }

        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : objs) {
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{x, y});
            }

            if (x != 1.0f) {
                obj->updateCustomScaleX(obj->m_scaleX * x);
            }
            if (y != 1.0f) {
                obj->updateCustomScaleY(obj->m_scaleY * y);
            }
        }
    }
    void scaleBy(std::span<GameObject* const> objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        scaleBy(objs, mod, mod, undo, center, move);
    }
    void scaleXBy(std::span<GameObject* const> objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || objs.empty() || !mod || mod == 1.0f) {
            return;
        }

        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : objs) {
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{mod, 1.0f});
            }

            obj->updateCustomScaleX(obj->m_scaleX * mod);
        }
    }
    void scaleYBy(std::span<GameObject* const> objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || objs.empty() || !mod || mod == 1.0f) {
            return;
        }

        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : objs) {
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{1.0f, mod});
            }

            obj->updateCustomScaleY(obj->m_scaleY * mod);
        }
    }
    void scaleBy(CCArray* objs, float x, float y, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || !objs->count()) {
            return;
        }
        
        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{x, y});
            }

            if (x && x != 1.0f) {
                obj->updateCustomScaleX(obj->m_scaleX * x);
            }
            if (y && y != 1.0f) {
                obj->updateCustomScaleY(obj->m_scaleY * y);
            }
        }
    }
    void scaleBy(CCArray* objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        scaleBy(objs, mod, mod, undo, center, move);
    }
    void scaleXBy(CCArray* objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || !objs->count() || !mod || mod == 1.0f) {
            return;
        }
        
        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {        
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{mod, 1.0f});
            }

            obj->updateCustomScaleX(obj->m_scaleX * mod);
        }
    }
    void scaleYBy(CCArray* objs, float mod, bool undo, std::optional<CCPoint> center, bool move) {
        if (notLoaded(LoadedType::Editor) || !objs->count() || !mod || mod == 1.0f) {
            return;
        }
        
        if (center == std::nullopt) {
            center = object::center(objs);
        }

        if (undo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(objs)) {        
            if (move) {
                object::move(obj, center.value() + (obj->getRealPosition() - center.value()) * CCSize{1.0f, mod});
            }

            obj->updateCustomScaleY(obj->m_scaleY * mod);
        }
    }
}