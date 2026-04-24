#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::trigger {
    namespace impl {
        std::vector<TriggerInfo> getTriggerInfoVec() {
            std::vector<TriggerInfo> vec;
            vec.resize(nwo5::editor::constants::OBJECT_IDS + 1);
            
            vec[COLOR_TRIGGER] = Info<COLOR_TRIGGER>; 
            vec[MOVE_TRIGGER] = Info<MOVE_TRIGGER>; 
            vec[STOP_TRIGGER] = Info<STOP_TRIGGER>;
            vec[PULSE_TRIGGER] = Info<PULSE_TRIGGER>; 
            vec[ALPHA_TRIGGER] = Info<ALPHA_TRIGGER>; 
            vec[TOGGLE_TRIGGER] = Info<TOGGLE_TRIGGER>;
            vec[SPAWN_TRIGGER] = Info<SPAWN_TRIGGER>; 
            vec[ROTATE_TRIGGER] = Info<ROTATE_TRIGGER>; 
            vec[SCALE_TRIGGER] = Info<SCALE_TRIGGER>;
            vec[FOLLOW_TRIGGER] = Info<FOLLOW_TRIGGER>; 
            vec[SHAKE_TRIGGER] = Info<SHAKE_TRIGGER>; 
            vec[ANIMATION_TRIGGER] = Info<ANIMATION_TRIGGER>;
            vec[KEYFRAME_TRIGGER] = Info<KEYFRAME_TRIGGER>; 
            vec[FOLLOW_PLAYER_Y_TRIGGER] = Info<FOLLOW_PLAYER_Y_TRIGGER>; 
            vec[ADVANCED_FOLLOW_TRIGGER] = Info<ADVANCED_FOLLOW_TRIGGER>;
            vec[EDIT_ADVANCED_FOLLOW_TRIGGER] = Info<EDIT_ADVANCED_FOLLOW_TRIGGER>; 
            vec[RETARGET_ADVANCED_FOLLOW_TRIGGER] = Info<RETARGET_ADVANCED_FOLLOW_TRIGGER>; 
            vec[AREA_MOVE_TRIGGER] = Info<AREA_MOVE_TRIGGER>;
            vec[AREA_ROTATE_TRIGGER] = Info<AREA_ROTATE_TRIGGER>; 
            vec[AREA_SCALE_TRIGGER] = Info<AREA_SCALE_TRIGGER>; 
            vec[AREA_FADE_TRIGGER] = Info<AREA_FADE_TRIGGER>;
            vec[AREA_TINT_TRIGGER] = Info<AREA_TINT_TRIGGER>; 
            vec[EDIT_AREA_MOVE_TRIGGER] = Info<EDIT_AREA_MOVE_TRIGGER>; 
            vec[EDIT_AREA_ROTATE_TRIGGER] = Info<EDIT_AREA_ROTATE_TRIGGER>;
            vec[EDIT_AREA_SCALE_TRIGGER] = Info<EDIT_AREA_SCALE_TRIGGER>; 
            vec[EDIT_AREA_FADE_TRIGGER] = Info<EDIT_AREA_FADE_TRIGGER>; 
            vec[EDIT_AREA_TINT_TRIGGER] = Info<EDIT_AREA_TINT_TRIGGER>;
            vec[AREA_STOP_TRIGGER] = Info<AREA_STOP_TRIGGER>; 
            vec[BG_TRIGGER] = Info<BG_TRIGGER>; 
            vec[GROUND_TRIGGER] = Info<GROUND_TRIGGER>;
            vec[MG_TRIGGER] = Info<MG_TRIGGER>; 
            vec[TOUCH_TRIGGER] = Info<TOUCH_TRIGGER>; 
            vec[COUNT_TRIGGER] = Info<COUNT_TRIGGER>;
            vec[INSTANT_COUNT_TRIGGER] = Info<INSTANT_COUNT_TRIGGER>; 
            vec[PICKUP_TRIGGER] = Info<PICKUP_TRIGGER>; 
            vec[TIME_TRIGGER] = Info<TIME_TRIGGER>;
            vec[TIME_EVENT_TRIGGER] = Info<TIME_EVENT_TRIGGER>; 
            vec[TIME_CONTROL_TRIGGER] = Info<TIME_CONTROL_TRIGGER>; 
            vec[ITEM_EDIT_TRIGGER] = Info<ITEM_EDIT_TRIGGER>;
            vec[ITEM_COMP_TRIGGER] = Info<ITEM_COMP_TRIGGER>; 
            vec[ITEM_PERSIST_TRIGGER] = Info<ITEM_PERSIST_TRIGGER>; 
            vec[RANDOM_TRIGGER] = Info<RANDOM_TRIGGER>;
            vec[ADVANCED_RANDOM_TRIGGER] = Info<ADVANCED_RANDOM_TRIGGER>; 
            vec[SEQUENCE_TRIGGER] = Info<SEQUENCE_TRIGGER>; 
            vec[SPAWN_PARTICLE_TRIGGER] = Info<SPAWN_PARTICLE_TRIGGER>;
            vec[RESET_TRIGGER] = Info<RESET_TRIGGER>; 
            vec[ZOOM_TRIGGER] = Info<ZOOM_TRIGGER>; 
            vec[STATIC_CAMERA_TRIGGER] = Info<STATIC_CAMERA_TRIGGER>;
            vec[OFFSET_CAMERA_TRIGGER] = Info<OFFSET_CAMERA_TRIGGER>; 
            vec[GP_OFFSET_TRIGGER] = Info<GP_OFFSET_TRIGGER>; 
            vec[ROTATE_CAMERA_TRIGGER] = Info<ROTATE_CAMERA_TRIGGER>;
            vec[CAMERA_EDGE_TRIGGER] = Info<CAMERA_EDGE_TRIGGER>;
            vec[CAMERA_MODE_TRIGGER] = Info<CAMERA_MODE_TRIGGER>;
            vec[OLD_REVERSE_TRIGGER] = Info<OLD_REVERSE_TRIGGER>;
            vec[GAMEPLAY_ROTATE_TRIGGER] = Info<GAMEPLAY_ROTATE_TRIGGER>;
            vec[SONG_TRIGGER] = Info<SONG_TRIGGER>;
            vec[EDIT_SONG_TRIGGER] = Info<EDIT_SONG_TRIGGER>;
            vec[SFX_TRIGGER] = Info<SFX_TRIGGER>;
            vec[EDIT_SFX_TRIGGER] = Info<EDIT_SFX_TRIGGER>;
            vec[EVENT_TRIGGER] = Info<EVENT_TRIGGER>;
            vec[TIMEWARP_TRIGGER] = Info<TIMEWARP_TRIGGER>;
            vec[EDIT_MG_TRIGGER] = Info<EDIT_MG_TRIGGER>;
            vec[BG_SPEED_TRIGGER] = Info<BG_SPEED_TRIGGER>;
            vec[MG_SPEED_TRIGGER] = Info<MG_SPEED_TRIGGER>;
            vec[COUNTER_LABEL] = Info<COUNTER_LABEL>;
            vec[UI_TRIGGER] = Info<UI_TRIGGER>;
            vec[LINK_VISIBLE_TRIGGER] = Info<LINK_VISIBLE_TRIGGER>;
            vec[COLLISION_TRIGGER] = Info<COLLISION_TRIGGER>;
            vec[INSTANT_COLLISION_TRIGGER] = Info<INSTANT_COLLISION_TRIGGER>;
            vec[COLLISION_STATE_BLOCK] = Info<COLLISION_STATE_BLOCK>;
            vec[COLLISION_BLOCK] = Info<COLLISION_BLOCK>;
            vec[TOGGLE_BLOCK] = Info<TOGGLE_BLOCK>;
            vec[ON_DEATH_TRIGGER] = Info<ON_DEATH_TRIGGER>;
            vec[DISABLE_TRAIL_TRIGGER] = Info<DISABLE_TRAIL_TRIGGER>;
            vec[ENABLE_TRAIL_TRIGGER] = Info<ENABLE_TRAIL_TRIGGER>;
            vec[SHOW_PLAYER_TRIGGER] = Info<SHOW_PLAYER_TRIGGER>;
            vec[HIDE_PLAYER_TRIGGER] = Info<HIDE_PLAYER_TRIGGER>;
            vec[BG_EFFECT_ON_TRIGGER] = Info<BG_EFFECT_ON_TRIGGER>;
            vec[BG_EFFECT_OFF_TRIGGER] = Info<BG_EFFECT_OFF_TRIGGER>;
            vec[END_TRIGGER] = Info<END_TRIGGER>;
            vec[PLAYER_CONTROL_TRIGGER] = Info<PLAYER_CONTROL_TRIGGER>;
            vec[OPTIONS_TRIGGER] = Info<OPTIONS_TRIGGER>;
            vec[GRADIENT_TRIGGER] = Info<GRADIENT_TRIGGER>;
            vec[GRAVITY_TRIGGER] = Info<GRAVITY_TRIGGER>;
            vec[TELEPORT_TRIGGER] = Info<TELEPORT_TRIGGER>;
            vec[SHADER_TRIGGER] = Info<SHADER_TRIGGER>;
            vec[SHOCK_WAVE_SHADER_TRIGGER] = Info<SHOCK_WAVE_SHADER_TRIGGER>;
            vec[SHOCK_LINE_SHADER_TRIGGER] = Info<SHOCK_LINE_SHADER_TRIGGER>;
            vec[GLITCH_SHADER_TRIGGER] = Info<GLITCH_SHADER_TRIGGER>;
            vec[CHROMATIC_SHADER_TRIGGER] = Info<CHROMATIC_SHADER_TRIGGER>;
            vec[CHROMATIC_GLITCH_SHADER_TRIGGER] = Info<CHROMATIC_GLITCH_SHADER_TRIGGER>;
            vec[PIXELATE_SHADER_TRIGGER] = Info<PIXELATE_SHADER_TRIGGER>;
            vec[LENS_CIRCLE_SHADER_TRIGGER] = Info<LENS_CIRCLE_SHADER_TRIGGER>;
            vec[RADIAL_BLUR_SHADER_TRIGGER] = Info<RADIAL_BLUR_SHADER_TRIGGER>;
            vec[MOTION_BLUR_SHADER_TRIGGER] = Info<MOTION_BLUR_SHADER_TRIGGER>;
            vec[BULGE_SHADER_TRIGGER] = Info<BULGE_SHADER_TRIGGER>;
            vec[PINCH_SHADER_TRIGGER] = Info<PINCH_SHADER_TRIGGER>;
            vec[GRAY_SCALE_SHADER_TRIGGER] = Info<GRAY_SCALE_SHADER_TRIGGER>;
            vec[SEPIA_SHADER_TRIGGER] = Info<SEPIA_SHADER_TRIGGER>;
            vec[INVERT_COLOR_SHADER_TRIGGER] = Info<INVERT_COLOR_SHADER_TRIGGER>;
            vec[HUE_SHADER_TRIGGER] = Info<HUE_SHADER_TRIGGER>;
            vec[EDIT_COLOR_SHADER_TRIGGER] = Info<EDIT_COLOR_SHADER_TRIGGER>;
            vec[SPLIT_SCREEN_SHADER_TRIGGER] = Info<SPLIT_SCREEN_SHADER_TRIGGER>;
            vec[OLD_NO_ENTER_EFFECT_TRIGGER] = Info<OLD_NO_ENTER_EFFECT_TRIGGER>;
            vec[FADE_TOP_ENTER_EFFECT_TRIGGER] = Info<FADE_TOP_ENTER_EFFECT_TRIGGER>;
            vec[FADE_BOTTOM_ENTER_EFFECT_TRIGGER] = Info<FADE_BOTTOM_ENTER_EFFECT_TRIGGER>;
            vec[FADE_LEFT_ENTER_EFFECT_TRIGGER] = Info<FADE_LEFT_ENTER_EFFECT_TRIGGER>;
            vec[FADE_RIGHT_ENTER_EFFECT_TRIGGER] = Info<FADE_RIGHT_ENTER_EFFECT_TRIGGER>;
            vec[SMALL_TO_BIG_ENTER_EFFECT_TRIGGER] = Info<SMALL_TO_BIG_ENTER_EFFECT_TRIGGER>;
            vec[BIG_TO_SMALL_ENTER_EFFECT_TRIGGER] = Info<BIG_TO_SMALL_ENTER_EFFECT_TRIGGER>;
            vec[CHAOTIC_ENTER_EFFECT_TRIGGER] = Info<CHAOTIC_ENTER_EFFECT_TRIGGER>;
            vec[HALVE_LEFT_ENTER_EFFECT_TRIGGER] = Info<HALVE_LEFT_ENTER_EFFECT_TRIGGER>;
            vec[HALVE_RIGHT_ENTER_EFFECT_TRIGGER] = Info<HALVE_RIGHT_ENTER_EFFECT_TRIGGER>;
            vec[HALVE_ENTER_EFFECT_TRIGGER] = Info<HALVE_ENTER_EFFECT_TRIGGER>;
            vec[INVERSE_HALVE_ENTER_EFFECT_TRIGGER] = Info<INVERSE_HALVE_ENTER_EFFECT_TRIGGER>;
            vec[NO_ENTER_EFFECT_TRIGGER] = Info<NO_ENTER_EFFECT_TRIGGER>;
            vec[MOVE_ENTER_TRIGGER] = Info<MOVE_ENTER_TRIGGER>;
            vec[ROTATE_ENTER_TRIGGER] = Info<ROTATE_ENTER_TRIGGER>;
            vec[FADE_ENTER_TRIGGER] = Info<FADE_ENTER_TRIGGER>;
            vec[TINT_ENTER_TRIGGER] = Info<TINT_ENTER_TRIGGER>;
            vec[ENTER_STOP_TRIGGER] = Info<ENTER_STOP_TRIGGER>;

            return vec;
        }
    }

    bool is(int pID) {
        return get(pID).isTrigger();
    }
    bool is(GameObject* pObj) {
        return get(pObj).isTrigger();
    }

    const TriggerInfo& get(int pID) {
        static auto vec = impl::getTriggerInfoVec();
        
        if (pID < COLOR_TRIGGER || pID > constants::OBJECT_IDS) {
            return vec.front();
        }

        return vec[pID];
    }
    const TriggerInfo& get(GameObject* pObj) {
        return get(pObj->m_objectID);
    }

    int primaryTarget(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryTarget().exists()) {
            return 0;
        }

        if (info.category() == Category::EnterEffect || info.category() == Category::AdvancedEnter || id == ENTER_STOP_TRIGGER) {
            return static_cast<EnterEffectObject*>(pObj)->m_enterChannel;
        }

        switch (id) {
            case COLOR_TRIGGER: return pObj->m_targetColor;
            case PICKUP_TRIGGER: [[__fallthrough__]]; // fuck you compile with clang specifically cuz i think this looks a lil cooler :3
            case TIME_CONTROL_TRIGGER: [[__fallthrough__]];
            case ITEM_PERSIST_TRIGGER: [[__fallthrough__]];
            case COLLISION_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_itemID;
            case STATIC_CAMERA_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_centerGroupID;
            case GAMEPLAY_ROTATE_TRIGGER: return static_cast<RotateGameplayGameObject*>(pObj)->m_targetChannelID;
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case SONG_TRIGGER: return static_cast<SongTriggerGameObject*>(pObj)->m_songChannel;
            case EDIT_SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(pObj)->m_sfxUniqueID;
            default: return static_cast<EffectGameObject*>(pObj)->m_targetGroupID;
        }
    }
    InputType primaryTargetType(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);

        if (!info.primaryTarget().exists()) {
            return InputType::None;
        }
        
        if (!info.primaryTarget().mixed() && !info.primaryTarget().conditional()) {
            return info.primaryTarget().type();
        }

        if (info.category() == Category::EditArea) {
            return static_cast<EnterEffectObject*>(pObj)->m_useEffectID ? InputType::Effect : InputType::Group;
        }

        switch (id) {
            case EDIT_ADVANCED_FOLLOW_TRIGGER: [[__fallthrough__]];
            case RETARGET_ADVANCED_FOLLOW_TRIGGER: [[__fallthrough__]];
            case STOP_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_targetControlID ? InputType::Control : InputType::Group;
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_pulseTargetType == 1 ? InputType::Group : InputType::Color;
            case GAMEPLAY_ROTATE_TRIGGER: return static_cast<RotateGameplayGameObject*>(pObj)->m_changeChannel ? InputType::Channel : InputType::None;
            case SHOCK_WAVE_SHADER_TRIGGER: [[__fallthrough__]];
            case SHOCK_LINE_SHADER_TRIGGER: [[__fallthrough__]];
            case RADIAL_BLUR_SHADER_TRIGGER: [[__fallthrough__]];
            case BULGE_SHADER_TRIGGER: return targetModeEnabled(pObj) ? InputType::Group : InputType::None;
            default: return InputType::None;
        }

    }
    void setPrimaryTarget(GameObject* pObj, int pVal) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryTarget().exists() ||info.primaryTarget().type() == InputType::GroupArray) {
            return;
        }

        if (info.category() == Category::EnterEffect || info.category() == Category::AdvancedEnter || id == ENTER_STOP_TRIGGER) {
            static_cast<EnterEffectObject*>(pObj)->m_enterChannel = pVal;

            return;
        }

        switch (id) {
            case COLOR_TRIGGER: {
                pObj->m_targetColor = pVal;
            break; }
            case PICKUP_TRIGGER: [[__fallthrough__]];
            case TIME_CONTROL_TRIGGER: [[__fallthrough__]];
            case ITEM_PERSIST_TRIGGER: [[__fallthrough__]];
            case COLLISION_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_itemID = pVal;
            break; }
            case STATIC_CAMERA_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_centerGroupID = pVal;
            break; }
            case GAMEPLAY_ROTATE_TRIGGER: {
                static_cast<RotateGameplayGameObject*>(pObj)->m_targetChannelID = pVal;
            break; }
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case SONG_TRIGGER: {
                static_cast<SongTriggerGameObject*>(pObj)->m_songChannel = pVal;
            break; }
            case EDIT_SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(pObj)->m_sfxUniqueID = pVal;
            break; }
            default: {
                static_cast<EffectGameObject*>(pObj)->m_targetGroupID = pVal;
            break;}
        }
    }
    int target(GameObject* pObj) {
        return primaryTarget(pObj);
    }
    InputType targetType(GameObject* pObj) {
        return primaryTargetType(pObj);
    }
    void setTarget(GameObject* pObj, int pVal) {
        return setPrimaryTarget(pObj, pVal);
    }

    int secondaryTarget(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryTarget().exists() || id == SPAWN_TRIGGER) {
            return 0;
        }

        switch (id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_copyColorID;
            case MOVE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_targetModCenterID;
            case ANIMATION_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_animationID;
            case COUNT_TRIGGER: [[__fallthrough__]];
            case INSTANT_COUNT_TRIGGER: [[__fallthrough__]];
            case TIME_TRIGGER: [[__fallthrough__]];
            case TIME_EVENT_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_itemID;
            case EDIT_SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(pObj)->m_sfxGroup;
            case AREA_STOP_TRIGGER: return static_cast<EnterEffectObject*>(pObj)->m_effectID;
            default: return static_cast<EffectGameObject*>(pObj)->m_centerGroupID;
        }
    }
    InputType secondaryTargetType(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);

        if (!info.secondaryTarget().exists()) {
            return InputType::None;
        }
        
        if (!info.secondaryTarget().mixed() && !info.secondaryTarget().conditional()) {
            return info.secondaryTarget().type();
        }

        switch(id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_copyColorID ? InputType::Color : InputType::None;
            case MOVE_TRIGGER: return targetModeEnabled(pObj) ? InputType::Group : InputType::None;
            default: return InputType::None;
        }
    }
    void setSecondaryTarget(GameObject* pObj, int pVal) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryTarget().exists() || id == SPAWN_TRIGGER) {
            return;
        }

        switch (id) {
            case COLOR_TRIGGER: [[__fallthrough__]];
            case PULSE_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_copyColorID = pVal;
            break; }
            case MOVE_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_targetModCenterID = pVal;
            break; }
            case ANIMATION_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_animationID = pVal;
            break; }
            case COUNT_TRIGGER: [[__fallthrough__]];
            case INSTANT_COUNT_TRIGGER: [[__fallthrough__]];
            case TIME_TRIGGER: [[__fallthrough__]];
            case TIME_EVENT_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_itemID = pVal;
            break; }
            case EDIT_SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(pObj)->m_sfxGroup = pVal;
            break; }
            case AREA_STOP_TRIGGER: {
                static_cast<EnterEffectObject*>(pObj)->m_effectID = pVal;
            break; }
            default: {
                static_cast<EffectGameObject*>(pObj)->m_centerGroupID = pVal;
            break; }
        }
    }
    int center(GameObject* pObj) {
        return secondaryTarget(pObj);
    }
    InputType centerType(GameObject* pObj) {
        return secondaryTargetType(pObj);
    }
    void setCenter(GameObject* pObj, int pVal) {
        return setSecondaryTarget(pObj, pVal);
    }

    int primaryInput(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryInput().exists()) {
            return 0;
        }

        if (info.category() == Category::Area || info.category() == Category::EnterEffect) {
            return static_cast<EnterEffectObject*>(pObj)->m_effectID;
        }

        switch (id) {
            case MOVE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_targetModCenterID;
            case ROTATE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_rotationTargetID;
            case KEYFRAME_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_animationID;
            case SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(pObj)->m_sfxUniqueID;
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_targetGroupID;
            case GRADIENT_TRIGGER: return static_cast<GradientTriggerObject*>(pObj)->m_gradientID;
            default: return static_cast<EffectGameObject*>(pObj)->m_itemID;
        }
    }
    InputType primaryInputType(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);

        if (!info.primaryInput().exists()) {
            return InputType::None;
        }
        
        if (id == MOVE_TRIGGER || id == ROTATE_TRIGGER) {
            return targetModeEnabled(pObj) ? InputType::Group : InputType::None;
        }

        return info.secondaryTarget().type();
    }
    void setPrimaryInput(GameObject* pObj, int pVal) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.primaryInput().exists()) {
            return;
        }

        if (info.category() == Category::Area || info.category() == Category::EnterEffect) {
            static_cast<EnterEffectObject*>(pObj)->m_effectID = pVal;

            return;
        }

        switch (id) {
            case MOVE_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_targetModCenterID = pVal;
            break; }
            case ROTATE_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_rotationTargetID = pVal;
            break; }
            case KEYFRAME_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_animationID = pVal;
            break; }
            case SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(pObj)->m_sfxUniqueID = pVal;
            break; }
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_targetGroupID = pVal;
            break; }
            case GRADIENT_TRIGGER: {
                static_cast<GradientTriggerObject*>(pObj)->m_gradientID = pVal;
            break; }
            default: {
                static_cast<EffectGameObject*>(pObj)->m_itemID = pVal;
            break; }
        }
    }
    int identifier(GameObject* pObj) {
        return primaryInput(pObj);
    }
    InputType identifierType(GameObject* pObj) {
        return primaryInputType(pObj);
    }
    void setIdentifier(GameObject* pObj, int pVal) {
        return setPrimaryInput(pObj, pVal);
    }

    int secondaryInput(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryInput().exists()) {
            return 0;
        }
        
        switch (id) {
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_centerGroupID;
            case SFX_TRIGGER: return static_cast<SFXTriggerGameObject*>(pObj)->m_sfxGroup;
            case AREA_TINT_TRIGGER: return static_cast<EnterEffectObject*>(pObj)->m_tintChannelID;
            default: return static_cast<EffectGameObject*>(pObj)->m_itemID2;
        }
    }
    InputType secondaryInputType(GameObject* pObj) {
        return get(pObj).secondaryInput().type();
    }
    void setSecondaryInput(GameObject* pObj, int pVal) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);
        
        if (!info.secondaryInput().exists()) {
            return;
        }
        
        switch (id) {
            case EDIT_SONG_TRIGGER: [[__fallthrough__]];
            case EDIT_SFX_TRIGGER: {
                static_cast<EffectGameObject*>(pObj)->m_centerGroupID = pVal;
            break; }
            case SFX_TRIGGER: {
                static_cast<SFXTriggerGameObject*>(pObj)->m_sfxGroup = pVal;
            break; }
            case AREA_TINT_TRIGGER: {
                static_cast<EnterEffectObject*>(pObj)->m_tintChannelID = pVal;
            break; }
            default: {
                static_cast<EffectGameObject*>(pObj)->m_itemID2 = pVal;
            break; }
        }
    }

    bool hasDuration(int pID) {
        return get(pID).duration();
    }
    bool hasDuration(GameObject* pObj) {
        return get(pObj).duration();
    }
    float duration(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);

        if (!info.duration()) {
            return 0.0f;
        }

        if (info.category() == Category::Shader) {
            auto shader = static_cast<ShaderGameObject*>(pObj);

            if (id == SHOCK_WAVE_SHADER_TRIGGER || id == SHOCK_LINE_SHADER_TRIGGER) {
                return shader->m_fadeIn + shader->m_fadeOut;
            }
            else {
                return shader->m_fadeIn;
            }
        }

        if (id == PULSE_TRIGGER) {
            auto trigger = static_cast<EffectGameObject*>(pObj);

            return trigger->m_fadeInDuration + trigger->m_holdDuration + trigger->m_fadeOutDuration;
        }

        return static_cast<EffectGameObject*>(pObj)->m_duration;
    }  
    void setDuration(GameObject* pObj, float pDuration) {
        const auto id = pObj->m_objectID;

        const auto& info = get(id);

        if (!info.duration()) {
            return;
        }

        if (info.category() == Category::Shader || id == PULSE_TRIGGER) {
            return;
        }

        static_cast<EffectGameObject*>(pObj)->m_duration = pDuration;

        layer()->m_drawGridLayer->m_updateTimeMarkers = true;
    } 
    bool hasEasing(int pID) {
        return get(pID).easing();
    }
    bool hasEasing(GameObject* pObj) {
        return get(pObj).easing();
    }
    EasingType easing(GameObject* pObj) {
        if (!hasEasing(pObj)) {
            return EasingType::None;
        }

        if (get(pObj).category() == Category::Area || get(pObj).category() == Category::EditArea) {
            return static_cast<EnterEffectObject*>(pObj)->m_easingInType;
        }
        else {
            return static_cast<EffectGameObject*>(pObj)->m_easingType;
        }
    }
    void setEasing(GameObject* pObj, EasingType pEasing) {
        if (!hasEasing(pObj)) {
            return;
        }

        if (get(pObj).category() == Category::EditArea) {
            static_cast<EnterEffectObject*>(pObj)->m_easingInType = pEasing;
        }
        else if (get(pObj).category() == Category::Area) {
            auto trigger = static_cast<EnterEffectObject*>(pObj);

            if (!trigger->m_easeOutEnabled) {
                trigger->m_easingInType = pEasing;
            }
        }
        else {
            static_cast<EffectGameObject*>(pObj)->m_easingType = pEasing;
        }
    }

    bool hasLabel(int pID) {
        return get(pID).hasLabel();
    }
    bool hasLabel(GameObject* pObj) {
        return get(pObj).hasLabel();
    }
    LabelType labelType(int pID) {
        return get(pID).labelType();
    }
    LabelType labelType(GameObject* pObj) {
        return get(pObj).labelType();
    }

    Category category(int pID) {
        return get(pID).category();
    }
    Category category(GameObject* pObj) {
        return get(pObj).category();
    }

    ccColor3B color(int pID) {
        return get(pID).color();
    }
    ccColor3B color(GameObject* pObj) {
        const auto id = pObj->m_objectID;

        if (id == COLOR_TRIGGER || id == PULSE_TRIGGER) {
            return static_cast<EffectGameObject*>(pObj)->m_triggerTargetColor;
        }
        else {
            return color(id);
        }
    }

    bool activateGroup(GameObject* pObj) {
        return pObj->m_isActivated;
    }
    bool targetModeEnabled(GameObject* pObj) {
        switch (pObj->m_objectID) {
            case SHOCK_WAVE_SHADER_TRIGGER: [[__fallthrough__]];
            case SHOCK_LINE_SHADER_TRIGGER: [[__fallthrough__]];
            case RADIAL_BLUR_SHADER_TRIGGER: [[__fallthrough__]];
            case BULGE_SHADER_TRIGGER: return static_cast<ShaderGameObject*>(pObj)->m_useX;
            case MOVE_TRIGGER: [[__fallthrough__]];
            case ROTATE_TRIGGER: return static_cast<EffectGameObject*>(pObj)->m_useMoveTarget || static_cast<EffectGameObject*>(pObj)->m_isDirectionFollowSnap360;
            default: return false;
        }
    }
}