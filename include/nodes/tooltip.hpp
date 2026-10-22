#pragma once

#include "../export.hpp"

namespace nwo5::nodes {
    /// basic tooltip class 
    /// just create and add as child to ur popup (or to whatever node is the parent to all the nodes thatll have tooltip)
    /// for automatic mode (which is default) add a TooltipInfo userobject with id "nwo5.silly-api/tooltip" to a node and those nodes will show tooltips !
    /// if you want to do all the logic yourself you can just set an updatefunc
    /// @note automatic mode does not pay attention to z order soooo gl with that might make that toggleable later cuz it would b slower
    class SILLY_API_DLL Tooltip final : public cocos2d::CCNode {
    protected:
        geode::NineSlice* m_background = nullptr;
        geode::Label* m_label = nullptr;

        geode::Function<void()> m_updateFunc = nullptr;

        bool m_followingMouse = false;
        bool m_automatic = false;
        bool m_dynamicAnchor = false;
        cocos2d::CCPoint m_defaultAnchor = {0.0f, 0.0f};

        float m_padding = 5.0f;

        void updateText(geode::ZStringView text);
        void updateAutomatic();

        bool init(geode::ZStringView font, bool followMouse, bool automatic);
    public:
        /// show tooltip with text
        void show(geode::ZStringView text);
        /// hide tool tip
        void hide();

        /// update tooltips anchor position (dynamically changes if touching window edge)
        void updateAnchor();

        /// runs on mouse move and mouse scroll
        void setUpdateFunc(geode::Function<void()> func);

        /// set background opacity
        void setOpacity(uint8_t opacity);
        /// get opacity (default is 127)
        /// @returns background opacity
        uint8_t getOpacity() const;

        /// set max width of tooltip
        void setMaxWidth(float width);
        /// get max width (default is 300)
        /// @returns max width
        float getMaxWidth() const;

        /// set if tooltip should go to mouse pos
        void setFollowMouse(bool on);
        /// get follow mouse enabled (default is true)
        /// @returns tooltip is following mouse
        bool getFollowMouse() const;

        /// set if tooltip should show/hide automatically (hides tooltip when disabled)
        /// @note only works with follow mouse enabled
        void setAutomatic(bool on);
        /// get automatic mode enabled (default is true)
        /// @returns tooltip is automatic
        bool getAutomatic() const;

        /// set if tooltip should dynamically set anchor based on position
        /// you can force an anchor update with Tooltip::updateAnchor
        /// @note only works with follow mouse enabled
        void setDynamicAnchor(bool on);
        /// get dynamic anchor enabled (default is true)
        /// @returns dynamic anchor enabled
        bool getDynamicAnchor() const;
        /// set default anchor of tooltip and sets current anchor
        void setDefaultAnchor(cocos2d::CCPoint anchor);
        /// get default anchor
        /// @returns default anchor
        cocos2d::CCPoint getDefaultAnchor() const;

        /// set padding (*total* space between background and label, distance between backround edge and label on either side will be this number / 2)
        void setPadding(float padding);
        /// get padding (default is 5)
        /// @returns padding
        float getPadding() const;

        geode::Label* getLabel() const;
        geode::NineSlice* getBackground() const;

        /// create tooltip
        /// @param font label font
        /// @param followMouse if tooltip should follow mouse (and dynamic anchor) or be static (ie ur responsible for moving it)
        /// @param automatic if follow mouse is true, do you want the tooltip to automatically show/hide on objects with tooltips
        static Tooltip* create(geode::ZStringView font, bool followMouse = true, bool automatic = true);
    };

    class SILLY_API_DLL TooltipInfo final : public cocos2d::CCObject {
    protected:
        std::string m_text;
        cocos2d::CCNode* m_node = nullptr;

        bool init(cocos2d::CCNode* node, geode::ZStringView text);
        ~TooltipInfo();

        inline static std::unordered_set<cocos2d::CCNode*> set;
        static geode::ListenerHandle listener;

    public:
        static const std::unordered_set<cocos2d::CCNode*>& getSet();

        geode::ZStringView getString() const;
        cocos2d::CCNode* getNode() const;

        /// create a tooltip info object
        /// @param text tooltip text
        static TooltipInfo* create(geode::ZStringView text);
        /// create a tooltip info object and add it to node
        /// @param node node tooltip will be added to
        /// @param text tooltip text
        static TooltipInfo* create(cocos2d::CCNode* node, geode::ZStringView text);
    };
};