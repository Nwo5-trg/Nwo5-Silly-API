#include <nodes/include.hpp>
#include <ui/include.hpp>

using namespace nwo5::ui::prelude;
using namespace geode::prelude;

namespace nwo5::nodes {
    void Tooltip::updateText(geode::ZStringView text) {
        m_label->setText(text);

        m_background->setContentSize({ui::w(m_label) + m_padding, ui::h(m_label) + m_padding});

        this->setContentSize(ui::size(m_background));

        Setup(m_background).center();
        Setup(m_label).center();
    }
    void Tooltip::updateAutomatic() {
        if (!this->getParent()) {
            return;
        }

        const auto worldPos = cocos::getMousePos();

        const auto find = [this, worldPos] (this auto&& self, CCNode* node, CCPoint pos) -> CCNode* {
            if (!node || !node->isVisible()) {
                return nullptr;
            }

            if (node->boundingBox().containsPoint(pos)) {
                if (TooltipInfo::getSet().contains(node)) {
                    return node;
                }
            }

            const auto nodePos = node->convertToNodeSpace(worldPos);

            for (auto child : node->getChildrenExt()) {
                if (auto node = self(child, nodePos)) {
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

    bool Tooltip::init(geode::ZStringView font, bool followMouse, bool automatic) {
        if (!CCNode::init()) {
            return false;
        }

        m_followingMouse = followMouse;
        m_dynamicAnchor = followMouse;
        m_automatic = automatic;

        m_background = ui::nineSlice(resources::sprite::SQUARE)
            .id("background"_spr)
            .pos(CCPointZero)
            .opacity(127)
            .parent(this);

        m_label = ui::label(font)
            .id("label"_spr)
            .pos(CCPointZero)
            .maxWidth(300.0f - m_padding)
            .breakWords(false)
            .parent(this);

        Setup(this)
            .order(10)
            .hide();

        this->updateText("");

        this->addEventListener(MouseMoveEvent(), [this] (auto, auto) {
            if (!this->getParent()) {
                return;
            }
            
            if (this->m_followingMouse) {
                this->setPosition(this->getParent()->convertToNodeSpace(cocos::getMousePos()));

                if (m_automatic) {
                    this->updateAutomatic();
                }
                if (this->m_dynamicAnchor) {
                    this->updateAnchor();
                }
            }

            if (m_updateFunc) {
                this->m_updateFunc();
            }
        });
        
        this->addEventListener(ScrollWheelEvent(), [this] (double, double) {
            if (!this->getParent()) {
                return;
            }

            if (this->m_followingMouse) {
                this->setPosition(this->getParent()->convertToNodeSpace(cocos::getMousePos()));

                if (m_automatic) {
                    this->updateAutomatic();
                }
                if (this->m_dynamicAnchor) {
                    this->updateAnchor();
                }   
            }

            if (m_updateFunc) {
                this->m_updateFunc();
            }
        });

        return true;
    }

    void Tooltip::show(geode::ZStringView text) {
        this->setVisible(true);

        if (text != m_label->getString()) {
            this->updateText(text);
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

        const auto pos = this->getPosition() + CCPoint{ui::sw(this) * m_defaultAnchor.x * 2 - 1, ui::sh(this) * m_defaultAnchor.y * 2 - 1};

        const auto min = parent->convertToWorldSpace(pos);
        const auto max = parent->convertToWorldSpace(pos + ui::ssize(this));

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

    void Tooltip::setUpdateFunc(geode::Function<void()> func) {
        m_updateFunc = std::move(func);
    }

    void Tooltip::setOpacity(uint8_t opacity) {
        m_background->setOpacity(opacity);
    }
    uint8_t Tooltip::getOpacity() const {
        return m_background->getOpacity();
    }

    void Tooltip::setMaxWidth(float width) {
        m_label->setMaxWidth(width - m_padding);

        this->updateText(m_label->getText());
    }
    float Tooltip::getMaxWidth() const {
        return m_label->getMaxWidth() + m_padding;
    }

    void Tooltip::setFollowMouse(bool on) {
        m_followingMouse = on;
    }
    bool Tooltip::getFollowMouse() const {
        return m_followingMouse;
    }

    void Tooltip::setAutomatic(bool on) {
        m_automatic = on;

        if (!m_automatic) {
            this->hide();
        }
    }
    bool Tooltip::getAutomatic() const {
        return m_automatic;
    }

    void Tooltip::setDynamicAnchor(bool on) {
        m_dynamicAnchor = on;
    }
    bool Tooltip::getDynamicAnchor() const {
        return m_dynamicAnchor;
    }
    void Tooltip::setDefaultAnchor(CCPoint anchor) {
        m_defaultAnchor = anchor;

        this->setAnchorPoint(m_defaultAnchor);

        Setup(m_background).center();
        Setup(m_label).center();
    }
    CCPoint Tooltip::getDefaultAnchor() const {
        return m_defaultAnchor;
    }

    void Tooltip::setPadding(float padding) {
        m_label->setMaxWidth((m_label->getMaxWidth() + m_padding) - padding);
        m_padding = padding;
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

    Tooltip* Tooltip::create(geode::ZStringView font, bool followMouse, bool automatic) {
        auto ret = new Tooltip;

        if (!ret->init(font, followMouse, automatic)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }

    bool TooltipInfo::init(cocos2d::CCNode* node, geode::ZStringView text) {
        m_text = text;

        if (node) {
            node->setUserObject("tooltip"_spr, this);
        }

        return true;
    }
    TooltipInfo::~TooltipInfo() {
        set.erase(this->m_node);
    }

    ListenerHandle TooltipInfo::listener = UserObjectSetEvent("tooltip"_spr).listen([] (CCNode* node, CCObject* object) {
        if (set.contains(node)) {
            set.erase(node);
        }
        if (auto info = typeinfo_cast<TooltipInfo*>(object)) {
            set.insert(node);
            info->m_node = node;
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

    TooltipInfo* TooltipInfo::create(geode::ZStringView text) {
        auto ret = new TooltipInfo;

        if (!ret->init(nullptr, text)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
    TooltipInfo* TooltipInfo::create(cocos2d::CCNode* node, geode::ZStringView text) {
        auto ret = new TooltipInfo;

        if (!ret->init(node, text)) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
}