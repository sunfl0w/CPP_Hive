#pragma once

#include "AxialPosition.hpp"

#include <vector>

namespace Hive {
    class SlidePathNode {
    private:
        AxialPosition position;
        SlidePathNode* parentNode;
        std::vector<SlidePathNode*> childNodes;

    public:
        SlidePathNode(const AxialPosition& position);
        AxialPosition GetPosition();
        SlidePathNode* GetParent();
        std::vector<SlidePathNode*> GetChildren();
        void AddChildNode(SlidePathNode* childNode);

        SlidePathNode* GetParentAtRelativeDepth(int depth);
        std::vector<SlidePathNode*> GetChildrenAtRelativeDepth(int depth);
    };
}  // namespace Hive
