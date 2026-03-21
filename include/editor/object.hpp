#pragma once

#include "editor.hpp"

namespace nwo5::editor::object {
    SILLY_API_DLL size_t count();

    SILLY_API_DLL cocos2d::CCArray* getAll(bool pCopy = false);
    /// @note will copy anyway (creating a new empty ccarray) if pGroup doesnt have a m_groupDict entry
    SILLY_API_DLL cocos2d::CCArray* getWithGroup(int pGroup, bool pCopy = false);
    /// get group parent
    /// @returns group parent or returns nullptr if group has no group parent
    SILLY_API_DLL GameObject* getParent(int pGroup);

    SILLY_API_DLL std::vector<int> groups(GameObject* pObj);
    SILLY_API_DLL std::vector<int> groups(std::span<GameObject*> pObjs, bool pSort = false);
    SILLY_API_DLL std::vector<int> groups(cocos2d::CCArray* pObjs, bool pSort = false);
    /// check if an object has groups
    /// @returns true if object has any groups, false otherwise
    SILLY_API_DLL bool hasGroups(GameObject* pObj);
    /// check if an object has a group
    /// @returns true if object has group or group is 0
    SILLY_API_DLL bool hasGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL bool sharesGroup(std::span<GameObject*> pObjs, int pGroup);
    SILLY_API_DLL bool sharesGroup(cocos2d::CCArray* pObjs, int pGroup);
    /// check if a group has a group parent
    /// @returns true if group has a parent, false otherwise
    SILLY_API_DLL bool hasParent(int pGroup);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(std::span<GameObject*> pObjs, int pGroup);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(cocos2d::CCArray* pObjs, int pGroup);


    SILLY_API_DLL bool hasColor(GameObject* pObj, int pColor, bool pPrimary);

    SILLY_API_DLL int id(GameObject* pObj);
    SILLY_API_DLL std::vector<int> ids(std::span<GameObject*> pObjs, bool pSort = false);
    SILLY_API_DLL std::vector<int> ids(cocos2d::CCArray* pObjs, bool pSort = false);

    SILLY_API_DLL bool canSelectLayer(GameObject* pObj);

    /// get bounds of objects
    /// @param pAddSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top rght most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(std::span<GameObject*> pObjs, bool pAddSize = false);
    /// get bounds of objects
    /// @param pAddSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top rght most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(cocos2d::CCArray* pObjs, bool pAddSize = false);
    SILLY_API_DLL cocos2d::CCPoint center(std::span<GameObject*> pObjs, bool pIgnoreParent = false);
    SILLY_API_DLL cocos2d::CCPoint center(cocos2d::CCArray* pObjs, bool pIgnoreParent = false);

    /// get (grid)size of object
    SILLY_API_DLL float size(GameObject* pObj);
    /// get (grid)size of object id
    SILLY_API_DLL float size(int pID);

    /// gets grid snapped pos of object
    /// @param pGridSize grid size object is snapped to
    /// @returns pos of object snapped to pGridSize
    SILLY_API_DLL cocos2d::CCPoint snappedPos(GameObject* pObj, float pGridSize = 30.0f);

    SILLY_API_DLL void addGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL void addGroup(std::span<GameObject*> pObjs, int pGroup);
    SILLY_API_DLL void addGroup(cocos2d::CCArray* pObjs, int pGroup);
    SILLY_API_DLL void removeGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL void removeGroup(std::span<GameObject*> pObjs, int pGroup);
    SILLY_API_DLL void removeGroup(cocos2d::CCArray* pObjs, int pGroup);

    /// deletes object
    SILLY_API_DLL void remove(GameObject* pObj, bool pUndo = false);
    /// deletes objects
    SILLY_API_DLL void remove(std::span<GameObject*> pObjs, bool pUndo = false);
    /// deletes objects
    SILLY_API_DLL void remove(cocos2d::CCArray* pObjs, bool pUndo = false);

    SILLY_API_DLL void move(GameObject* pObj, cocos2d::CCPoint pTo, bool pUndo = false);
    SILLY_API_DLL void move(std::span<GameObject*> pObjs, cocos2d::CCPoint pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER);
    SILLY_API_DLL void move(cocos2d::CCArray* pObjs, cocos2d::CCPoint pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER);
    SILLY_API_DLL void moveBy(GameObject* pObj, cocos2d::CCPoint pOff, bool pUndo = false);
    SILLY_API_DLL void moveBy(std::span<GameObject*> pObjs, cocos2d::CCPoint pOff, bool pUndo = false);
    SILLY_API_DLL void moveBy(cocos2d::CCArray* pObjs, cocos2d::CCPoint pOff, bool pUndo = false);

    SILLY_API_DLL void scale(std::span<GameObject*> pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(std::span<GameObject*> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleX(std::span<GameObject*> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleY(std::span<GameObject*> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleX(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleY(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(std::span<GameObject*> pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(std::span<GameObject*> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleXBy(std::span<GameObject*> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleYBy(std::span<GameObject*> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleXBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleYBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
}