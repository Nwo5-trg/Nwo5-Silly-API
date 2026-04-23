#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::object {
    size_t count() {
        return getAll()->count();
    }

    CCArray* getAll(bool pCopy) {
        return loaded() ? (pCopy ? CCArray::createWithArray(layer()->m_objects) : layer()->m_objects) : CCArray::create();
    }
    CCArray* getWithGroup(int pGroup, bool pCopy) {
        if (notLoaded()) {
            return CCArray::create();
        }
        
        if (auto ptr = layer()->m_groupDict->objectForKey(pGroup)) {
            return pCopy ? CCArray::createWithArray(static_cast<CCArray*>(ptr)) : static_cast<CCArray*>(ptr);
        }
        else {
            return CCArray::create();
        }
    }
    GameObject* getParent(int pGroup) {
        return loaded() ? layer()->getGroupParent(pGroup) : nullptr;
    }

    std::vector<int> groups(GameObject* pObj) {
        std::vector<int> out;

        if (!pObj->m_groups) {
            return out;
        }

        for (const auto group : *pObj->m_groups) {
            if (group) {
                out.push_back(group);
            }
        }

        return out;
    }
    std::vector<int> groups(std::span<GameObject*> pObjs, bool pSort) {
        std::unordered_set<int> groups;

        for (auto obj : pObjs) {
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

        if (pSort) {
            std::ranges::sort(out);
        }

        return out;
    }
    std::vector<int> groups(CCArray* pObjs, bool pSort) {
        std::unordered_set<int> groups;

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
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

        if (pSort) {
            std::ranges::sort(out);
        }

        return out;
    }
    bool hasGroups(GameObject* pObj) {
        if (!pObj->m_groups) {
            return false;
        }

        for (const auto group : *pObj->m_groups) {
            if (group) {
                return true;
            }
        }

        return false;
    }
    bool hasGroup(GameObject* pObj, int pGroup) {
        if (!pGroup) {
            return true;
        }
        else {
            return pObj->m_groups && std::ranges::contains(*pObj->m_groups, pGroup);
        }
    }
    bool sharesGroup(std::span<GameObject*> pObjs, int pGroup) {
        if (pObjs.empty()) {
            return false;
        }

        for (auto obj : pObjs) {
            if (!hasGroup(obj, pGroup)) {
                return false;
            }
        }

        return true;
    }
    bool sharesGroup(CCArray* pObjs, int pGroup) {
        if (!pObjs->count()) {
            return false;
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            if (!hasGroup(obj, pGroup)) {
                return false;
            }
        }

        return true;
    }
    bool hasParent(int pGroup) {
        return getParent(pGroup);
    }
    bool hasParent(std::span<GameObject*> pObjs, int pGroup) {
        auto parent = getParent(pGroup);

        if (!parent) {
            return false;
        }

        return std::ranges::contains(pObjs, parent);
    }
    bool hasParent(CCArray* pObjs, int pGroup) {
        auto parent = getParent(pGroup);

        if (!parent) {
            return false;
        }

        return pObjs->containsObject(parent);
    }

    std::optional<int> baseColor(GameObject* pObj) {
        auto col = pObj->m_baseColor;

        if (!col) {
            return std::nullopt;
        }

        return col->m_colorID ? col->m_colorID : col->m_defaultColorID;
    }
    std::optional<int> detailColor(GameObject* pObj) {
        auto col = pObj->m_detailColor;

        if (!col) {
            return std::nullopt;
        }

        return col->m_colorID ? col->m_colorID : col->m_defaultColorID;
    }
    bool hasColor(GameObject* pObj, int pColor, bool pPrimary) {
        auto col = pPrimary ? pObj->m_baseColor : pObj->m_detailColor;

        return col && pColor == (col->m_colorID ? col->m_colorID : col->m_defaultColorID);
    }

    int id(GameObject* pObj) {
        return pObj->m_objectID;
    }
    std::vector<int> ids(std::span<GameObject*> pObjs, bool pSort) {
        std::unordered_set<int> ids;

        for (auto obj : pObjs) {
            ids.insert(obj->m_objectID);
        }

       std::vector<int> out = {ids.begin(), ids.end()};

        if (pSort) {
            std::ranges::sort(out);
        }

        return out;
    }
    std::vector<int> ids(CCArray* pObjs, bool pSort) {
        std::unordered_set<int> ids;

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            ids.insert(obj->m_objectID);
        }

        std::vector<int> out = {ids.begin(), ids.end()};

        if (pSort) {
            std::ranges::sort(out);
        }

        return out;
    }

    bool canSelectLayer(GameObject* pObj) {
        return editor::layerSelectable(pObj->m_editorLayer) || editor::layerSelectable(pObj->m_editorLayer2);
    }

    CCRect bounds(std::span<GameObject*> pObjs, bool pAddSize) {
        if (pObjs.empty()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : pObjs) {
            const auto pos = obj->getRealPosition();
            const auto size = pAddSize ? obj->getScaledContentSize() / 2 : CCSizeZero;

            min.x = std::min(min.x, pos.x - size.width);
            min.y = std::min(min.y, pos.y - size.height);
            max.x = std::max(max.x, pos.x + size.width);
            max.y = std::max(max.y, pos.y + size.height);
        }

        return {min, max - min};
    }
    CCRect bounds(CCArray* pObjs, bool pAddSize) {
        if (!pObjs->count()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            const auto pos = obj->getRealPosition();
            const auto size = pAddSize ? obj->getScaledContentSize() / 2 : CCSizeZero;

            min.x = std::min(min.x, pos.x - size.width);
            min.y = std::min(min.y, pos.y - size.height);
            max.x = std::max(max.x, pos.x + size.width);
            max.y = std::max(max.y, pos.y + size.height);
        }

        return {min, max - min};
    }
    CCPoint center(std::span<GameObject*> pObjs, bool pIgnoreParent) {
        if (pObjs.empty()) {
            return CCPointZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        GameObject* parent = nullptr;
        bool multipleParents = false;

        for (auto obj : pObjs) {
            const auto pos = obj->getRealPosition();

            min.x = std::min(min.x, pos.x);
            min.y = std::min(min.y, pos.y);
            max.x = std::max(max.x, pos.x);
            max.y = std::max(max.y, pos.y);

            if (!pIgnoreParent && obj->m_hasGroupParent) {
                // highkey code golfing but like who even cares
                parent = (multipleParents = parent) ? parent : obj;
            }
        }

        if (parent && !multipleParents) {
            return parent->getRealPosition();
        } 

        return (min + max) / 2;
    }
    CCPoint center(CCArray* pObjs, bool pIgnoreParent) {
        if (!pObjs->count()) {
            return CCPointZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        GameObject* parent = nullptr;
        bool multipleParents = false;

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            const auto pos = obj->getRealPosition();

            min.x = std::min(min.x, pos.x);
            min.y = std::min(min.y, pos.y);
            max.x = std::max(max.x, pos.x);
            max.y = std::max(max.y, pos.y);

            if (!pIgnoreParent && obj->m_hasGroupParent) {
                // highkey code golfing but like who even cares
                parent = (multipleParents = parent) ? parent : obj;
            }
        }

        if (parent && !multipleParents) {
            return parent->getRealPosition();
        } 

        return (min + max) / 2;
    }

    float size(GameObject* pObj) {
        return size(id(pObj)); 
    }
    float size(int pID) {
        return ObjectToolbox::sharedState()->gridNodeSizeForKey(pID); 
    }

    CCPoint snappedPos(GameObject* pObj, float pGridSize) {
        const auto id = editor::object::id(pObj);
        const auto offset = ui()->offsetForKey(id);
        const auto pos = pObj->getRealPosition() - offset;
        const auto gridSize = pGridSize * (editor::object::size(pObj) / 30.0f);

        return CCPoint{
            std::round(pos.x / gridSize) * gridSize,
            std::round(pos.y / gridSize) * gridSize
        } + offset;
    }

    void addGroup(GameObject* pObj, int pGroup) {
        if (loaded()) {
            layer()->addToGroup(pObj, pGroup, false);
        }
    }
    void addGroup(std::span<GameObject*> pObjs, int pGroup) {
        if (loaded()) {
            for (auto obj : pObjs) {
                layer()->addToGroup(obj, pGroup, false);
            }
        }
    }
    void addGroup(CCArray* pObjs, int pGroup) {
        if (loaded()) {
            for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
                layer()->addToGroup(obj, pGroup, false);
            }
        }
    }
    void removeGroup(GameObject* pObj, int pGroup) {
        if (loaded()) {
            layer()->removeFromGroup(pObj, pGroup);
        }
    }
    void removeGroup(std::span<GameObject*> pObjs, int pGroup) {
        if (loaded()) {
            for (auto obj : pObjs) {
                layer()->removeFromGroup(obj, pGroup);
            }
        }
    }
    void removeGroup(CCArray* pObjs, int pGroup) {
        if (loaded()) {
            for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
                layer()->removeFromGroup(obj, pGroup);
            }
        }
    }

    void remove(GameObject* pObj, bool pUndo) {
        if (notLoaded()) {
            return;
        }

        if (pUndo) {
            layer()->addToUndoList(UndoObject::create(pObj, UndoCommand::Delete), false);
        }

        editor::selection::remove(pObj);

        layer()->removeObject(pObj, !pUndo);
    }
    void remove(std::span<GameObject*> pObjs, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo && !pObjs.empty()) {
            layer()->addToUndoList(UndoObject::createWithArray(CCArrayExt(pObjs).inner(), UndoCommand::DeleteMulti), false);
        }

        editor::selection::remove(pObjs);

        for (auto obj : pObjs) {
            layer()->removeObject(obj, true);
        }
    }
    void remove(CCArray* pObjs, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo && pObjs->count()) {
            layer()->addToUndoList(UndoObject::createWithArray(pObjs, UndoCommand::DeleteMulti), false);
        }

        editor::selection::remove(pObjs);

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            layer()->removeObject(obj, true);
        }
    }

    void move(GameObject* pObj, CCPoint pTo, bool pUndo) {
        moveBy(pObj, pTo - pObj->getRealPosition());
    }
    void move(std::span<GameObject*> pObjs, CCPoint pTo, bool pUndo, CCPoint pCenter) {
        moveBy(pObjs, pTo - (pCenter == editor::AUTO_CENTER ? center(pObjs) : pCenter));
    }
    void move(CCArray* pObjs, CCPoint pTo, bool pUndo, CCPoint pCenter) {
        moveBy(pObjs, pTo - (pCenter == editor::AUTO_CENTER ? center(pObjs) : pCenter));
    }
    void moveBy(GameObject* pObj, CCPoint pOff, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        ui()->moveObject(pObj, pOff);
    }
    void moveBy(std::span<GameObject*> pObjs, CCPoint pOff, bool pUndo) {
        if (notLoaded() || pObjs.empty()) {
            return;
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : pObjs) {
            ui()->moveObject(obj, pOff);
        }
    }
    void moveBy(CCArray* pObjs, CCPoint pOff, bool pUndo) {
        if (notLoaded() || !pObjs->count()) {
            return;
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            ui()->moveObject(obj, pOff);
        }
    }

    void rotate(GameObject* pObj, float pTo, GameObject* pBase, bool pUndo, CCPoint pCenter, bool pMove) {
        rotateBy(pObj, pTo - pBase->getObjectRotation(), pUndo, pCenter, pMove);
    }
    void rotate(std::span<GameObject*> pObjs, float pTo, GameObject* pBase, bool pUndo, CCPoint pCenter, bool pMove) {
        rotateBy(pObjs, pTo - pBase->getObjectRotation(), pUndo, pCenter, pMove);
    }
    void rotate(CCArray* pObjs, float pTo, GameObject* pBase, bool pUndo, CCPoint pCenter, bool pMove) {
        rotateBy(pObjs, pTo - pBase->getObjectRotation(), pUndo, pCenter, pMove);
    }
    void rotateBy(GameObject* pObj, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        rotateBy(CCArray::createWithObject(pObj), pTo, pUndo, pCenter, pMove);
    }
    void rotateBy(std::span<GameObject*> pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        rotateBy(CCArrayExt(pObjs).inner(), pTo, pUndo, pCenter, pMove);
    }
    void rotateBy(CCArray* pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || !pObjs->count()) {
            return;
        }

        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        // i dont wanna rewrite rotate logic so for now the better edit way™ will have to do
        impl::toggleMoveObject(pMove);

        ui()->rotateObjects(pObjs, pTo, pCenter);

        impl::toggleMoveObject(true);
    }

    void scale(GameObject* pObj, float pX, float pY, bool pUndo) {
        scaleBy(pObj, pX / (pObj->m_scaleX ? pObj->m_scaleX : 1.0f), pY / (pObj->m_scaleY ? pObj->m_scaleY : 1.0f), pUndo);
    }
    void scale(GameObject* pObj, float pTo, bool pUndo) {
        const float maxScale = std::max(pObj->m_scaleX, pObj->m_scaleY);

        if (!maxScale) {
            return;
        }

        const auto mod = pTo / maxScale;

        scaleBy(pObj, mod, mod, pUndo);
    }
    void scaleX(GameObject* pObj, float pTo, bool pUndo) {
        const float maxScale = pObj->m_scaleX;

        if (!maxScale) {
            return;
        }

        scaleXBy(pObj, pTo / maxScale, pUndo);
    }
    void scaleY(GameObject* pObj, float pTo, bool pUndo) {
        const float maxScale = pObj->m_scaleY;

        if (!maxScale) {
            return;
        }

        scaleYBy(pObj, pTo / maxScale, pUndo);
    }
    void scale(std::span<GameObject*> pObjs, float pX, float pY, bool pUndo, CCPoint pCenter, bool pMove) {
        CCPoint maxScale = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : pObjs) {
            maxScale.x = std::max(maxScale.x, obj->m_scaleX);
            maxScale.y = std::max(maxScale.y, obj->m_scaleY);
        }

        scaleBy(pObjs, pX / (maxScale.x ? maxScale.x : 1.0f), pY / (maxScale.y ? maxScale.y : 1.0f), pUndo, pCenter, pMove);
    }
    void scale(std::span<GameObject*> pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : pObjs) {
            maxScale = std::max(maxScale, std::max(obj->m_scaleX, obj->m_scaleY));
        }

        if (!maxScale) {
            return;
        }

        const auto mod = pTo / maxScale;

        scaleBy(pObjs, mod, mod, pUndo, pCenter, pMove);
    }
    void scaleX(std::span<GameObject*> pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : pObjs) {
            maxScale = std::max(maxScale, obj->m_scaleX);
        }

        if (!maxScale) {
            return;
        }

        scaleXBy(pObjs, pTo / maxScale, pUndo, pCenter, pMove);
    }
    void scaleY(std::span<GameObject*> pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : pObjs) {
            maxScale = std::max(maxScale, obj->m_scaleY);
        }

        if (!maxScale) {
            return;
        }

        scaleYBy(pObjs, pTo / maxScale, pUndo, pCenter, pMove);
    }
    void scale(CCArray* pObjs, float pX, float pY, bool pUndo, CCPoint pCenter, bool pMove) {
        CCPoint maxScale = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            maxScale.x = std::max(maxScale.x, obj->m_scaleX);
            maxScale.y = std::max(maxScale.y, obj->m_scaleY);
        }

        scaleBy(pObjs, pX / (maxScale.x ? maxScale.x : 1.0f), pY / (maxScale.y ? maxScale.y : 1.0f), pUndo, pCenter, pMove);
    }
    void scale(CCArray* pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            maxScale = std::max(maxScale, std::max(obj->m_scaleX, obj->m_scaleY));
        }

        if (!maxScale) {
            return;
        }

        const auto mod = pTo / maxScale;

        scaleBy(pObjs, mod, mod, pUndo, pCenter, pMove);
    }
    void scaleX(CCArray* pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            maxScale = std::max(maxScale, obj->m_scaleX);
        }

        if (!maxScale) {
            return;
        }

        scaleXBy(pObjs, pTo / maxScale, pUndo, pCenter, pMove);
    }
    void scaleY(CCArray* pObjs, float pTo, bool pUndo, CCPoint pCenter, bool pMove) {
        float maxScale = std::numeric_limits<float>::lowest();

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            maxScale = std::max(maxScale, obj->m_scaleY);
        }

        if (!maxScale) {
            return;
        }

        scaleYBy(pObjs, pTo / maxScale, pUndo, pCenter, pMove);
    }
    void scaleBy(GameObject* pObj, float pX, float pY, bool pUndo) {
        if (notLoaded()) {
            return;
        }
        
        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        if (pX != 1.0f) {
            pObj->updateCustomScaleX(pObj->m_scaleX * pX);
        }
        if (pY != 1.0f) {
            pObj->updateCustomScaleY(pObj->m_scaleY * pY);
        }
    }
    void scaleBy(GameObject* pObj, float pMod, bool pUndo) {
        scaleBy(pObj, pMod, pMod, pUndo);
    }
    void scaleXBy(GameObject* pObj, float pMod, bool pUndo) {
        if (notLoaded() || !pMod || pMod == 1.0f) {
            return;
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        pObj->updateCustomScaleX(pObj->m_scaleX * pMod);
    }
    void scaleYBy(GameObject* pObj, float pMod, bool pUndo) {
        if (notLoaded() || !pMod || pMod == 1.0f) {
            return;
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        pObj->updateCustomScaleY(pObj->m_scaleY * pMod);
    }
    void scaleBy(std::span<GameObject*> pObjs, float pX, float pY, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || pObjs.empty()) {
            return;
        }

        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : pObjs) {
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{pX, pY});
            }

            if (pX != 1.0f) {
                obj->updateCustomScaleX(obj->m_scaleX * pX);
            }
            if (pY != 1.0f) {
                obj->updateCustomScaleY(obj->m_scaleY * pY);
            }
        }
    }
    void scaleBy(std::span<GameObject*> pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        scaleBy(pObjs, pMod, pMod, pUndo, pCenter, pMove);
    }
    void scaleXBy(std::span<GameObject*> pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || pObjs.empty() || !pMod || pMod == 1.0f) {
            return;
        }

        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : pObjs) {
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{pMod, 1.0f});
            }

            obj->updateCustomScaleX(obj->m_scaleX * pMod);
        }
    }
    void scaleYBy(std::span<GameObject*> pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || pObjs.empty() || !pMod || pMod == 1.0f) {
            return;
        }

        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : pObjs) {
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{1.0f, pMod});
            }

            obj->updateCustomScaleY(obj->m_scaleY * pMod);
        }
    }
    void scaleBy(CCArray* pObjs, float pX, float pY, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || !pObjs->count()) {
            return;
        }
        
        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{pX, pY});
            }

            if (pX && pX != 1.0f) {
                obj->updateCustomScaleX(obj->m_scaleX * pX);
            }
            if (pY && pY != 1.0f) {
                obj->updateCustomScaleY(obj->m_scaleY * pY);
            }
        }
    }
    void scaleBy(CCArray* pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        scaleBy(pObjs, pMod, pMod, pUndo, pCenter, pMove);
    }
    void scaleXBy(CCArray* pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || !pObjs->count() || !pMod || pMod == 1.0f) {
            return;
        }
        
        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {        
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{pMod, 1.0f});
            }

            obj->updateCustomScaleX(obj->m_scaleX * pMod);
        }
    }
    void scaleYBy(CCArray* pObjs, float pMod, bool pUndo, CCPoint pCenter, bool pMove) {
        if (notLoaded() || !pObjs->count() || !pMod || pMod == 1.0f) {
            return;
        }
        
        if (pCenter == editor::AUTO_CENTER) {
            pCenter = center(pObjs);
        }

        if (pUndo) {
            editor::impl::createUndoObject(UndoCommand::Transform);
        }

        for (auto obj : CCArrayExt<GameObject*>(pObjs)) {        
            if (pMove) {
                move(obj, pCenter + (obj->getRealPosition() - pCenter) * CCSize{1.0f, pMod});
            }

            obj->updateCustomScaleY(obj->m_scaleY * pMod);
        }
    }
}