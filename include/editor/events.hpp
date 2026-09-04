#pragma once

namespace nwo5::editor {
    /// object(s) selected
    /// @note pObjects is guaranteed not to be empty
    struct ObjectsSelectedEvent final : public geode::Event<ObjectsSelectedEvent, bool(cocos2d::CCArray* pObjects)> {
        using Event::Event;
    };
    /// object(s) deselected
    /// @note pObjects is guaranteed not to be empty
    struct ObjectsDeselectedEvent final : public geode::Event<ObjectsDeselectedEvent, bool(cocos2d::CCArray* pObjects)> {
        using Event::Event;
    };
    
    /// object(s) created
    /// filter is true if object is created by clicking, false otherwise
    /// @note if filter is true pObjects is guaranteed to only have 1 object
    /// @note pObjects is guaranteed not to be empty
    struct ObjectsCreatedEvent final : public geode::GlobalEvent<ObjectsCreatedEvent, bool(cocos2d::CCArray* pObjects), bool> {
        using GlobalEvent::GlobalEvent;
    };
    /// object deleted
    /// @note unlike other events, this one is triggered *before* the object is actually removed so u can do stuff with the ptr
    struct ObjectsDeletedEvent final : public geode::Event<ObjectsDeletedEvent, bool(cocos2d::CCArray* pObjects)> {
        using Event::Event;
    };

    /// object count changed
    /// @note pObjects is guaranteed not to be empty
    struct ObjectsChangedEvent final : public geode::Event<ObjectsChangedEvent, bool()> {
        using Event::Event;
    };

    /// playtested started/stopped
    /// @note if filter is true playtest has started
    struct OnPlaytestEvent final : public geode::GlobalEvent<OnPlaytestEvent, bool(), bool> {
        using GlobalEvent::GlobalEvent;
    };
};