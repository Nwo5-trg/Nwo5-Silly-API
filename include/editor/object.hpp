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

    /// get obj string
    SILLY_API_DLL std::string string(GameObject* pObj);
    /// get obj string seperated with ;
    SILLY_API_DLL std::string string(std::span<GameObject* const> pObjs);
    /// get obj string seperated with ;
    SILLY_API_DLL std::string string(cocos2d::CCArray* pObjs);
    /// create basic object
    /// @param pSetup do the basic object setup (e.g. 0.5 duration default for triggers)
    SILLY_API_DLL GameObject* createObject(int pID, bool pUndo = false, bool pSetup = true);
    /// create basic object
    /// @param pSetup do the basic object setup (e.g. 0.5 duration default for triggers)
    SILLY_API_DLL GameObject* createObject(int pID, cocos2d::CCPoint pPos, bool pUndo = false, bool pSetup = true);
    /// pretty much fmt::format("1,{},2,0,3,0,{}", pID, pArgs)
    /// @note pArgs can have a leading comma
    SILLY_API_DLL GameObject* createObject(int pID, geode::ZStringView pArgs, bool pUndo = false);
    /// pretty much fmt::format("1,{},2,{},3,{},{}", pID, pPos.x, pPos.y, pArgs)
    /// @note pArgs can have a leading comma
    SILLY_API_DLL GameObject* createObject(int pID, cocos2d::CCPoint pPos, geode::ZStringView pArgs, bool pUndo = false);
    /// create object from string
    SILLY_API_DLL GameObject* createObject(geode::ZStringView pStr, bool pUndo = false);
    /// create objects from string
    SILLY_API_DLL cocos2d::CCArray* createObjects(geode::ZStringView pStr, bool pUndo = false);

    SILLY_API_DLL std::vector<int> groups(GameObject* pObj);
    SILLY_API_DLL std::vector<int> groups(std::span<GameObject* const> pObjs, bool pSort = false);
    SILLY_API_DLL std::vector<int> groups(cocos2d::CCArray* pObjs, bool pSort = false);
    /// check if an object has groups
    /// @returns true if object has any groups, false otherwise
    SILLY_API_DLL bool hasGroups(GameObject* pObj);
    /// check if an object has a group
    /// @returns true if object has group or group is 0
    SILLY_API_DLL bool hasGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL bool sharesGroup(std::span<GameObject* const> pObjs, int pGroup);
    SILLY_API_DLL bool sharesGroup(cocos2d::CCArray* pObjs, int pGroup);
    /// check if a group has a group parent
    /// @returns true if group has a parent, false otherwise
    SILLY_API_DLL bool hasParent(int pGroup);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(std::span<GameObject* const> pObjs, int pGroup);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(cocos2d::CCArray* pObjs, int pGroup);

    SILLY_API_DLL std::optional<int> baseColor(GameObject* pObj);
    SILLY_API_DLL std::optional<int> detailColor(GameObject* pObj);
    SILLY_API_DLL bool hasColor(GameObject* pObj, int pColor, bool pPrimary);

    SILLY_API_DLL int id(GameObject* pObj);
    SILLY_API_DLL std::vector<int> ids(std::span<GameObject* const> pObjs, bool pSort = false);
    SILLY_API_DLL std::vector<int> ids(cocos2d::CCArray* pObjs, bool pSort = false);

    SILLY_API_DLL bool canSelectLayer(GameObject* pObj, bool pIgnoreLocked = false);

    /// get bounds of objects
    /// @param pContentSize use content size of object instead of grid size
    /// @returns bounds or CCRectZero, origin is the center of the bottom left, size is distance to the top right
    SILLY_API_DLL cocos2d::CCRect bounds(GameObject* pObj, bool pContentSize = false);
    /// get bounds of objects
    /// @param pAddSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top right most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(std::span<GameObject* const> pObjs, bool pAddSize = false);
    /// get bounds of objects
    /// @param pAddSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top right most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(cocos2d::CCArray* pObjs, bool pAddSize = false);
    SILLY_API_DLL cocos2d::CCPoint center(std::span<GameObject* const> pObjs, bool pIgnoreParent = false);
    SILLY_API_DLL cocos2d::CCPoint center(cocos2d::CCArray* pObjs, bool pIgnoreParent = false);

    SILLY_API_DLL void cluster(std::vector<std::vector<GameObject*>>& pOut, std::span<GameObject* const> pObjs, float pClusterSize);
    SILLY_API_DLL void cluster(std::vector<std::vector<GameObject*>>& pOut, cocos2d::CCArray* pObjs, float pClusterSize);
    SILLY_API_DLL std::vector<std::vector<GameObject*>> cluster(std::span<GameObject* const> pObjs, float pClusterSize);
    SILLY_API_DLL std::vector<std::vector<GameObject*>> cluster(cocos2d::CCArray* pObjs, float pClusterSize);

    /// get (grid)size of object
    SILLY_API_DLL float size(GameObject* pObj);
    /// get (grid)size of object id
    SILLY_API_DLL float size(int pID);

    /// gets grid snapped pos of object
    /// @param pGridSize grid size object is snapped to
    /// @returns pos of object snapped to pGridSize
    SILLY_API_DLL cocos2d::CCPoint snappedPos(GameObject* pObj, float pGridSize = 30.0f);

    /// move camera to obj and optionally zoom out
    /// @param pZoomToFit zoom out to fit obj on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(GameObject* pObj, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param pZoomToFit zoom out to fit objs on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(std::span<GameObject* const> pObjs, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());
    /// move camera to objs and optionally zoom out
    /// @param pZoomToFit zoom out to fit objs on screen
    /// @param pZoomBuffer *divide* zoom by this
    /// @param pMinimumZoom clamps zoom to this
    /// @param pMaximumZoom clamps zoom to this
    SILLY_API_DLL void moveTo(cocos2d::CCArray* pObjs, bool pZoomToFit = true, float pZoomBuffer = 1.5f, float pMinimumZoom = 0.0f, float pMaximumZoom = editor::zoom());

    SILLY_API_DLL void addGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL void addGroup(std::span<GameObject* const> pObjs, int pGroup);
    SILLY_API_DLL void addGroup(cocos2d::CCArray* pObjs, int pGroup);
    SILLY_API_DLL void removeGroup(GameObject* pObj, int pGroup);
    SILLY_API_DLL void removeGroup(std::span<GameObject* const> pObjs, int pGroup);
    SILLY_API_DLL void removeGroup(cocos2d::CCArray* pObjs, int pGroup);

    /// deletes object
    SILLY_API_DLL void remove(GameObject* pObj, bool pUndo = false);
    /// deletes objects
    SILLY_API_DLL void remove(std::span<GameObject* const> pObjs, bool pUndo = false);
    /// deletes objects
    SILLY_API_DLL void remove(cocos2d::CCArray* pObjs, bool pUndo = false);

    SILLY_API_DLL void move(GameObject* pObj, cocos2d::CCPoint pTo, bool pUndo = false);
    SILLY_API_DLL void move(std::span<GameObject* const> pObjs, cocos2d::CCPoint pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER);
    SILLY_API_DLL void move(cocos2d::CCArray* pObjs, cocos2d::CCPoint pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER);
    SILLY_API_DLL void moveBy(GameObject* pObj, cocos2d::CCPoint pOff, bool pUndo = false);
    SILLY_API_DLL void moveBy(std::span<GameObject* const> pObjs, cocos2d::CCPoint pOff, bool pUndo = false);
    SILLY_API_DLL void moveBy(cocos2d::CCArray* pObjs, cocos2d::CCPoint pOff, bool pUndo = false);

    SILLY_API_DLL void rotate(GameObject* pObj, float pTo, GameObject* pBase, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void rotate(std::span<GameObject* const> pObjs, float pTo, GameObject* pBase, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void rotate(cocos2d::CCArray* pObjs, float pTo, GameObject* pBase, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void rotateBy(GameObject* pObj, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void rotateBy(std::span<GameObject* const> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void rotateBy(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);

    SILLY_API_DLL void scale(GameObject* pObj, float pX, float pY, bool pUndo = false);
    SILLY_API_DLL void scale(GameObject* pObj, float pTo, bool pUndo = false);
    SILLY_API_DLL void scaleX(GameObject* pObj, float pTo, bool pUndo = false);
    SILLY_API_DLL void scaleY(GameObject* pObj, float pTo, bool pUndo = false);
    SILLY_API_DLL void scale(std::span<GameObject* const> pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(std::span<GameObject* const> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleX(std::span<GameObject* const> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleY(std::span<GameObject* const> pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleX(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleY(cocos2d::CCArray* pObjs, float pTo, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(GameObject* pObj, float pX, float pY, bool pUndo = false);
    SILLY_API_DLL void scaleBy(GameObject* pObj, float pMod, bool pUndo = false);
    SILLY_API_DLL void scaleXBy(GameObject* pObj, float pMod, bool pUndo = false);
    SILLY_API_DLL void scaleYBy(GameObject* pObj, float pMod, bool pUndo = false);
    SILLY_API_DLL void scaleBy(std::span<GameObject* const> pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(std::span<GameObject* const> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleXBy(std::span<GameObject* const> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleYBy(std::span<GameObject* const> pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* pObjs, float pX, float pY, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleXBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
    SILLY_API_DLL void scaleYBy(cocos2d::CCArray* pObjs, float pMod, bool pUndo = false, cocos2d::CCPoint pCenter = editor::AUTO_CENTER, bool pMove = true);
}