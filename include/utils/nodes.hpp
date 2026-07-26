#pragma once

#include "../export.hpp"

namespace nwo5::utils {
    namespace impl {
        struct SILLY_API_DLL GetChildQueryBase {};
    }

    // i should prolly split this into multiple types but ill do that some other time (never)
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    struct GetChildQuery : impl::GetChildQueryBase {
        const std::string id;
        const int index{};

        GetChildQuery()
            = default;
        GetChildQuery(int pIndex)
            : index(pIndex) {}
        GetChildQuery(std::string_view pID)
            : id(pID) {}

        cocos2d::CCNode* query(cocos2d::CCNode* pNode) {
            if (id.empty()) {
                return pNode->getChildByType<T*>(index);
            }
            else {
                if constexpr (std::same_as<T, cocos2d::CCNode>) {
                    return pNode->getChildByID(id);
                }
                else {
                    return geode::cast::typeinfo_cast<T*>(pNode->getChildByID(id));
                }
            }
        }
    };
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryID = GetChildQuery<T>;
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryIndex = GetChildQuery<T>;
    template<typename ImplT, typename T = std::remove_pointer_t<ImplT>>
    using GetChildQueryType = GetChildQuery<T>;
    
    template<typename ImplT = cocos2d::CCNode, typename T = std::remove_pointer_t<ImplT>, typename... Args>
    requires (std::derived_from<Args, impl::GetChildQueryBase> && ...)
    T* getNestedChildSafe(cocos2d::CCNode* pNode, Args... pArgs) {
        if (!pNode) {
            return nullptr;
        }

        auto node = static_cast<cocos2d::CCNode*>(pNode);

        ([&] -> bool {
            return (node = pArgs.query(node));
        }() && ...);

        if constexpr (std::same_as<T, cocos2d::CCNode>) {
            return node;
        }
        else {
            return geode::cast::typeinfo_cast<T*>(node);
        }
    }
}