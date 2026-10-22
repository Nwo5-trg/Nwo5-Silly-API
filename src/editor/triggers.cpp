#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::trigger {
    bool is(int id) {
        return get(id).isTrigger();
    }
    bool is(GameObject* obj) {
        return get(obj).isTrigger();
    }
    ObjectType type(int id) {
        return get(id).type();
    }
    ObjectType type(GameObject* obj) {
        return get(obj).type();
    }

    const TriggerInfo& get(int id) {
        static const auto arr = impl::createTriggerInfoArray();
        
        if (id < COLOR_TRIGGER || id > constants::MAX_OBJECT_ID) {
            return arr.front();
        }

        return arr[id];
    }
    const TriggerInfo& get(GameObject* obj) {
        return get(obj->m_objectID);
    }

    int primaryTarget(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryTarget().exists()) {
            return 0;
        }

        if (info.category() == Category::EnterEffect || info.category() == Category::AdvancedEnter || id == ENTER_STOP_TRIGGER) {
            return static_cast<EnterEffectObject*>(obj)->m_enterChannel;
        }

        switch (id) {
            case COLOR_TRIGGER: return obj->m_targetColor;
            case PICKUP_TRIGGER: [[__fallthrough__]]; // fuck you compile with clang specifically cuz i think this looks a lil cooler :3
            case TIME_CONTROL_TRIGGER: [[__fallthrough__]];
            case ITEM_PERSIST_TRIGGER: [[__fallthrough__]];
            case PLATFORMER_PERCENT_TRIGGER: [[__fallthrough__]];
            case COLLISION_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_itemID;
            case STATIC_CAMERA_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_centerGroupID;
            case GAMEPLAY_ROTATE_TRIGGER: return static_cast<RotateGameplayGameObject*>(obj)->m_targetChannelID;
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case SONG_TRIGGER: return static_cast<SongTriggerGameObject*>(obj)->m_songChannel;
            case EDIT_SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(obj)->m_sfxUniqueID;
            default: return static_cast<EffectGameObject*>(obj)->m_targetGroupID;
        }
    }
    InputType primaryTargetType(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);

        if (!info.primaryTarget().exists()) {
            return InputType::None;
        }
        
        if (!info.primaryTarget().mixed() && !info.primaryTarget().conditional()) {
            return info.primaryTarget().type();
        }

        if (info.category() == Category::EditArea) {
            return static_cast<EnterEffectObject*>(obj)->m_useEffectID ? InputType::Effect : InputType::Group;
        }

        switch (id) {
            case EDIT_ADVANCED_FOLLOW_TRIGGER: [[__fallthrough__]];
            case RETARGET_ADVANCED_FOLLOW_TRIGGER: [[__fallthrough__]];
            case STOP_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_targetControlID ? InputType::Control : InputType::Group;
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_pulseTargetType == 1 ? InputType::Group : InputType::Color;
            case GAMEPLAY_ROTATE_TRIGGER: return static_cast<RotateGameplayGameObject*>(obj)->m_changeChannel ? InputType::Channel : InputType::None;
            case SHOCK_WAVE_SHADER_TRIGGER: [[__fallthrough__]];
            case SHOCK_LINE_SHADER_TRIGGER: [[__fallthrough__]];
            case RADIAL_BLUR_SHADER_TRIGGER: [[__fallthrough__]];
            case BULGE_SHADER_TRIGGER: return targetModeEnabled(obj) ? InputType::Group : InputType::None;
            default: return InputType::None;
        }

    }
    void setPrimaryTarget(GameObject* obj, int val) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryTarget().exists() ||info.primaryTarget().type() == InputType::GroupArray) {
            return;
        }

        if (info.category() == Category::EnterEffect || info.category() == Category::AdvancedEnter || id == ENTER_STOP_TRIGGER) {
            static_cast<EnterEffectObject*>(obj)->m_enterChannel = val;

            return;
        }

        switch (id) {
            case COLOR_TRIGGER: {
                obj->m_targetColor = val;
            break; }
            case PICKUP_TRIGGER: [[__fallthrough__]];
            case TIME_CONTROL_TRIGGER: [[__fallthrough__]];
            case ITEM_PERSIST_TRIGGER: [[__fallthrough__]];
            case PLATFORMER_PERCENT_TRIGGER: [[__fallthrough__]];
            case COLLISION_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_itemID = val;
            break; }
            case STATIC_CAMERA_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_centerGroupID = val;
            break; }
            case GAMEPLAY_ROTATE_TRIGGER: {
                static_cast<RotateGameplayGameObject*>(obj)->m_targetChannelID = val;
            break; }
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case SONG_TRIGGER: {
                static_cast<SongTriggerGameObject*>(obj)->m_songChannel = val;
            break; }
            case EDIT_SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(obj)->m_sfxUniqueID = val;
            break; }
            default: {
                static_cast<EffectGameObject*>(obj)->m_targetGroupID = val;
            break;}
        }
        
        if (auto layer = editor::layer()) {
            layer->updateObjectLabel(obj);
        }
    }
    int target(GameObject* obj) {
        return primaryTarget(obj);
    }
    InputType targetType(GameObject* obj) {
        return primaryTargetType(obj);
    }
    void setTarget(GameObject* obj, int val) {
        return setPrimaryTarget(obj, val);
    }

    int secondaryTarget(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryTarget().exists() || id == SPAWN_TRIGGER) {
            return 0;
        }

        if (info.category() == Category::Area) {
            const auto specialTarget = static_cast<EffectGameObject*>(obj)->m_specialTarget;

            if (specialTarget) {
                return specialTarget;
            }
        }

        switch (id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_copyColorID;
            case MOVE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_targetModCenterID;
            case ANIMATION_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_animationID;
            case COUNT_TRIGGER: [[__fallthrough__]];
            case INSTANT_COUNT_TRIGGER: [[__fallthrough__]];
            case TIME_TRIGGER: [[__fallthrough__]];
            case TIME_EVENT_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_itemID;
            case EDIT_SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(obj)->m_sfxGroup;
            case AREA_STOP_TRIGGER: return static_cast<EnterEffectObject*>(obj)->m_effectID;
            default: return static_cast<EffectGameObject*>(obj)->m_centerGroupID;
        }
    }
    InputType secondaryTargetType(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);

        if (!info.secondaryTarget().exists()) {
            return InputType::None;
        }
        
        if (!info.secondaryTarget().mixed() && !info.secondaryTarget().conditional()) {
            return info.secondaryTarget().type();
        }

        switch(id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_copyColorID ? InputType::Color : InputType::None;
            case MOVE_TRIGGER: return targetModeEnabled(obj) ? InputType::Group : InputType::None;
            default: return InputType::None;
        }
    }
    void setSecondaryTarget(GameObject* obj, int val) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryTarget().exists() || id == SPAWN_TRIGGER) {
            return;
        }

        if (info.category() == Category::Area) {
            auto trigger = static_cast<EffectGameObject*>(obj);

            if (val >= 0) {
                trigger->m_specialTarget = 0;
            }
            else {
                trigger->m_specialTarget = val;

                if (auto layer = editor::layer()) {
                    layer->updateObjectLabel(obj);
                }
                
                return;
            }
        }

        switch (id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_copyColorID = val;
            break; }
            case MOVE_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_targetModCenterID = val;
            break; }
            case ANIMATION_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_animationID = val;
            break; }
            case COUNT_TRIGGER: [[__fallthrough__]];
            case INSTANT_COUNT_TRIGGER: [[__fallthrough__]];
            case TIME_TRIGGER: [[__fallthrough__]];
            case TIME_EVENT_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_itemID = val;
            break; }
            case EDIT_SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(obj)->m_sfxGroup = val;
            break; }
            case AREA_STOP_TRIGGER: {
                static_cast<EnterEffectObject*>(obj)->m_effectID = val;
            break; }
            default: {
                static_cast<EffectGameObject*>(obj)->m_centerGroupID = val;
            break; }
        }

        if (auto layer = editor::layer()) {
            layer->updateObjectLabel(obj);
        }
    }
    int center(GameObject* obj) {
        return secondaryTarget(obj);
    }
    InputType centerType(GameObject* obj) {
        return secondaryTargetType(obj);
    }
    void setCenter(GameObject* obj, int val) {
        return setSecondaryTarget(obj, val);
    }

    int primaryInput(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryInput().exists()) {
            return 0;
        }

        if (info.category() == Category::Area || info.category() == Category::EnterEffect) {
            return static_cast<EnterEffectObject*>(obj)->m_effectID;
        }

        switch (id) {
            case MOVE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_targetModCenterID;
            case ROTATE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_rotationTargetID;
            case KEYFRAME_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_animationID;
            case SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(obj)->m_sfxUniqueID;
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_targetGroupID;
            case GRADIENT_TRIGGER: return static_cast<GradientTriggerObject*>(obj)->m_gradientID;
            default: return static_cast<EffectGameObject*>(obj)->m_itemID;
        }
    }
    InputType primaryInputType(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);

        if (!info.primaryInput().exists()) {
            return InputType::None;
        }
        
        if (id == MOVE_TRIGGER || id == ROTATE_TRIGGER) {
            return targetModeEnabled(obj) ? InputType::Group : InputType::None;
        }

        return info.primaryInput().type();
    }
    void setPrimaryInput(GameObject* obj, int val) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryInput().exists()) {
            return;
        }

        if (info.category() == Category::Area || info.category() == Category::EnterEffect) {
            static_cast<EnterEffectObject*>(obj)->m_effectID = val;

            return;
        }

        switch (id) {
            case MOVE_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_targetModCenterID = val;
            break; }
            case ROTATE_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_rotationTargetID = val;
            break; }
            case KEYFRAME_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_animationID = val;
            break; }
            case SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(obj)->m_sfxUniqueID = val;
            break; }
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_targetGroupID = val;
            break; }
            case GRADIENT_TRIGGER: {
                static_cast<GradientTriggerObject*>(obj)->m_gradientID = val;
            break; }
            default: {
                static_cast<EffectGameObject*>(obj)->m_itemID = val;
            break; }
        }

        if (auto layer = editor::layer()) {
            layer->updateObjectLabel(obj);
        }
    }
    int identifier(GameObject* obj) {
        return primaryInput(obj);
    }
    InputType identifierType(GameObject* obj) {
        return primaryInputType(obj);
    }
    void setIdentifier(GameObject* obj, int val) {
        return setPrimaryInput(obj, val);
    }

    int secondaryInput(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryInput().exists()) {
            return 0;
        }
        
        switch (id) {
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_centerGroupID;
            case SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(obj)->m_sfxGroup;
            case AREA_TINT_TRIGGER: return static_cast<EnterEffectObject*>(obj)->m_tintChannelID;
            default: return static_cast<EffectGameObject*>(obj)->m_itemID2;
        }
    }
    InputType secondaryInputType(GameObject* obj) {
        return get(obj).secondaryInput().type();
    }
    void setSecondaryInput(GameObject* obj, int val) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryInput().exists()) {
            return;
        }
        
        switch (id) {
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: {
                static_cast<EffectGameObject*>(obj)->m_centerGroupID = val;
            break; }
            case SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(obj)->m_sfxGroup = val;
            break; }
            case AREA_TINT_TRIGGER: {
                static_cast<EnterEffectObject*>(obj)->m_tintChannelID = val;
            break; }
            default: {
                static_cast<EffectGameObject*>(obj)->m_itemID2 = val;
            break; }
        }

        if (auto layer = editor::layer()) {
            layer->updateObjectLabel(obj);
        }
    }

    bool hasDuration(int id) {
        return get(id).duration();
    }
    bool hasDuration(GameObject* obj) {
        return get(obj).duration();
    }
    float duration(GameObject* obj) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);

        if (!info.duration()) {
            return 0.0f;
        }

        if (info.category() == Category::Shader) {
            auto shader = static_cast<ShaderGameObject*>(obj);

            if (id == SHOCK_WAVE_SHADER_TRIGGER || id == SHOCK_LINE_SHADER_TRIGGER) {
                return shader->m_fadeIn + shader->m_fadeOut;
            }
            else {
                return shader->m_fadeIn;
            }
        }

        if (id == PULSE_TRIGGER) {
            auto trigger = static_cast<EffectGameObject*>(obj);

            return trigger->m_fadeInDuration + trigger->m_holdDuration + trigger->m_fadeOutDuration;
        }

        return static_cast<EffectGameObject*>(obj)->m_duration;
    }  
    void setDuration(GameObject* obj, float duration) {
        const auto id = obj->m_objectID;

        const auto& info = get(id);

        if (!info.duration()) {
            return;
        }

        if (info.category() == Category::Shader || id == PULSE_TRIGGER) {
            return;
        }

        static_cast<EffectGameObject*>(obj)->m_duration = duration;

        if (auto layer = editor::layer()) {
            layer->m_drawGridLayer->m_updateTimeMarkers = true;
        }
    } 
    bool hasEasing(int id) {
        return get(id).easing();
    }
    bool hasEasing(GameObject* obj) {
        return get(obj).easing();
    }
    EasingType easing(GameObject* obj) {
        if (!hasEasing(obj)) {
            return EasingType::None;
        }

        if (get(obj).category() == Category::Area || get(obj).category() == Category::EditArea) {
            return static_cast<EnterEffectObject*>(obj)->m_easingInType;
        }
        else {
            return static_cast<EffectGameObject*>(obj)->m_easingType;
        }
    }
    void setEasing(GameObject* obj, EasingType easing) {
        if (!hasEasing(obj)) {
            return;
        }

        if (get(obj).category() == Category::EditArea) {
            static_cast<EnterEffectObject*>(obj)->m_easingInType = easing;
        }
        else if (get(obj).category() == Category::Area) {
            auto trigger = static_cast<EnterEffectObject*>(obj);

            if (!trigger->m_easeOutEnabled) {
                trigger->m_easingInType = easing;
            }
        }
        else {
            static_cast<EffectGameObject*>(obj)->m_easingType = easing;
        }
    }

    bool hasLabel(int id) {
        return get(id).hasLabel();
    }
    bool hasLabel(GameObject* obj) {
        return get(obj).hasLabel();
    }
    LabelType labelType(int id) {
        return get(id).labelType();
    }
    LabelType labelType(GameObject* obj) {
        return get(obj).labelType();
    }

    Category category(int id) {
        return get(id).category();
    }
    Category category(GameObject* obj) {
        return get(obj).category();
    }

    ccColor3B spriteColor(int id) {
        return get(id).color();
    }
    ccColor3B spriteColor(GameObject* obj) {
        return spriteColor(obj->m_objectID);
    }

    bool activateGroup(GameObject* obj) {
        return is(obj) ? static_cast<EffectGameObject*>(obj)->m_activateGroup : false;
    }
    bool targetModeEnabled(GameObject* obj) {
        switch (obj->m_objectID) {
            case SHOCK_WAVE_SHADER_TRIGGER: [[__fallthrough__]];
            case SHOCK_LINE_SHADER_TRIGGER: [[__fallthrough__]];
            case RADIAL_BLUR_SHADER_TRIGGER: [[__fallthrough__]];
            case BULGE_SHADER_TRIGGER: return static_cast<ShaderGameObject*>(obj)->m_useX;
            case STATIC_CAMERA_TRIGGER: return static_cast<CameraTriggerGameObject*>(obj)->m_followObject;
            case MOVE_TRIGGER: [[__fallthrough__]];
            case ROTATE_TRIGGER: return static_cast<EffectGameObject*>(obj)->m_useMoveTarget || static_cast<EffectGameObject*>(obj)->m_isDirectionFollowSnap360;
            default: return false;
        }
    }
}