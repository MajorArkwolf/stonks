#pragma once

#include "Stonk\Pathing\Grid.hpp"
#include "Node.hpp"

namespace BSP {
    class BSPTree {
      public:
        BSPTree(Pathing::Grid &grid, int subdivisions);
        BSPTree();
        ~BSPTree();

        void deleteTree();
        void reGen(Pathing::Grid &grid, int subdivisions);

        std::vector<Node *> getRooms();

      private:
        Node *root = nullptr;

        void populateTree(BSP::Node *node, int subdivisions);
        bool splitNode(BSP::Node *node);

        int traverse(BSP::Node *node);
        int traverse(BSP::Node *node, std::vector<Node *> &list);
    };
};
