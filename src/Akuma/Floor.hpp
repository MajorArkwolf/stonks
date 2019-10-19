#pragma once

#include "Akuma/ProceduralGen/BSP/BSP.hpp"

using BSP::BSPTree;
using Pathing::Grid;

/**
 * @class Floor
 * @brief Class representing a floor within the Akuma game
 */
class Floor {
  public:
    Floor();
    Floor(glm::uvec2 size, int subdivisions);
    Floor(unsigned sizeX, unsigned sizeY, int subdivisions);
    auto getGridSize() -> glm::uvec2;
    auto getRoomList() -> std::vector<BSP::Node *>;
    auto getGrid() -> Pathing::Grid &;
    auto getBSP() -> BSP::BSPTree &;
    auto getGridNode(unsigned x, unsigned y) -> Pathing::Node *;
    auto setGridSquare(glm::uvec2 bottomLeft, glm::uvec2 topRight, bool walkable)
        -> void;
    auto getNeighbours(Pathing::Node &_node) -> vector<Pathing::Node *>;
    auto findPath(Pathing::Node &startNode, Pathing::Node &endNode)
        -> std::vector<Pathing::Node *>;
    auto regen() -> void;

  private:
    /// The grid representation of the room
    Pathing::Grid grid;

    /// The BSP tree that gets loaded into the grid
    BSP::BSPTree tree;

    auto loadGrid() -> void;

    /// The default size of the grid to create
    const glm::uvec2 defaultGridSize = {30, 30};

    /// The default amount of times to subdivide the grid
    const int defaultSubdivisions = 3;
};
