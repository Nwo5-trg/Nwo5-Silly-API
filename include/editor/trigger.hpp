#pragma once

#include "editor.hpp"

namespace nwo5::editor::trigger {
    enum class LabelType {
        None,
        Target,
        TargetCenter,
        Item,
        Collision,
        Other
    };

    enum class Category {
        Other,
        Area,
        EditArea,
        Camera,
        Shader,
        EnterEffect,
        AdvancedEnter
    };

    enum class InputType {
        Group,
        Color,
        Control,
        Animation,
        Item,
        GroupArray,
        Collision,
        Effect,
        Channel,
        EnterChannel,
        SongChannel,
        SFX,
        SFXUnique,
        Gradient,
        Mixed,
        None
    };

    class Input final {
    private:
        bool m_conditional = false;
        InputType m_type = InputType::None;
        InputType m_secondaryType = InputType::None;

    public:
        constexpr Input()
            = default;
        constexpr Input(InputType pType)
            : m_type(pType) {}
        constexpr Input(InputType pType, InputType pSecondaryType)
            : m_type(pType), m_secondaryType(pSecondaryType) {}
        constexpr Input(InputType pType, bool pConditional)
            : m_type(pType), m_conditional(pConditional) {}

        InputType type() const {
            return m_type;
        }
        InputType secondaryType() const {
            return m_secondaryType;
        }
        bool exists() const {
            return m_type != InputType::None;
        }
        bool mixed() const {
            return m_secondaryType != InputType::None;
        }
        bool conditional() const {
            return m_conditional;
        }
     };

    class TriggerInfo final {
    private:
        bool m_isTrigger = false;

        Input m_primaryTarget{};
        Input m_secondaryTarget{};
        Input m_primaryInput{};
        Input m_secondaryInput{};

        bool m_duration = false;
        bool m_easing = false;
        LabelType m_labelType = LabelType::None;

        cocos2d::ccColor3B m_color{};
        Category m_category = Category::Other;
    
    public:

        constexpr TriggerInfo() 
            = default;
        constexpr TriggerInfo(
            Input pPrimaryTarget,
            Input pSecondaryTarget,
            Input pPrimaryInput,
            Input pSecondaryInput,
            bool pDuration,
            bool pEasing,
            LabelType pLabelType,
            cocos2d::ccColor3B pColor,
            Category pCategory
        )
            : m_isTrigger(true),
              m_primaryTarget(pPrimaryTarget), m_secondaryTarget(pSecondaryTarget),
              m_primaryInput(pPrimaryInput), m_secondaryInput(pSecondaryInput),
              m_duration(pDuration), m_easing(pEasing), m_labelType(pLabelType),
              m_color(pColor), m_category(pCategory) {}

        bool isTrigger() const {
            return m_isTrigger;
        }

        /// e.g. toggle trigger target, move trigger target, color trigger target, sfx trigger gid 1, *edit* sfx trigger unique id, counter label item id, gray scale shader reference color channel
        const Input& primaryTarget() const {
            return m_primaryTarget;
        }
        /// same as primary target
        const Input& target() const {
            return m_primaryTarget;
        }
        /// e.g. rotate trigger center, random trigger gid 2, collision state off, counter trigger item id, timer trigger item id, lens circle shader refernce color channel
        const Input& secondaryTarget() const {
            return m_secondaryTarget;
        }
        /// same as secondary target
        const Input& center() const {
            return m_secondaryTarget;
        }
        /// e.g. item edit item 1 move trigger target pos gid, area trigger effect id, sfx trigger unique id, *edit* sfx trigger gid 1
        const Input& primaryInput() const {
            return m_primaryInput;
        }
        /// same as primary input
        const Input& identifer() const {
            return m_primaryInput;
        }
        /// e.g. collision trigger block b, item edit item 2, tint rea trigger reference channel
        const Input& secondaryInput() const {
            return m_secondaryInput;
        }

        bool duration() const {
            return m_duration;
        }
        bool easing() const {
            return m_easing;
        }
        bool hasLabel() const {
            return m_labelType != LabelType::None;
        }
        LabelType labelType() const {
            return m_labelType;
        }

        cocos2d::ccColor3B color() const {
            return m_color;
        }
        bool categorized() const {
            return m_category != Category::Other;
        }
        Category category() const {
            return m_category;
        }
    };

    namespace impl {
        template<int ID>
        struct Trigger {
            static constexpr TriggerInfo info{};
            using Type = EffectGameObject;
        };
    }

    template<int ID>
    constexpr auto Info = impl::Trigger<ID>::info;
    template<int ID>
    using Type = impl::Trigger<ID>::TriggerType;
}

// making this collapsable
namespace nwo5::editor::trigger {
    constexpr int COLOR_TRIGGER = 899;
    template<> struct impl::Trigger<COLOR_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Color, {InputType::Color, true}, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "target is m_targetColor";
    };
    constexpr int MOVE_TRIGGER = 901;
    template<> struct impl::Trigger<MOVE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, {InputType::Group, true}, {InputType::Group, true}, InputType::None, 
            true, true, LabelType::Target,
            {255, 0, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "center gid is m_targetModCenterID, targetpos gid is center";
    };
    constexpr int STOP_TRIGGER = 1616;
    template<> struct impl::Trigger<STOP_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Control}, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {163, 0, 86}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int PULSE_TRIGGER = 1006;
    template<> struct impl::Trigger<PULSE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Color, InputType::Group}, {InputType::Color, true}, InputType::None, InputType::None, 
            true, false, LabelType::Target,
            {255, 255, 0}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "always uses target group regardless of mode, duration uses 3 members in EffectGameObject";
    };
    constexpr int ALPHA_TRIGGER = 1007;
    template<> struct impl::Trigger<ALPHA_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::Target,
            {0, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int TOGGLE_TRIGGER = 1049;
    template<> struct impl::Trigger<TOGGLE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {255, 63, 63}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "color can change based on toggle";
    };
    constexpr int SPAWN_TRIGGER = 1268;
    template<> struct impl::Trigger<SPAWN_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, {InputType::GroupArray, true}, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {35, 204, 127}, Category::Other
        };
        using TriggerType = SpawnTriggerGameObject;
    };
    constexpr int ROTATE_TRIGGER = 1346;
    template<> struct impl::Trigger<ROTATE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, {InputType::Group, true}, InputType::None, 
            true, true, LabelType::Target,
            {127, 127, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int SCALE_TRIGGER = 2067;
    template<> struct impl::Trigger<SCALE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            true, true, LabelType::Target,
            {63, 191, 255}, Category::Other
        };
        using TriggerType = TransformTriggerGameObject;
    };
    constexpr int FOLLOW_TRIGGER = 1347;
    template<> struct impl::Trigger<FOLLOW_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {255, 127, 127}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int SHAKE_TRIGGER = 1520;
    template<> struct impl::Trigger<SHAKE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ANIMATION_TRIGGER = 1585;
    template<> struct impl::Trigger<ANIMATION_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Animation, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {255, 183, 0}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "animation id is m_animationID";
    };
    constexpr int KEYFRAME_TRIGGER = 3033;
    template<> struct impl::Trigger<KEYFRAME_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Animation, InputType::None, 
            false, false, LabelType::Target,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = KeyframeAnimTriggerObject;
        static constexpr auto note = "parent gid is center, animation group is m_animationID";
    };
    constexpr int FOLLOW_PLAYER_Y_TRIGGER = 1814;
    template<> struct impl::Trigger<FOLLOW_PLAYER_Y_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::Target,
            {255, 255, 127}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ADVANCED_FOLLOW_TRIGGER = 3016;
    template<> struct impl::Trigger<ADVANCED_FOLLOW_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {204, 255, 199}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "follow gid is center";
    };
    constexpr int EDIT_ADVANCED_FOLLOW_TRIGGER = 3660;
    template<> struct impl::Trigger<EDIT_ADVANCED_FOLLOW_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Control}, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {204, 255, 199}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int RETARGET_ADVANCED_FOLLOW_TRIGGER = 3661;
    template<> struct impl::Trigger<RETARGET_ADVANCED_FOLLOW_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Control}, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {204, 255, 199}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "follow gid is center";
    };
    constexpr int AREA_MOVE_TRIGGER = 3006;
    template<> struct impl::Trigger<AREA_MOVE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {255, 0, 255}, Category::Area
        };
        using TriggerType = EnterEffectObject;
        static constexpr auto note = "easing has 2 types stored in EnterEffectObject, effect id is m_effectID";
    };
    constexpr int AREA_ROTATE_TRIGGER = 3007;
    template<> struct impl::Trigger<AREA_ROTATE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {127, 127, 255}, Category::Area
        };
        using TriggerType = EnterEffectObject;
        static constexpr auto note = "easing has 2 types stored in EnterEffectObject, effect id is m_effectID";
    };
    constexpr int AREA_SCALE_TRIGGER = 3008;
    template<> struct impl::Trigger<AREA_SCALE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {63, 191, 255}, Category::Area
        };
        using TriggerType = EnterEffectObject;
        static constexpr auto note = "easing has 2 types stored in EnterEffectObject, effect id is m_effectID";
    };
    constexpr int AREA_FADE_TRIGGER = 3009;
    template<> struct impl::Trigger<AREA_FADE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {0, 255, 255}, Category::Area
        };
        using TriggerType = EnterEffectObject;
        static constexpr auto note = "easing has 2 types stored in EnterEffectObject, effect id is m_effectID";
    };
    constexpr int AREA_TINT_TRIGGER = 3010;
    template<> struct impl::Trigger<AREA_TINT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Effect, InputType::Color, 
            false, true, LabelType::None,
            {255, 255, 0}, Category::Area
        };
        using TriggerType = EnterEffectObject;
        static constexpr auto note = "easing has 2 types stored in EnterEffectObject, effect id is m_effectID, color reference channel is m_tintChannelID";
    };
    constexpr int EDIT_AREA_MOVE_TRIGGER = 3011;
    template<> struct impl::Trigger<EDIT_AREA_MOVE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Effect}, InputType::None, InputType::None, InputType::None, 
            false, true, LabelType::None,
            {255, 0, 255}, Category::EditArea
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int EDIT_AREA_ROTATE_TRIGGER = 3012;
    template<> struct impl::Trigger<EDIT_AREA_ROTATE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Effect}, InputType::None, InputType::None, InputType::None, 
            false, true, LabelType::None,
            {127, 127, 255}, Category::EditArea
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int EDIT_AREA_SCALE_TRIGGER = 3013;
    template<> struct impl::Trigger<EDIT_AREA_SCALE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Effect}, InputType::None, InputType::None, InputType::None, 
            false, true, LabelType::None,
            {63, 191, 255}, Category::EditArea
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int EDIT_AREA_FADE_TRIGGER = 3014;
    template<> struct impl::Trigger<EDIT_AREA_FADE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Effect}, InputType::None, InputType::None, InputType::None, 
            false, true, LabelType::None,
            {0, 255, 255}, Category::EditArea
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int EDIT_AREA_TINT_TRIGGER = 3015;
    template<> struct impl::Trigger<EDIT_AREA_TINT_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, InputType::Effect}, InputType::None, InputType::None, InputType::None, 
            false, true, LabelType::None,
            {255, 255, 0}, Category::EditArea
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int AREA_STOP_TRIGGER = 3024;
    template<> struct impl::Trigger<AREA_STOP_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Effect, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "effect id is target";
    };
    constexpr int BG_TRIGGER = 3029;
    template<> struct impl::Trigger<BG_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = ArtTriggerGameObject;
    };
    constexpr int GROUND_TRIGGER = 3030;
    template<> struct impl::Trigger<GROUND_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = ArtTriggerGameObject;
    };
    constexpr int MG_TRIGGER = 3031;
    template<> struct impl::Trigger<MG_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = ArtTriggerGameObject;
    };
    constexpr int TOUCH_TRIGGER = 1595;
    template<> struct impl::Trigger<TOUCH_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {0, 136, 178}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int COUNT_TRIGGER = 1611;
    template<> struct impl::Trigger<COUNT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Item, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {255, 182, 255}, Category::Other
        };
        using TriggerType = CountTriggerGameObject;
    };
    constexpr int INSTANT_COUNT_TRIGGER = 1811;
    template<> struct impl::Trigger<INSTANT_COUNT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Item, InputType::None, InputType::None, 
            false, false, LabelType::Item,
            {255, 127, 255}, Category::Other
        };
        using TriggerType = CountTriggerGameObject;
    };
    constexpr int PICKUP_TRIGGER = 1817;
    template<> struct impl::Trigger<PICKUP_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Item, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Item,
            {255, 108, 0}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int TIME_TRIGGER = 3614;
    template<> struct impl::Trigger<TIME_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Item, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = TimerTriggerGameObject;
    };
    constexpr int TIME_EVENT_TRIGGER = 3615;
    template<> struct impl::Trigger<TIME_EVENT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Item, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {0, 255, 255}, Category::Other
        };
        using TriggerType = TimerTriggerGameObject;
    };
    constexpr int TIME_CONTROL_TRIGGER = 3617;
    template<> struct impl::Trigger<TIME_CONTROL_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Item, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 0}, Category::Other
        };
        using TriggerType = TimerTriggerGameObject;
    };
    constexpr int ITEM_EDIT_TRIGGER = 3619;
    template<> struct impl::Trigger<ITEM_EDIT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Item, InputType::None, InputType::Item, InputType::Item, 
            false, false, LabelType::None,
            {0, 255, 255}, Category::Other
        };
        using TriggerType = ItemTriggerGameObject;
        static constexpr auto note = "target item id is target";
    };
    constexpr int ITEM_COMP_TRIGGER = 3620;
    template<> struct impl::Trigger<ITEM_COMP_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Item, InputType::Item, 
            false, false, LabelType::None,
            {255, 255, 0}, Category::Other
        };
        using TriggerType = ItemTriggerGameObject;
        static constexpr auto note = "true gid is target, false gid is center";
    };
    constexpr int ITEM_PERSIST_TRIGGER = 3641;
    template<> struct impl::Trigger<ITEM_PERSIST_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Item, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int RANDOM_TRIGGER = 1912;
    template<> struct impl::Trigger<RANDOM_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::TargetCenter,
            {63, 127, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "chance is m_duration (\?\?\?)";
    };
    constexpr int ADVANCED_RANDOM_TRIGGER = 2068;
    template<> struct impl::Trigger<ADVANCED_RANDOM_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::GroupArray, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {165, 93, 255}, Category::Other
        };
        using TriggerType = RandTriggerGameObject;
    };
    constexpr int SEQUENCE_TRIGGER = 3607;
    template<> struct impl::Trigger<SEQUENCE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::GroupArray, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {165, 93, 255}, Category::Other
        };
        using TriggerType = SequenceTriggerGameObject;
    };
    constexpr int SPAWN_PARTICLE_TRIGGER = 3608;
    template<> struct impl::Trigger<SPAWN_PARTICLE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {149, 149, 149}, Category::Other
        };
        using TriggerType = SpawnParticleGameObject;
        static constexpr auto note = "particle group is target, position group is center";
    };
    constexpr int RESET_TRIGGER = 3618;
    template<> struct impl::Trigger<RESET_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 100, 0}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ZOOM_TRIGGER = 1913;
    template<> struct impl::Trigger<ZOOM_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {127, 127, 255}, Category::Camera
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int STATIC_CAMERA_TRIGGER = 1914;
    template<> struct impl::Trigger<STATIC_CAMERA_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 127, 127}, Category::Camera
        };
        using TriggerType = CameraTriggerGameObject;
        static constexpr auto note = "target id is center (\?\?\?)";
    };
    constexpr int OFFSET_CAMERA_TRIGGER = 1916;
    template<> struct impl::Trigger<OFFSET_CAMERA_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Camera // todo
        };
        using TriggerType = CameraTriggerGameObject;
    };
    constexpr int GP_OFFSET_TRIGGER = 2901;
    template<> struct impl::Trigger<GP_OFFSET_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Camera // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ROTATE_CAMERA_TRIGGER = 2015;
    template<> struct impl::Trigger<ROTATE_CAMERA_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 0}, Category::Camera
        };
        using TriggerType = CameraTriggerGameObject;
    };
    constexpr int CAMERA_EDGE_TRIGGER = 2062;
    template<> struct impl::Trigger<CAMERA_EDGE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {63, 191, 255}, Category::Camera
        };
        using TriggerType = CameraTriggerGameObject;
    };
    constexpr int CAMERA_MODE_TRIGGER = 2925;
    template<> struct impl::Trigger<CAMERA_MODE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Camera // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int OLD_REVERSE_TRIGGER = 1917;
    template<> struct impl::Trigger<OLD_REVERSE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int GAMEPLAY_ROTATE_TRIGGER = 2900;
    template<> struct impl::Trigger<GAMEPLAY_ROTATE_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Channel, true}, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = RotateGameplayGameObject;
    };
    constexpr int SONG_TRIGGER = 1934;
    template<> struct impl::Trigger<SONG_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::SongChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = SongTriggerGameObject;
    };
    constexpr int EDIT_SONG_TRIGGER = 3605;
    template<> struct impl::Trigger<EDIT_SONG_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::SongChannel, InputType::None, InputType::Group, InputType::Group, 
            true, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = SongTriggerGameObject;
        static constexpr auto note = "gid 1 is target, gid 2 is center";
    };
    constexpr int SFX_TRIGGER = 3602;
    template<> struct impl::Trigger<SFX_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::SFXUnique, InputType::SFX, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = SFXTriggerGameObject;
        static constexpr auto note = "gid 1 is target, gid 2 is center, unique id and sfxgroup are in SFXTriggerGameObject";
    };
    constexpr int EDIT_SFX_TRIGGER = 3603;
    template<> struct impl::Trigger<EDIT_SFX_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::SFXUnique, InputType::SFX, InputType::Group, InputType::Group, 
            true, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = SFXTriggerGameObject;
        static constexpr auto note = "gid 1 is target, gid 2 is center, unique id, group id, and sfxgroup are in SFXTriggerGameObject";
    };
    constexpr int EVENT_TRIGGER = 3604;
    template<> struct impl::Trigger<EVENT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EventLinkTrigger;
    };
    constexpr int TIMEWARP_TRIGGER = 1935;
    template<> struct impl::Trigger<TIMEWARP_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::None,
            {153, 128, 153}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int EDIT_MG_TRIGGER = 2999;
    template<> struct impl::Trigger<EDIT_MG_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 128, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int BG_SPEED_TRIGGER = 3606;
    template<> struct impl::Trigger<BG_SPEED_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {128, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int MG_SPEED_TRIGGER = 3612;
    template<> struct impl::Trigger<MG_SPEED_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 128, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int COUNTER_LABEL = 1615;
    template<> struct impl::Trigger<COUNTER_LABEL> {
        static constexpr TriggerInfo info{
            InputType::Item, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Item,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int UI_TRIGGER = 3613;
    template<> struct impl::Trigger<UI_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = UISettingsGameObject;
        static constexpr auto note = "gid is target, ui target is center";
    };
    constexpr int LINK_VISIBLE_TRIGGER = 3662;
    template<> struct impl::Trigger<LINK_VISIBLE_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int COLLISION_TRIGGER = 1815;
    template<> struct impl::Trigger<COLLISION_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::Collision, InputType::Collision, 
            false, false, LabelType::Target,
            {83, 66, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "block a is itemid, lock b is itemid2";
    };
    constexpr int INSTANT_COLLISION_TRIGGER = 3609;
    template<> struct impl::Trigger<INSTANT_COLLISION_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::Collision, InputType::Collision, 
            false, false, LabelType::Target,
            {83, 191, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "block a is itemid, lock b is itemid2, true gid is target, false gid is center";
    };
    constexpr int COLLISION_STATE_BLOCK = 3640;
    template<> struct impl::Trigger<COLLISION_STATE_BLOCK> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::TargetCenter,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int COLLISION_BLOCK = 1816;
    template<> struct impl::Trigger<COLLISION_BLOCK> {
        static constexpr TriggerInfo info{
            InputType::Collision, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Collision,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
        static constexpr auto note = "block id is itemid";
    };
    constexpr int TOGGLE_BLOCK = 3643;
    template<> struct impl::Trigger<TOGGLE_BLOCK> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ON_DEATH_TRIGGER = 1812;
    template<> struct impl::Trigger<ON_DEATH_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::Target,
            {204, 101, 101}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int DISABLE_TRAIL_TRIGGER = 33;
    template<> struct impl::Trigger<DISABLE_TRAIL_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ENABLE_TRAIL_TRIGGER = 32;
    template<> struct impl::Trigger<ENABLE_TRAIL_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int SHOW_PLAYER_TRIGGER = 1613;
    template<> struct impl::Trigger<SHOW_PLAYER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int HIDE_PLAYER_TRIGGER = 1612;
    template<> struct impl::Trigger<HIDE_PLAYER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int BG_EFFECT_ON_TRIGGER = 1818;
    template<> struct impl::Trigger<BG_EFFECT_ON_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int BG_EFFECT_OFF_TRIGGER = 1819;
    template<> struct impl::Trigger<BG_EFFECT_OFF_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int END_TRIGGER = 3600;
    template<> struct impl::Trigger<END_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Group, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {0, 0, 0}, Category::Other
        };
        using TriggerType = EndTriggerGameObject;
        static constexpr auto note = "spawn id is target, target pos is center";
    };
    constexpr int PLAYER_CONTROL_TRIGGER = 1932;
    template<> struct impl::Trigger<PLAYER_CONTROL_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {101, 255, 255}, Category::Other
        };
        using TriggerType = PlayerControlGameObject;
    };
    constexpr int OPTIONS_TRIGGER = 2899;
    template<> struct impl::Trigger<OPTIONS_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = GameOptionsTrigger;
    };
    constexpr int GRADIENT_TRIGGER = 2903;
    template<> struct impl::Trigger<GRADIENT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::Gradient, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = GradientTriggerObject;
    };
    constexpr int GRAVITY_TRIGGER = 2066;
    template<> struct impl::Trigger<GRAVITY_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {0, 255, 255}, Category::Other
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int TELEPORT_TRIGGER = 3022;
    template<> struct impl::Trigger<TELEPORT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {104, 226, 255}, Category::Other
        };
        using TriggerType = TeleportPortalObject;
    };
    constexpr int SHADER_TRIGGER = 2904;
    template<> struct impl::Trigger<SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = ShaderGameObject;
    };
    constexpr int SHOCK_WAVE_SHADER_TRIGGER = 2905;
    template<> struct impl::Trigger<SHOCK_WAVE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, true}, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::None,
            {128, 128, 128}, Category::Shader
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id (which btw appears when u click target) is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int SHOCK_LINE_SHADER_TRIGGER = 2907;
    template<> struct impl::Trigger<SHOCK_LINE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, true}, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::None,
            {128, 128, 128}, Category::Shader
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id (which btw appears when u click target) is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int GLITCH_SHADER_TRIGGER = 2909;
    template<> struct impl::Trigger<GLITCH_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, false, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int CHROMATIC_SHADER_TRIGGER = 2910;
    template<> struct impl::Trigger<CHROMATIC_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int CHROMATIC_GLITCH_SHADER_TRIGGER = 2911;
    template<> struct impl::Trigger<CHROMATIC_GLITCH_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int PIXELATE_SHADER_TRIGGER = 2912;
    template<> struct impl::Trigger<PIXELATE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int LENS_CIRCLE_SHADER_TRIGGER = 2913;
    template<> struct impl::Trigger<LENS_CIRCLE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Color, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {128, 128, 128}, Category::Shader
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int RADIAL_BLUR_SHADER_TRIGGER = 2914;
    template<> struct impl::Trigger<RADIAL_BLUR_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Color, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id (which btw appears when u click target) is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int MOTION_BLUR_SHADER_TRIGGER = 2915;
    template<> struct impl::Trigger<MOTION_BLUR_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Group, InputType::Color, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {128, 128, 128}, Category::Shader
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int BULGE_SHADER_TRIGGER = 2916;
    template<> struct impl::Trigger<BULGE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, true}, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {128, 128, 128}, Category::Shader
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id (which btw appears when u click target) is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int PINCH_SHADER_TRIGGER = 2917;
    template<> struct impl::Trigger<PINCH_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            {InputType::Group, true}, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "center id (which btw appears when u click target) is target, fadetime is ShaderGameObject fade in";
    };
    constexpr int GRAY_SCALE_SHADER_TRIGGER = 2919;
    template<> struct impl::Trigger<GRAY_SCALE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::Color, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int SEPIA_SHADER_TRIGGER = 2920;
    template<> struct impl::Trigger<SEPIA_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int INVERT_COLOR_SHADER_TRIGGER = 2921;
    template<> struct impl::Trigger<INVERT_COLOR_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int HUE_SHADER_TRIGGER = 2922;
    template<> struct impl::Trigger<HUE_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int EDIT_COLOR_SHADER_TRIGGER = 2923;
    template<> struct impl::Trigger<EDIT_COLOR_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int SPLIT_SCREEN_SHADER_TRIGGER = 2924;
    template<> struct impl::Trigger<SPLIT_SCREEN_SHADER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::None, InputType::None, InputType::None, InputType::None, 
            true, true, LabelType::None,
            {255, 255, 255}, Category::Shader // todo
        };
        using TriggerType = ShaderGameObject;
        static constexpr auto note = "fadetime is ShaderGameObject fade in";
    };
    constexpr int OLD_NO_ENTER_EFFECT_TRIGGER = 22;
    template<> struct impl::Trigger<OLD_NO_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int FADE_TOP_ENTER_EFFECT_TRIGGER = 24;
    template<> struct impl::Trigger<FADE_TOP_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int FADE_BOTTOM_ENTER_EFFECT_TRIGGER = 23;
    template<> struct impl::Trigger<FADE_BOTTOM_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int FADE_LEFT_ENTER_EFFECT_TRIGGER = 25;
    template<> struct impl::Trigger<FADE_LEFT_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int FADE_RIGHT_ENTER_EFFECT_TRIGGER = 26;
    template<> struct impl::Trigger<FADE_RIGHT_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int SMALL_TO_BIG_ENTER_EFFECT_TRIGGER = 27;
    template<> struct impl::Trigger<SMALL_TO_BIG_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int BIG_TO_SMALL_ENTER_EFFECT_TRIGGER = 28;
    template<> struct impl::Trigger<BIG_TO_SMALL_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int CHAOTIC_ENTER_EFFECT_TRIGGER = 55;
    template<> struct impl::Trigger<CHAOTIC_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int HALVE_LEFT_ENTER_EFFECT_TRIGGER = 56;
    template<> struct impl::Trigger<HALVE_LEFT_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int HALVE_RIGHT_ENTER_EFFECT_TRIGGER = 57;
    template<> struct impl::Trigger<HALVE_RIGHT_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int HALVE_ENTER_EFFECT_TRIGGER = 58;
    template<> struct impl::Trigger<HALVE_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int INVERSE_HALVE_ENTER_EFFECT_TRIGGER = 59;
    template<> struct impl::Trigger<INVERSE_HALVE_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };
    constexpr int NO_ENTER_EFFECT_TRIGGER = 1915;
    template<> struct impl::Trigger<NO_ENTER_EFFECT_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::EnterEffect // todo
        };
        using TriggerType = EnterEffectObject;
    };  
    constexpr int MOVE_ENTER_TRIGGER = 3017;
    template<> struct impl::Trigger<MOVE_ENTER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {255, 255, 255}, Category::AdvancedEnter // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ROTATE_ENTER_TRIGGER = 3018;
    template<> struct impl::Trigger<ROTATE_ENTER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {255, 255, 255}, Category::AdvancedEnter // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int FADE_ENTER_TRIGGER = 3020;
    template<> struct impl::Trigger<FADE_ENTER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {255, 255, 255}, Category::AdvancedEnter // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int TINT_ENTER_TRIGGER = 3021;
    template<> struct impl::Trigger<TINT_ENTER_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::None, InputType::Effect, InputType::None, 
            false, true, LabelType::None,
            {255, 255, 255}, Category::AdvancedEnter // todo
        };
        using TriggerType = EffectGameObject;
    };
    constexpr int ENTER_STOP_TRIGGER = 3023;
    template<> struct impl::Trigger<ENTER_STOP_TRIGGER> {
        static constexpr TriggerInfo info{
            InputType::EnterChannel, InputType::Effect, InputType::None, InputType::None, 
            false, false, LabelType::None,
            {255, 255, 255}, Category::Other // todo
        };
        using TriggerType = EffectGameObject;
    };
}

namespace nwo5::editor::trigger {
    namespace impl {
        SILLY_API_DLL std::vector<TriggerInfo> getTriggerInfoVec();
    }

    /// check if object is trigger
    /// @returns if object is trigger
    SILLY_API_DLL bool is(int pID);
    /// check if object is trigger
    /// @returns if object is trigger
    SILLY_API_DLL bool is(GameObject* pObj);

    /// get trigger info for object
    SILLY_API_DLL const TriggerInfo& get(int pID);
    /// get trigger info for object
    SILLY_API_DLL const TriggerInfo& get(GameObject* pObj);

    /// value of primary target
    SILLY_API_DLL int primaryTarget(GameObject* pObj);
    /// runtime type of primary target e.g. type for pulse trigger would change when use group id is selected
    SILLY_API_DLL InputType primaryTargetType(GameObject* pObj);
    SILLY_API_DLL void setPrimaryTarget(GameObject* pObj, int pVal);
    /// same as primary target
    SILLY_API_DLL int target(GameObject* pObj);
    /// same as primary target
    SILLY_API_DLL InputType targetType(GameObject* pObj);
    /// same as primary target
    SILLY_API_DLL void setTarget(GameObject* pObj, int pVal);

    /// value of secondary target
    SILLY_API_DLL int secondaryTarget(GameObject* pObj);
    /// runtime type of secondary target
    SILLY_API_DLL InputType secondaryTargetType(GameObject* pObj);
    SILLY_API_DLL void setSecondaryTarget(GameObject* pObj, int pVal);
    /// same as secondary target
    SILLY_API_DLL int center(GameObject* pObj);
    /// same as secondary target
    SILLY_API_DLL InputType centerType(GameObject* pObj);
    /// same as secondary target
    SILLY_API_DLL void setCenter(GameObject* pObj, int pVal);

    /// value of primary input
    SILLY_API_DLL int primaryInput(GameObject* pObj);
    /// runtime type of primary input
    SILLY_API_DLL InputType primaryInputType(GameObject* pObj);
    SILLY_API_DLL void setPrimaryInput(GameObject* pObj, int pVal);
    /// same as primary input
    SILLY_API_DLL int identifier(GameObject* pObj);
    /// same as primary input
    SILLY_API_DLL InputType identifierType(GameObject* pObj);
    /// same as primary input
    SILLY_API_DLL void setIdentifier(GameObject* pObj, int pVal);

    /// value of secondary input
    SILLY_API_DLL int secondaryInput(GameObject* pObj);
    /// runtime type of secondary input
    SILLY_API_DLL InputType secondaryInputType(GameObject* pObj);
    SILLY_API_DLL void setSecondaryInput(GameObject* pObj, int pVal);

    SILLY_API_DLL bool hasDuration(int pID);
    SILLY_API_DLL bool hasDuration(GameObject* pObj);
    SILLY_API_DLL float duration(GameObject* pObj);
    SILLY_API_DLL void setDuration(GameObject* pObj, float pDuration);
    SILLY_API_DLL bool hasEasing(int pID);
    SILLY_API_DLL bool hasEasing(GameObject* pObj);
    SILLY_API_DLL EasingType easing(GameObject* pObj);
    SILLY_API_DLL void setEasing(GameObject* pObj, EasingType pEasing);

    SILLY_API_DLL bool hasLabel(int pID);
    SILLY_API_DLL bool hasLabel(GameObject* pObj);
    SILLY_API_DLL LabelType labelType(int pID);
    SILLY_API_DLL LabelType labelType(GameObject* pObj);

    SILLY_API_DLL Category category(int pID);
    SILLY_API_DLL Category category(GameObject* pObj);

    /// this took a while
    SILLY_API_DLL cocos2d::ccColor3B color(int pID);
    /// returns target color for color trigger/pulse so that might be useful :3
    SILLY_API_DLL cocos2d::ccColor3B color(GameObject* pObj);

    /// check if activate group enabled, e.g. toggle 
    /// @note touch trigger always reutrns false
    /// @returns false if trigger doesnt supprot option, activate group enabled otherwise
    SILLY_API_DLL bool activateGroup(GameObject* pObj);
    /// check if target mode enabled
    /// - target option in some shaders
    /// - target/direction mode in move trigger
    /// - aim/follow mode in rotation trigger
    /// @returns false if trigger doesnt support option, target mode enabled otherwise
    SILLY_API_DLL bool targetModeEnabled(GameObject* pObj);
}