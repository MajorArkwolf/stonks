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
        Grid(int _gridSizeX, int _gridSizeY);

        Node &getStartNode();
        Node &getEndNode();
        Node &getSelectedNode();

        void resetGridCosts();
        void resetGrid();
        Node *getNode(glm::ivec2 pos);

        void resizeGrid(int x, int y);

        /// 2Dimensional Vector of nodes
        vector<vector<Node>> nodeGrid;

        /// The number of columns of nodes
        int gridSizeX = 20;

        /// The number of rows of nodes
        int gridSizeY = 20;

        int selected[2]  = {0, 0};
        int pathStart[2] = {0, 0};
        int pathEnd[2]   = {0, 0};

        vector<Node *> getNeighbours(Node &_node);
        vector<Node *> getNeighbours(Node &_node, int radius);
    };
};
