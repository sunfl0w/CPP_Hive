#include "SlidePathNode.hpp"

namespace Hive {
    SlidePathNode::SlidePathNode(const AxialPosition& position) {
        this->position = position;
        this->parentNode = parentNode;
    }

    AxialPosition SlidePathNode::GetPosition() {
        return position;
    }

    SlidePathNode* SlidePathNode::GetParent() {
        return parentNode;
    }

    std::vector<SlidePathNode*> SlidePathNode::GetChildren() {
        return childNodes;
    }

    void SlidePathNode::AddChildNode(SlidePathNode* childNode) {
        childNode->parentNode = this;
        this->childNodes.push_back(childNode);
    }

    SlidePathNode* SlidePathNode::GetParentAtRelativeDepth(int depth) {
        SlidePathNode* currentNode = this;
        for(int i = 0; i < depth; i++) {
            currentNode = currentNode->parentNode;
        }
        return currentNode;
    }

    std::vector<SlidePathNode*> SlidePathNode::GetChildrenAtRelativeDepth(int depth) {
        std::vector<SlidePathNode*> currentNodes;
        currentNodes.push_back(this);
        for(int i = 0; i < depth; i++) {
            std::vector<SlidePathNode*> newNodes;
            for(SlidePathNode* node : currentNodes) {
                std::vector<SlidePathNode*> childNodes = node->childNodes;
                newNodes.insert(newNodes.end(), childNodes.begin(), childNodes.end());
            }
            currentNodes = newNodes;
        }
        return currentNodes;
    }
}  // namespace Hive