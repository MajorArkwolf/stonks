#include "Node.hpp"

/**
 * @brief Overloaded constructor for Node
 * @param _bottomLeft Bottom left grid node position of partition
 * @param _topRight Top right grid node position of partition
 */
BSP::Node::Node(glm::uvec2 _bottomLeft, glm::uvec2 _topRight) {
    this->gridBottomLeft = _bottomLeft;
    this->gridTopRight   = _topRight;
}

/**
 * @brief Destructor for Node
 *
 */
BSP::Node::~Node() {
    delete (this->left);
    delete (this->right);
    right  = nullptr;
    left   = nullptr;
    parent = nullptr;
}

/**
 * @brief Returns the centre grid node of the grid space encompassed by this node
 * @return Returns the centre point in glm vec2 format
 */

glm::vec2 BSP::Node::getCentrePoint() {
    glm::ivec2 centre;
    centre = (gridTopRight - gridBottomLeft);
    centre.x /= 2;
    centre.y /= 2;
	
    centre += gridBottomLeft;
    return centre;
}
