#pragma once
#include <vector>

#include "Node.hpp"
#include "glm/vec2.hpp"

using std::vector;

namespace Pathing {
    class Grid {
      private:
        void initialiseSelections();

      public:
        Grid();
        Grid(unsigned _gridSizeX, unsigned _gridSizeY);

        Node &getStartNode();
        Node &getEndNode();
        Node &getSelectedNode();

        void resetGridCosts();
        void resetGrid();
        Node *getNode(glm::uvec2 pos);

        void resizeGrid(unsigned x, unsigned y);

        /// 2Dimensional Vector of nodes
        vector<vector<Node>> nodeGrid;

        /// The number of columns of nodes
        unsigned gridSizeX = 20;

        /// The number of rows of nodes
        unsigned gridSizeY = 20;

        unsigned selected[2]  = {0, 0};
        unsigned pathStart[2] = {0, 0};
        unsigned pathEnd[2]   = {0, 0};

        vector<Node *> getNeighbours(Node &_node);
        vector<Node *> getNeighbours(Node &_node, int radius, bool oct);
    };
};
