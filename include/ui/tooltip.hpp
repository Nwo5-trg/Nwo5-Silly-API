#pragma once

namespace nwo5::ui {
    /// basic tooltip class !
    /// for automatic mode (which is default) add a TooltipInfo userobject with id "nwo5.silly-api/tooltip" to a node and those nodes will show tooltips !
    /// if you want to do all the logic yourself you can just set an updatefunc
    /// @note automatic mode does not pay attention to z order soooo gl with that might make that toggleable later cuz it would b slower
    class Tooltip final : public cocos2d::CCNode {
    protected:
        geode::NineSlice* m_background = nullptr;
        geode::Label* m_label = nullptr;

        geode::Function<void()> m_updateFunc = nullptr;

        bool m_followingMouse = false;
        bool m_automatic = false;
        bool m_dynamicAnchor = false;
        cocos2d::CCPoint m_defaultAnchor = {0.0f, 0.0f};

        float m_padding = 5.0f;

        void updateText(geode::ZStringView pText);
        void updateVisible();

        bool init(geode::ZStringView pFont, bool pFollowMouse, bool pAutomatic);
    public:
        /// show tooltip with text
        void show(geode::ZStringView pText);
        /// hide tool tip
        void hide();

        /// update tooltips anchor position (dynamically changes if touching window edge)
        void updateAnchor();

        /// runs on mouse move and mouse scroll
        void setUpdateFunc(geode::Function<void()> pFunc);

        /// set background opacity
        void setOpacity(uint8_t pOpacity);
        /// get opacity
        /// @returns background opacity
        uint8_t getOpacity() const;

        /// set max width of tooltip
        void setMaxWidth(float pWidth);
        /// get max width
        /// @returns max width
        float getMaxWidth() const;

        /// set if tooltip should go to mouse pos
        void setFollowMouse(bool pOn);
        /// get follow mouse enabled
        /// @returns tooltip is following mouse
        bool getFollowMouse() const;

        /// set if tooltip should show/hide automatically (hides tooltip when disabled)
        /// @note only works with follow mouse enabled
        void setAutomatic(bool pOn);
        /// get automatic mode enabled
        /// @returns tooltip is automatic
        bool isAutomatic() const;

        /// set if tooltip should dynamically set anchor based on position
        /// you can force an anchor update with Tooltip::updateAnchor
        /// @note only works with follow mouse enabled
        void setDynamicAnchor(bool pOn);
        /// get dynamic anchor enabled
        /// @returns dynamic anchor enabled
        bool isDynamicAnchor() const;
        /// set default anchor of tooltip and sets current anchor
        void setDefaultAnchor(cocos2d::CCPoint pAnchor);
        /// get default anchor
        /// @returns default anchor
        cocos2d::CCPoint getDefaultAnchor() const;

        /// set padding (total space between background and label)
        void setPadding(float pPadding);
        /// get padding
        /// @returns padding
        float getPadding() const;

        geode::Label* getLabel() const;
        geode::NineSlice* getBackground() const;

        /// create tooltip
        /// @param pFont label font
        /// @param pFollowMouse if tooltip should follow mouse or be static (ie ur responsible for moving it)
        /// @param pAutomatic if follow mouse is true, do you want the tooltip to automatically show/hide on objects with tooltips
        static Tooltip* create(geode::ZStringView pFont, bool pFollowMouse = true, bool pAutomatic = true);
    };

    class TooltipInfo final : public cocos2d::CCObject {
    protected:
        std::string m_text;
        cocos2d::CCNode* m_node = nullptr;

        bool init(cocos2d::CCNode* pNode, geode::ZStringView pText);
        ~TooltipInfo();

        inline static std::unordered_set<cocos2d::CCNode*> set;
        static geode::ListenerHandle listener;

    public:
        static const std::unordered_set<cocos2d::CCNode*>& getSet();

        geode::ZStringView getString() const;
        cocos2d::CCNode* getNode() const;

        /// create a tooltip info object
        /// @param pText tooltip text
        static TooltipInfo* create(geode::ZStringView pText);
        /// create a tooltip info object and add it to node
        /// @param pNode node tooltip will be added to
        /// @param pText tooltip text
        static TooltipInfo* create(cocos2d::CCNode* pNode, geode::ZStringView pText);
    };
};