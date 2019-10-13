#pragma once

#include "Akuma/Pathing/Grid.hpp"
#include "Node.hpp"

namespace BSP {
    class BSPTree {
      public:
        BSPTree(glm::vec2 size, int subdivisions);
        BSPTree();
        ~BSPTree();
        const BSPTree& operator=(const BSPTree &rhs);
        BSPTree(const BSPTree & other);

        void deleteTree();
        void reGen(glm::vec2 size, int subdivisions);

        std::vector<Node *> getRooms();

      private:
        Node *root = nullptr;

        void populateTree(BSP::Node *node, int subdivisions);
        bool splitNode(BSP::Node *node);

        int traverse(BSP::Node *node);
        int traverse(BSP::Node *node, std::vector<Node *> &list);
        void copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot);
    };
};
