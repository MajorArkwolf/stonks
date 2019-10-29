#pragma once

#include "Akuma/Pathing/Grid.hpp"
#include "Node.hpp"

/**
 * @namespace BSP
 * @brief A namespace for the Binary Space Partitioning Tree
 */
namespace BSP {

    /**
     * @class BSPTree
     * @brief A class used partition a rectangle into semi-randomly size partitions
     * Uses a binary space partitioning algorithm to continually subdivide partitions until a criteria is met
     */
    class BSPTree {
      public:
        BSPTree();
        BSPTree(glm::uvec2 size, int subdivisions);
        ~BSPTree();
        BSPTree(const BSPTree &other);
        const BSPTree &operator=(const BSPTree &rhs);

        void reGen(glm::vec2 size, int subdivisions);

        std::vector<Node *> getRooms();

      private:
        /// Root node of tree, initialised to nullptr
        Node *root = nullptr;

        void deleteTree();
        void copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot);

        void populateTree(BSP::Node *node, int subdivisions);
        bool splitNode(BSP::Node *node);

        int traverse(BSP::Node *node);
        int traverse(BSP::Node *node, std::vector<Node *> &list);
    };
};
