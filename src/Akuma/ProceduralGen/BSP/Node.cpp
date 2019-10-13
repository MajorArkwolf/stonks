#include "Node.hpp"

BSP::Node::Node(glm::vec2 _bottomLeft, glm::vec2 _topRight) {
    this->gridBottomLeft = _bottomLeft;
    this->gridTopRight   = _topRight;
}

BSP::Node::~Node() {
    delete (this->left);
    delete (this->right);
    right  = nullptr;
    left   = nullptr;
    parent = nullptr;
}

glm::vec2 BSP::Node::getCentrePoint() {
    glm::vec2 centre;
    centre = (gridTopRight - gridBottomLeft);
    centre.x *= static_cast<float>(0.5);
    centre.y *= static_cast<float>(0.5);
    centre += gridBottomLeft;
    return centre;
}

BSP::Node::Node() {}
