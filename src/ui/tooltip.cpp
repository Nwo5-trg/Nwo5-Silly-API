#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    void Tooltip::updateText(geode::ZStringView pText) {
        m_label->setText(pText);

        m_background->setContentSize({ui::w(m_label) + m_padding, ui::h(m_label) + m_padding});

        this->setContentSize(ui::size(m_background));

        Setup(m_background).center();
        Setup(m_label).center();
    }
    void Tooltip::updateVisible() {
        if (!this->getParent()) {
            return;
        }

        const auto worldPos = cocos::getMousePos();

        const auto find = [this, worldPos] (this auto&& pSelf, CCNode* pNode, CCPoint pPos) -> CCNode* {
            if (!pNode || !pNode->isVisible()) {
                return nullptr;
            }

            if (pNode->boundingBox().containsPoint(pPos)) {
                if (TooltipInfo::getSet().contains(pNode)) {
                    return pNode;
                }
            }

            const auto pos = pNode->convertToNodeSpace(worldPos);

            for (auto child : pNode->getChildrenExt()) {
                if (auto node = pSelf(child, pos)) {
                    return node;
                }
            }

            return nullptr;
        };

        CCNode* node = nullptr;
        
        const auto pos = this->getParent()->convertToNodeSpace(worldPos);

        for (auto child : this->getParent()->getChildrenExt()) {
            if (child == this) {
                break;
            }

            node = find(child, pos);

            if (node) {
                break;
            }
        }

        if (node) {
            if (auto info = static_cast<TooltipInfo*>(node->getUserObject("tooltip"_spr))) {
                this->show(info->getString());
            }
        } else {
            this->hide();
        }
    }

    bool Tooltip::init(geode::ZStringView pFont, bool pFollowMouse, bool pAutomatic) {
        if (!CCNode::init()) {
            return false;
        }

        m_followingMouse = pFollowMouse;
        m_dynamicAnchor = pFollowMouse;
        m_automatic = pAutomatic;

        m_background = Setup(NineSlice::create("square02_001.png"))
            .id("background"_spr)
            .pos(CCPointZero)
            .opacity(127)
            .parent(this);

        m_label = Setup(Label::create("", pFont))
            .id("label"_spr)
            .pos(CCPointZero)
            .parent(this);
        m_label->setMaxWidth(300.0f - m_padding);

        Setup(this)
            .order(10)
            .hide();

        this->addEventListener(MouseMoveEvent(), [this] (int32_t, int32_t) {
            if (!this->getParent()) {
                return;
            }
            
            if (this->m_followingMouse) {
                this->setPosition(this->getParent()->convertToNodeSpace(cocos::getMousePos()));
            }
            if (this->m_dynamicAnchor) {
                this->updateAnchor();
            }
            if (m_automatic) {
                this->updateVisible();
            }

            if (m_updateFunc) {
                this->m_updateFunc();
            }
        });
        
        this->addEventListener(ScrollWheelEvent(), [this] (int32_t, int32_t) {
            if (!this->getParent()) {
                return;
            }

            if (m_automatic) {
                this->updateVisible();
            }

            if (m_updateFunc) {
                this->m_updateFunc();
            }
        });

        return true;
    }

    void Tooltip::show(geode::ZStringView pText) {
        this->setVisible(true);

        if (pText != m_label->getString()) {
            this->updateText(pText);
        }
    }
    void Tooltip::hide() {
        this->setVisible(false);
    }

    void Tooltip::updateAnchor() {
        auto parent = this->getParent();

        if (!parent) {
            return;
        }

        const auto rect = this->boundingBox();
        const auto min = parent->convertToWorldSpace(rect.origin);
        const auto max = parent->convertToWorldSpace({rect.getMaxX(), rect.getMaxY()});

        auto anchor = m_defaultAnchor;

        if (min.x < 0.0f) {
            anchor.x = 0.0f;
        }
        else if (max.x > CCDirector::get()->getWinSize().width) {
            anchor.x = 1.0f;
        }

        if (min.y < 0.0f) {
            anchor.y = 0.0f;
        }
        else if (max.y > CCDirector::get()->getWinSize().height) {
            anchor.y = 1.0f;
        }

        this->setAnchorPoint(anchor);

        Setup(m_background).center();
        Setup(m_label).center();
    }

    void Tooltip::setUpdateFunc(geode::Function<void()> pFunc) {
        m_updateFunc = std::move(pFunc);
    }

    void Tooltip::setOpacity(uint8_t pOpacity) {
        m_background->setOpacity(pOpacity);
    }
    uint8_t Tooltip::getOpacity() const {
        return m_background->getOpacity();
    }

    void Tooltip::setMaxWidth(float pWidth) {
        m_label->setMaxWidth(pWidth - m_padding);

        this->updateText(m_label->getText());
    }
    float Tooltip::getMaxWidth() const {
        return m_label->getMaxWidth();
    }

    void Tooltip::setFollowMouse(bool pOn) {
        m_followingMouse = pOn;
    }
    bool Tooltip::getFollowMouse() const {
        return m_followingMouse;
    }

    void Tooltip::setAutomatic(bool pOn) {
        m_automatic = pOn;

        if (!m_automatic) {
            this->hide();
        }
    }
    bool Tooltip::isAutomatic() const {
        return m_automatic;
    }

    void Tooltip::setDynamicAnchor(bool pOn) {
        m_dynamicAnchor = pOn;
    }
    bool Tooltip::isDynamicAnchor() const {
        return m_dynamicAnchor;
    }
    void Tooltip::setDefaultAnchor(CCPoint pAnchor) {
        m_defaultAnchor = pAnchor;

        this->setAnchorPoint(m_defaultAnchor);

        Setup(m_background).center();
        Setup(m_label).center();
    }
    CCPoint Tooltip::getDefaultAnchor() const {
        return m_defaultAnchor;
    }

    void Tooltip::setPadding(float pPadding) {
        m_padding = pPadding;
    }
    float Tooltip::getPadding() const {
        return m_padding;
    }

    Label* Tooltip::getLabel() const {
        return m_label;
    }
    NineSlice* Tooltip::getBackground() const {
        return m_background;
    }

    Tooltip* Tooltip::create(geode::ZStringView pFont, bool pFollowMouse, bool pAutomatic) {
        auto ret = new Tooltip;

        if (!ret->init(pFont, pFollowMouse, pAutomatic)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }

    bool TooltipInfo::init(cocos2d::CCNode* pNode, geode::ZStringView pText) {
        m_text = pText;

        if (pNode) {
            pNode->setUserObject(this);
        }

        return true;
    }
    TooltipInfo::~TooltipInfo() {
        set.erase(this->m_node);
    }

    ListenerHandle TooltipInfo::listener = UserObjectSetEvent("tooltip"_spr).listen([] (CCNode* pNode, CCObject* pObject) {
        log::error("called");

        if (set.contains(pNode)) {
            set.erase(pNode);
        }
        if (auto info = typeinfo_cast<TooltipInfo*>(pObject)) {
            set.insert(pNode);
            info->m_node = pNode;

            log::error("added");
        }
    });

    const std::unordered_set<cocos2d::CCNode*>& TooltipInfo::getSet() {
        return set;
    }

    geode::ZStringView TooltipInfo::getString() const {
        return m_text;
    }
    CCNode* TooltipInfo::getNode() const {
        return m_node;
    }

    TooltipInfo* TooltipInfo::create(geode::ZStringView pText) {
        auto ret = new TooltipInfo;

        if (!ret->init(nullptr, pText)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
    TooltipInfo* TooltipInfo::create(cocos2d::CCNode* pNode, geode::ZStringView pText) {
        auto ret = new TooltipInfo;

        if (!ret->init(pNode, pText)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
}