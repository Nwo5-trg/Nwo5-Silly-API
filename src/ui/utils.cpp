#include <ui/include.hpp>

using namespace geode::prelude;

namespace nwo5::ui {
    CCRect nodesBounds(CCArray* pNodes) {
        if (!pNodes || !pNodes->count()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : CCArrayExt<CCNode*>(pNodes)) {
            const auto rect = obj->boundingBox();

            min.x = std::min(min.x, rect.origin.x);
            min.y = std::min(min.y, rect.origin.y);
            max.x = std::max(max.x, rect.origin.x + rect.size.width);
            max.y = std::max(max.y, rect.origin.y + rect.size.height);
        }

        return {min, {max.x - min.x, max.y - min.y}};
    }
    CCRect nodesBounds(std::span<CCNode* const> pNodes) {
        if (pNodes.empty()) {
            return CCRectZero;
        }

        CCPoint min = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        CCPoint max = {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest()};

        for (auto obj : pNodes) {
            const auto rect = obj->boundingBox();

            min.x = std::min(min.x, rect.origin.x);
            min.y = std::min(min.y, rect.origin.y);
            max.x = std::max(max.x, rect.origin.x + rect.size.width);
            max.y = std::max(max.y, rect.origin.y + rect.size.height);
        }

        return {min, {max.x - min.x, max.y - min.y}};
    }
    CCSize nodesSize(CCArray* pNodes) {
        return nodesBounds(pNodes).size;
    }
    CCSize nodesSize(std::span<CCNode* const> pNodes) {
        return nodesBounds(pNodes).size;
    }
}