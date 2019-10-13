#include "Node.hpp"

BSP::Node::Node(glm::vec2 _bottomLeft, glm::vec2 _topRight) {
    this->gridBottomLeft = _bottomLeft;
    this->gridTopRight   = _topRight;
}

BSP::Node::~Node() {
    delete (left);
    delete (right);
    right  = nullptr;
    left   = nullptr;
    parent = nullptr;
}

glm::vec2 BSP::Node::getCentrePoint() {
    glm::vec2 centre;
    centre = (gridTopRight - gridBottomLeft);
    centre.x *= 0.5;
    centre.y *= 0.5;
    centre += gridBottomLeft;
    return centre;
}

BSP::Node::Node() {}