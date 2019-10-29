#pragma once
#include "glm/vec2.hpp"

/**
 * @namespace BSP
 * @brief A namespace for the Binary Space Partitioning Tree
 */
namespace BSP {

    /**
     * @class Node
     * @brief A node symbolising a particular subdivision of a grid space
     * If the node has no children, then it is regarded as a room within the grid
     */
    class Node {
      public:
        /**
         * @brief Default constructor for node, set to default
         */
        Node() = default;
        Node(glm::uvec2 bottomLeft, glm::uvec2 topRight);
        ~Node();

        glm::ivec2 getCentrePoint();

        /// Pointer to parent node, root has parent == nullptr
        Node *parent = nullptr;

        /// Pointer to left child node
        Node *left = nullptr;

        /// Pointer to right child node
        Node *right = nullptr;

        /// The top right coordinate of the grid space encompassed by this node
        glm::vec2 gridTopRight = {0, 0};

        /// The bottom left coordinate of the grid space encompassed by this node
        glm::vec2 gridBottomLeft = {0, 0};

        /// The depth in the tree of this particular node
        int depth = 0;
    };
};
