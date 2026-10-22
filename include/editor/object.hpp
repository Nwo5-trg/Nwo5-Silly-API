#pragma once

#include "constants.hpp"
#include "editor.hpp"

namespace nwo5::editor::object {
    namespace impl {
        SILLY_API_DLL GameObject* createObject(int id, cocos2d::CCPoint pos, bool undo = false, bool setup = true);
        SILLY_API_DLL GameObject* createObject(int id, cocos2d::CCPoint pos, geode::ZStringView args, bool undo = false);
        SILLY_API_DLL GameObject* createObject(geode::ZStringView str, bool undo = false);
        SILLY_API_DLL cocos2d::CCArray* createObjects(geode::ZStringView str, bool undo = false);
    }
    
    /// get obj string
    SILLY_API_DLL std::string string(GameObject* obj);
    /// get obj string seperated with ;
    SILLY_API_DLL std::string string(std::span<GameObject* const> objs);
    /// get obj string seperated with ;
    SILLY_API_DLL std::string string(cocos2d::CCArray* objs);

    /// create basic object
    /// @param id obj id
    /// @param setup do the basic object setup (e.g. 0.5 duration default for triggers)
    /// @returns obj created
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    GameObject* create(int id, bool undo = false, bool setup = true) {
        return static_cast<T*>(impl::createObject(id, cocos2d::CCPointZero, undo, setup));
    }
    /// create basic object
    /// @param id obj id
    /// @param pos pos to create obj at
    /// @param setup do the basic object setup (e.g. 0.5 duration default for triggers)
    /// @returns obj created
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    GameObject* create(int id, cocos2d::CCPoint pos, bool undo = false, bool setup = true) {
        return static_cast<T*>(impl::createObject(id, pos, undo, setup));
    }
    /// pretty much fmt::format("1,{},2,0,3,0,{}", id, args)
    /// @param id obj id
    /// @param args any additional config for the obj as an obj string, can include leading comma
    /// @returns obj created
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    GameObject* create(int id, geode::ZStringView args, bool undo = false) {
        return static_cast<T*>(impl::createObject(id, cocos2d::CCPointZero, args, undo));
    }
    /// pretty much fmt::format("1,{},2,{},3,{},{}", id, pos.x, pos.y, args)
    /// @param id obj id
    /// @param pos pos to create obj at
    /// @param args any additional config for the obj as an obj string, can include leading comma
    /// @note does *not* do basic obj setup (e.g. 0.5 duration default for triggers)
    /// @returns obj created
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    GameObject* create(int id, cocos2d::CCPoint pos, geode::ZStringView args, bool undo = false) {
        return static_cast<T*>(impl::createObject(id, pos, args, undo));
    }
    /// create object from string
    /// @param str obj string
    /// @returns objscreated
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    GameObject* create(geode::ZStringView str, bool undo = false) {
        return static_cast<T*>(impl::createObject(str, undo));
    }
    /// create mutliple objects from string
    /// @param str obj string
    /// @returns objs created
    template<typename ImplT = GameObject, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    geode::cocos::CCArrayExt<T> createMulti(geode::ZStringView str, bool undo = false) {
        return impl::createObjects(str, undo);
    }

    /// deletes object
    SILLY_API_DLL void remove(GameObject* obj, bool undo = false);
    /// deletes objects
    SILLY_API_DLL void remove(std::span<GameObject* const> objs, bool undo = false);
    /// deletes objects
    SILLY_API_DLL void remove(cocos2d::CCArray* objs, bool undo = false);

    SILLY_API_DLL std::vector<int> groups(GameObject* obj);
    SILLY_API_DLL std::vector<int> groups(std::span<GameObject* const> objs, bool sort = false);
    SILLY_API_DLL std::vector<int> groups(cocos2d::CCArray* objs, bool sort = false);

    /// check if an object has any groups
    /// @returns true if object has any groups, false otherwise
    SILLY_API_DLL bool hasGroups(GameObject* obj);
    /// check if an object has a specific group
    /// @param group
    /// @returns true if object has group or group is 0
    SILLY_API_DLL bool hasGroup(GameObject* obj, int group);

    SILLY_API_DLL bool sharesGroup(std::span<GameObject* const> objs, int group);
    SILLY_API_DLL bool sharesGroup(cocos2d::CCArray* objs, int group);
    SILLY_API_DLL std::vector<int> sharedGroups(std::span<GameObject* const> objs, bool sort = false);
    SILLY_API_DLL std::vector<int> sharedGroups(cocos2d::CCArray* objs, bool sort = false);

    /// add group to object
    /// @param obj target
    /// @param group group
    SILLY_API_DLL void addGroup(GameObject* obj, int group);
    /// add group to objects
    /// @param objs targets
    /// @param group group
    SILLY_API_DLL void addGroup(std::span<GameObject* const> objs, int group);
    /// add group to objects
    /// @param objs targets
    /// @param group group
    SILLY_API_DLL void addGroup(cocos2d::CCArray* objs, int group);
    /// remove group from object
    /// @param obj targets
    /// @param group group
    SILLY_API_DLL void removeGroup(GameObject* obj, int group);
    /// remove group from objects
    /// @param objs targets
    /// @param group group
    SILLY_API_DLL void removeGroup(std::span<GameObject* const> objs, int group);
    /// remove group from objects
    /// @param objs targets
    /// @param group group
    SILLY_API_DLL void removeGroup(cocos2d::CCArray* objs, int group);

    /// check if a group has a group parent
    /// @returns true if group has a parent, false otherwise
    SILLY_API_DLL bool hasParent(int group);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(std::span<GameObject* const> objs, int group);
    /// checks if objects contains the group parent for group
    /// @returns true if objects has groups group parent, false otherwise
    SILLY_API_DLL bool hasParent(cocos2d::CCArray* objs, int group);

    SILLY_API_DLL std::optional<int> baseColor(GameObject* obj);
    /// set objects color channel or does nothing if object doesnt support base color
    /// @param color color channel
    /// @note pretty much js a decomp of CustomizeObjectLayer::updateSelected
    SILLY_API_DLL void setBaseColor(GameObject* obj, int color);
    SILLY_API_DLL std::optional<int> detailColor(GameObject* obj);
    /// set objects color channel or does nothing if object doesnt support detail color
    /// @param color color channel
    /// @note pretty much js a decomp of CustomizeObjectLayer::updateSelected
    SILLY_API_DLL void setDetailColor(GameObject* obj, int color);
    SILLY_API_DLL bool hasColor(GameObject* obj, int color, bool primary);
    
    /// get obj id
    /// @returns obj id
    SILLY_API_DLL int id(GameObject* obj);
    /// get obj id(s)
    /// @param sort sort the output vector
    /// @returns obj ids
    SILLY_API_DLL std::vector<int> ids(std::span<GameObject* const> objs, bool sort = false);
    /// get obj id(s)
    /// @param sort sort the output vector
    /// @returns obj ids
    SILLY_API_DLL std::vector<int> ids(cocos2d::CCArray* objs, bool sort = false);

    /// get object editor layer
    /// @returns editor layer
    SILLY_API_DLL int layer(GameObject* obj);
    /// set object editor layer
    SILLY_API_DLL void setLayer(GameObject* obj, int layer);
    /// set objects editor layer
    SILLY_API_DLL void setLayer(std::span<GameObject* const> objs, int layer);
    /// set objects editor layer
    SILLY_API_DLL void setLayer(cocos2d::CCArray* objs, int layer);
    /// get object secondary editor layer
    /// @returns secondary editor layer
    SILLY_API_DLL int layer2(GameObject* obj);
    /// set object secondary editor layer
    SILLY_API_DLL void setLayer2(GameObject* obj, int layer);
    /// set objects secondary editor layer
    SILLY_API_DLL void setLayer2(std::span<GameObject* const> objs, int layer);
    /// set objects secondary editor layer
    SILLY_API_DLL void setLayer2(cocos2d::CCArray* objs, int layer);

    SILLY_API_DLL bool canSelectLayer(GameObject* obj, bool ignoreLocked = false);

    /// get object z order
    SILLY_API_DLL int zOrder(GameObject* obj);
    /// set object z order
    SILLY_API_DLL void setZOrder(GameObject* obj, int order);
    /// set objects z order
    SILLY_API_DLL void setZOrder(std::span<GameObject* const> objs, int order);
    /// set objects z order
    SILLY_API_DLL void setZOrder(cocos2d::CCArray* objs, int order);

    /// get bounds of objects
    /// @param contentSize use content size of object instead of grid size
    /// @returns bounds or CCRectZero, origin is the center of the bottom left, size is distance to the top right
    SILLY_API_DLL cocos2d::CCRect bounds(GameObject* obj, bool contentSize = false);
    /// get bounds of objects
    /// @param addSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top right most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(std::span<GameObject* const> objs, bool addSize = false);
    /// get bounds of objects
    /// @param addSize adds scaled content size of the objects to the position checked
    /// @returns bounds or CCRectZero, origin is the center of the bottom left most object, size is distance to the top right most objects center
    SILLY_API_DLL cocos2d::CCRect bounds(cocos2d::CCArray* objs, bool addSize = false);
    /// get center of objects
    /// @param objs objects
    /// @param ignoreParent use robtops function if false lol
    /// @returns center of bounds or parent group
    SILLY_API_DLL cocos2d::CCPoint center(std::span<GameObject* const> objs, bool ignoreParent = true);
    /// get center of objects
    /// @param objs objects
    /// @param ignoreParent use robtops function if false lol
    /// @returns center of bounds
    SILLY_API_DLL cocos2d::CCPoint center(cocos2d::CCArray* objs, bool ignoreParent = true);

    /// cluster objects in place
    /// @param out output vector
    /// @param objs objects
    /// @param clusterSize cluster size
    SILLY_API_DLL void cluster(std::vector<std::vector<GameObject*>>& out, std::span<GameObject* const> objs, float clusterSize);
    /// cluster objects in place
    /// @param out output vector
    /// @param objs objects
    /// @param clusterSize cluster size
    SILLY_API_DLL void cluster(std::vector<std::vector<GameObject*>>& out, cocos2d::CCArray* objs, float clusterSize);
    /// cluster objects not in place (why)
    /// @param objs objects
    /// @param clusterSize cluster size
    /// @returns object clusters
    SILLY_API_DLL std::vector<std::vector<GameObject*>> cluster(std::span<GameObject* const> objs, float clusterSize);
    /// cluster objects not in place (why)
    /// @param objs objects
    /// @param clusterSize cluster size
    /// @returns object clusters
    SILLY_API_DLL std::vector<std::vector<GameObject*>> cluster(cocos2d::CCArray* objs, float clusterSize);

    /// get (grid)size of object
    SILLY_API_DLL float size(GameObject* obj);
    /// get (grid)size of object id
    SILLY_API_DLL float size(int id);
    
    SILLY_API_DLL void move(GameObject* obj, cocos2d::CCPoint to, bool undo = false);
    SILLY_API_DLL void move(std::span<GameObject* const> objs, cocos2d::CCPoint to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt);
    SILLY_API_DLL void move(cocos2d::CCArray* objs, cocos2d::CCPoint to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt);
    SILLY_API_DLL void moveBy(GameObject* obj, cocos2d::CCPoint off, bool undo = false);
    SILLY_API_DLL void moveBy(std::span<GameObject* const> objs, cocos2d::CCPoint off, bool undo = false);
    SILLY_API_DLL void moveBy(cocos2d::CCArray* objs, cocos2d::CCPoint off, bool undo = false);

    SILLY_API_DLL void rotate(GameObject* obj, float to, GameObject* base, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void rotate(std::span<GameObject* const> objs, float to, GameObject* base, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void rotate(cocos2d::CCArray* objs, float to, GameObject* base, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void rotateBy(GameObject* obj, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void rotateBy(std::span<GameObject* const> objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void rotateBy(cocos2d::CCArray* objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);

    SILLY_API_DLL void scale(GameObject* obj, float x, float y, bool undo = false);
    SILLY_API_DLL void scale(GameObject* obj, float to, bool undo = false);
    SILLY_API_DLL void scaleX(GameObject* obj, float to, bool undo = false);
    SILLY_API_DLL void scaleY(GameObject* obj, float to, bool undo = false);
    SILLY_API_DLL void scale(std::span<GameObject* const> objs, float x, float y, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scale(std::span<GameObject* const> objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleX(std::span<GameObject* const> objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleY(std::span<GameObject* const> objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* objs, float x, float y, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scale(cocos2d::CCArray* objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleX(cocos2d::CCArray* objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleY(cocos2d::CCArray* objs, float to, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleBy(GameObject* obj, float x, float y, bool undo = false);
    SILLY_API_DLL void scaleBy(GameObject* obj, float mod, bool undo = false);
    SILLY_API_DLL void scaleXBy(GameObject* obj, float mod, bool undo = false);
    SILLY_API_DLL void scaleYBy(GameObject* obj, float mod, bool undo = false);
    SILLY_API_DLL void scaleBy(std::span<GameObject* const> objs, float x, float y, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleBy(std::span<GameObject* const> objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleXBy(std::span<GameObject* const> objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleYBy(std::span<GameObject* const> objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* objs, float x, float y, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleBy(cocos2d::CCArray* objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleXBy(cocos2d::CCArray* objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
    SILLY_API_DLL void scaleYBy(cocos2d::CCArray* objs, float mod, bool undo = false, std::optional<cocos2d::CCPoint> center = std::nullopt, bool move = true);
}