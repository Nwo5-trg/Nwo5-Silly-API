#include <editor/include.hpp>

using namespace geode::prelude;

namespace nwo5::editor::trigger {
    bool is(int pID) {
        return get(pID).isTrigger();
    }
    bool is(GameObject* pObj) {
        return get(pObj).isTrigger();
    }
    ObjectType type(int pID) {
        return get(pID).type();
    }
    ObjectType type(GameObject* pObj) {
        return get(pObj).type();
    }

    const TriggerInfo& get(int pID) {
        static auto arr = impl::createTriggerInfoArray();
        
        if (pID < COLOR_TRIGGER || pID > constants::OBJECT_IDS) {
            return arr.front();
        }

        return arr[pID];
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

        return info.primaryInput().type();
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