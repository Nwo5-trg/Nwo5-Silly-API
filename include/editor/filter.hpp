#pragma once

#include "trigger.hpp"

namespace nwo5::editor::object {
    /// check if an object is a specific type a bit faster than a typeinfo cast
    /// @note offers the most performance increase for triggers since almost all of them are specialized here
    /// @returns a casted ptr to the obj or nullptr (should just be treated like a bool)
    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    T* is(GameObject* obj) {
        if constexpr (std::same_as<T, GameObject>) {
            return obj;
        }

        if constexpr (std::same_as<T, EffectGameObject>) {
            if (trigger::type(obj) != trigger::ObjectType::Normal || obj->m_classType == GameObjectClassType::Effect) {
                return static_cast<T*>(obj);
            }
        }
        else if constexpr (std::same_as<T, EnhancedGameObject>) {
            if (obj->m_classType == GameObjectClassType::Enhanced) {
                return static_cast<T*>(obj);
            }
        }
        else if constexpr(std::same_as<T, EnterEffectObject>) {
            const auto category = trigger::category(obj);

            if (category == trigger::Category::Area || category == trigger::Category::EditArea || category == trigger::Category::EnterEffect || category == trigger::Category::AdvancedEnter) {
                return static_cast<T*>(obj);
            }

            return nullptr;
        }
        else if constexpr(std::same_as<T, ShaderGameObject>) {
            return trigger::category(obj) == trigger::Category::Shader ?  static_cast<T*>(obj) : nullptr;
        }
        else if constexpr(std::same_as<T, CameraTriggerGameObject>) {
            return trigger::category(obj) == trigger::Category::Camera && obj->m_objectID != trigger::ZOOM_TRIGGER && obj->m_objectID != trigger::GP_OFFSET_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, ArtTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::BG_TRIGGER || id == trigger::GROUND_TRIGGER || id == trigger::MG_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, CountTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::COUNT_TRIGGER || id == trigger::INSTANT_COUNT_TRIGGER || id == trigger::PICKUP_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, TimerTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::TIME_TRIGGER || id == trigger::TIME_EVENT_TRIGGER || id == trigger::TIME_CONTROL_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, ItemTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::ITEM_EDIT_TRIGGER || id == trigger::ITEM_COMP_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, SongTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::SONG_TRIGGER || id == trigger::EDIT_SONG_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, SFXTriggerGameObject>) {
            const auto id = obj->m_objectID;
            return (id == trigger::SFX_TRIGGER || id == trigger::EDIT_SFX_TRIGGER) ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, KeyframeAnimTriggerObject>) {
            return obj->m_objectID == trigger::KEYFRAME_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, SpawnTriggerGameObject>) {
            return obj->m_objectID == trigger::SPAWN_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, TransformTriggerGameObject>) {
            return obj->m_objectID == trigger::SCALE_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, RandTriggerGameObject>) {
            return obj->m_objectID == trigger::ADVANCED_RANDOM_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, SequenceTriggerGameObject>) {
            return obj->m_objectID == trigger::SEQUENCE_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, SpawnParticleGameObject>) {
            return obj->m_objectID == trigger::SPAWN_PARTICLE_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, RotateGameplayGameObject>) {
            return obj->m_objectID == trigger::GAMEPLAY_ROTATE_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, EventLinkTrigger>) {
            return obj->m_objectID == trigger::EVENT_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, UISettingsGameObject>) {
            return obj->m_objectID == trigger::UI_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, EndTriggerGameObject>) {
            return obj->m_objectID == trigger::END_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, PlayerControlGameObject>) {
            return obj->m_objectID == trigger::PLAYER_CONTROL_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, GameOptionsTrigger>) {
            return obj->m_objectID == trigger::OPTIONS_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, GradientTriggerObject>) {
            return obj->m_objectID == trigger::GRADIENT_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        else if constexpr (std::same_as<T, TeleportPortalObject>) {
            return obj->m_objectID == trigger::TELEPORT_TRIGGER ? static_cast<T*>(obj) : nullptr;
        }
        
        return geode::cast::typeinfo_cast<T*>(obj);
    }

    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    cocos2d::CCArray* filter(cocos2d::CCArray* objs) {
        auto out = cocos2d::CCArray::createWithCapacity(objs->count());

        for (auto obj : geode::cocos::CCArrayExt<GameObject*>(out)) {
            if (is<T>(obj)) {
                out->addObject(obj);
            }
        }

        return out;
    }
}