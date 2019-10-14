#pragma once

#include "Akuma/ProceduralGen/BSP/BSP.hpp"

using BSP::BSPTree;
using Pathing::Grid;

namespace Akuma {
    class Floor {
      public:
        Floor();
        Floor(glm::uvec2 size, int subdivisions);
        Floor(unsigned sizeX, unsigned sizeY, int subdivisions);
        auto getGridSize() -> glm::uvec2;
        auto getRoomList() -> std::vector<BSP::Node *>;
        auto getGrid() -> Pathing::Grid;
        auto getBSP() -> BSP::BSPTree;
        auto getGridNode(unsigned x, unsigned y) -> Pathing::Node *;
        auto setGridSquare(glm::uvec2 bottomLeft, glm::uvec2 topRight,
                           bool walkable) -> void;

      private:
        Pathing::Grid grid;
        BSP::BSPTree tree;

        auto loadGrid() -> void;

        const glm::uvec2 defaultGridSize   = {30, 30};
        const int defaultSubdivisions = 3;
    };
};
