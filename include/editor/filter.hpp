#pragma once

#include "trigger.hpp"

namespace nwo5::editor::object {
    /// check if an object is a specific type a bit faster than a typeinfo cast
    /// @note offers the most performance increase for triggers since almost all of them are specialized here
    /// @returns a casted ptr to the obj or nullptr (should just be treated like a bool)
    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    T* is(GameObject* pObj) {
        if constexpr (std::same_as<T, GameObject>) {
            return pObj;
        }

        if constexpr (std::same_as<T, EffectGameObject>) {
            if (trigger::type(pObj) != trigger::ObjectType::Normal || pObj->m_classType == GameObjectClassType::Effect) {
                return static_cast<T*>(pObj);
            }
        }
        else if constexpr (std::same_as<T, EnhancedGameObject>) {
            if (pObj->m_classType == GameObjectClassType::Enhanced) {
                return static_cast<T*>(pObj);
            }
        }
        else if constexpr(std::same_as<T, EnterEffectObject>) {
            const auto category = trigger::category(pObj);

            if (category == trigger::Category::Area || category == trigger::Category::EditArea || category == trigger::Category::EnterEffect || category == trigger::Category::AdvancedEnter) {
                return static_cast<T*>(pObj);
            }

            return nullptr;
        }
        else if constexpr(std::same_as<T, ShaderGameObject>) {
            return trigger::category(pObj) == trigger::Category::Shader ?  static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr(std::same_as<T, CameraTriggerGameObject>) {
            return trigger::category(pObj) == trigger::Category::Camera && pObj->m_objectID != trigger::ZOOM_TRIGGER && pObj->m_objectID != trigger::GP_OFFSET_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, ArtTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::BG_TRIGGER || id == trigger::GROUND_TRIGGER || id == trigger::MG_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, CountTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::COUNT_TRIGGER || id == trigger::INSTANT_COUNT_TRIGGER || id == trigger::PICKUP_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, TimerTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::TIME_TRIGGER || id == trigger::TIME_EVENT_TRIGGER || id == trigger::TIME_CONTROL_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, ItemTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::ITEM_EDIT_TRIGGER || id == trigger::ITEM_COMP_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, SongTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::SONG_TRIGGER || id == trigger::EDIT_SONG_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, SFXTriggerGameObject>) {
            const auto id = pObj->m_objectID;
            return (id == trigger::SFX_TRIGGER || id == trigger::EDIT_SFX_TRIGGER) ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, KeyframeAnimTriggerObject>) {
            return pObj->m_objectID == trigger::KEYFRAME_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, SpawnTriggerGameObject>) {
            return pObj->m_objectID == trigger::SPAWN_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, TransformTriggerGameObject>) {
            return pObj->m_objectID == trigger::SCALE_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, RandTriggerGameObject>) {
            return pObj->m_objectID == trigger::ADVANCED_RANDOM_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, SequenceTriggerGameObject>) {
            return pObj->m_objectID == trigger::SEQUENCE_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, SpawnParticleGameObject>) {
            return pObj->m_objectID == trigger::SPAWN_PARTICLE_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, RotateGameplayGameObject>) {
            return pObj->m_objectID == trigger::GAMEPLAY_ROTATE_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, EventLinkTrigger>) {
            return pObj->m_objectID == trigger::EVENT_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, UISettingsGameObject>) {
            return pObj->m_objectID == trigger::UI_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, EndTriggerGameObject>) {
            return pObj->m_objectID == trigger::END_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, PlayerControlGameObject>) {
            return pObj->m_objectID == trigger::PLAYER_CONTROL_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, GameOptionsTrigger>) {
            return pObj->m_objectID == trigger::OPTIONS_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, GradientTriggerObject>) {
            return pObj->m_objectID == trigger::GRADIENT_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        else if constexpr (std::same_as<T, TeleportPortalObject>) {
            return pObj->m_objectID == trigger::TELEPORT_TRIGGER ? static_cast<T*>(pObj) : nullptr;
        }
        
        return geode::cast::typeinfo_cast<T*>(pObj);
    }

    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    requires std::derived_from<T, GameObject>
    cocos2d::CCArray* filter(cocos2d::CCArray* pObjs) {
        auto out = cocos2d::CCArray::createWithCapacity(pObjs->count());

        for (auto obj : geode::cocos::CCArrayExt<GameObject*>(out)) {
            if (is<T>(obj)) {
                out->addObject(obj);
            }
        }

        return out;
    }
}