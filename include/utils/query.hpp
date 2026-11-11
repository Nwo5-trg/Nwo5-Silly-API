#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    /// find nodes by certain criteria safely :3
    /// @todo mayb userObject/byUserObject (and flag)
    template<typename ImplNode, typename Node = std::remove_pointer_t<ImplNode>>
    requires std::derived_from<Node, cocos2d::CCNode>
    class Query final {
    private:
        Node* m_node;

    public:
        Query(Node* node) 
            : m_node(node) {}

        operator Node*() const {
            return m_node;
        }

        auto operator*() const {
            return m_node;
        }

        auto get() const {
            return m_node;
        }
        auto data() const {
            return m_node;
        }
        auto unwrap() const {
            return m_node;
        }





        /// check if current node has id (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> id(geode::ZStringView id) {
            if (!m_node || m_node->getID() != id) {
                return nullptr;
            }

            if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                return geode::cast::typeinfo_cast<T*>(m_node);
            } else {
                return m_node;
            }
        }
        /// check if current node has tag (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> tag(int tag) {
            if (!m_node || m_node->getTag() != tag) {
                return nullptr;
            }

            if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                return geode::cast::typeinfo_cast<T*>(m_node);
            } else {
                return m_node;
            }
        }

        /// typeinfo cast current node
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> type() {
            if (!m_node) {
                return nullptr;
            }

            return geode::cast::typeinfo_cast<T*>(m_node);
        }

        /// check if current node matches predicate (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>, std::predicate<T*> Callback>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> predicate(Callback&& predicate) {
            if (!m_node) {
                return nullptr;
            }

            if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                auto cast = geode::cast::typeinfo_cast<T*>(m_node);

                if (!cast || !predicate(cast)) {
                    return nullptr;
                }

                return cast;
            }
            else {
                if (!predicate(m_node)) {
                    return nullptr;
                }

                return m_node;
            }

            return nullptr;
        }

        /// check if current node has x amount of children (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> childrenCount(size_t count) {
            if (!m_node || m_node->getchildrenCount() != count) {
                return nullptr;
            }

            if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                return geode::cast::typeinfo_cast<T*>(m_node);
            } else {
                return m_node;
            }
        }

        /// check if current node has sprite name (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCSprite, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCSprite>
        Query<T> sprite(geode::ZStringView spriteName) {
            if (!m_node || !geode::cocos::isSpriteName(m_node, spriteName.c_str())) {
                return nullptr;
            }

            return geode::cast::typeinfo_cast<T*>(m_node);
        }
        /// check if current node has sprite frame name (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCSprite, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCSprite>
        Query<T> frame(geode::ZStringView spriteFrameName) {
            if (!m_node || !geode::cocos::isSpriteFrameName(m_node, spriteFrameName.c_str())) {
                return nullptr;
            }

            return geode::cast::typeinfo_cast<T*>(m_node);
        }

        /// check if current node matches string using cclabelprotocol (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCLabelProtocol, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCLabelProtocol>
        Query<T> string(geode::ZStringView string) {
            if (!m_node) {
                return nullptr;
            }

            auto cast = geode::cast::typeinfo_cast<T*>(m_node);

            if (!cast || string != cast->getString()) {
                return nullptr;
            }

            return cast;
        }





        /// find child node with id (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> byID(geode::ZStringView id) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child || child->getID() != id) {
                    continue;
                }

                if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                    auto cast = geode::cast::typeinfo_cast<T*>(child);

                    if (!cast) {
                        continue;
                    }

                    return cast;
                }
                else {
                    return child;
                }
            }

            return nullptr;
        }
        /// find child node with tag (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> byTag(int tag) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child || child->getTag() != tag) {
                    continue;
                }

                if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                    auto cast = geode::cast::typeinfo_cast<T*>(child);

                    if (!cast) {
                        continue;
                    }

                    return cast;
                }
                else {
                    return child;
                }
            }

            return nullptr;
        }

        /// find child node by type
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> byType(size_t index = 0) {
            if (!m_node) {
                return nullptr;
            }

            return m_node->template getChildByType<T*>(index);
        }
        /// same as byType
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> byIndex(size_t index = 0) {
            if (!m_node) {
                return nullptr;
            }

            return typeinfo_cast<T*>(m_node->template getChildByType<cocos2d::CCNode>(index));
        }

        /// find child that matches predicate (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>, std::predicate<T*> Callback>
        requires std::derived_from<T, cocos2d::CCNode>
        Query<T> byPredicate(Callback&& predicate) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child) {
                    continue;
                }
                
                if constexpr (!std::same_as<T, cocos2d::CCNode>) {
                    auto cast = geode::cast::typeinfo_cast<T*>(child);

                    if (!cast || !predicate(cast)) {
                        continue;
                    }

                    return cast;
                }
                else {
                    if (!predicate(child)) {
                        continue;
                    }

                    return child;
                }
            }

            return nullptr;
        }

        /// find child with sprite name (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCSprite, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCSprite>
        Query<T> bySprite(geode::ZStringView spriteName) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child || !geode::cocos::isSpriteName(child, spriteName.c_str())) {
                    continue;
                }

                auto cast = geode::cast::typeinfo_cast<T*>(child);

                if (!cast) {
                    continue;
                }

                return cast;
            }

            return nullptr;
        }
        /// find child with sprite frame name (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCSprite, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCSprite>
        Query<T> byFrame(geode::ZStringView spriteFrameName) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child || !geode::cocos::isSpriteFrameName(child, spriteFrameName.c_str())) {
                    continue;
                }

                auto cast = geode::cast::typeinfo_cast<T*>(child);

                if (!cast) {
                    continue;
                }

                return cast;
            }

            return nullptr;
        }

        /// find child that matches string using cclabelprotocol (and optionally typeinfo cast)
        template<typename ImplT = cocos2d::CCLabelProtocol, typename T = std::remove_pointer_t<ImplT>>
        requires std::derived_from<T, cocos2d::CCLabelProtocol>
        Query<T> byString(geode::ZStringView string) {
            if (!m_node) {
                return nullptr;
            }

            for (auto child : m_node->getChildrenExt()) {
                if (!child) {
                    continue;
                }

                auto cast = geode::cast::typeinfo_cast<T*>(child);

                if (!cast || string != cast->getString()) {
                    continue;
                }

                return cast;
            }

            return nullptr;
        }
    };

    template<typename T>
    Query(T*) -> Query<T*, T>;
}