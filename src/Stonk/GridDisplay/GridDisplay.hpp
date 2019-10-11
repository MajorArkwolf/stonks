#pragma once

#include <glm/vec2.hpp>

#include "..\Pathing\Grid.hpp"
#include "..\Pathing\Pathfinding.hpp"
#include "..\ProceduralGen\BSP\BSP.hpp"

using BSP::BSPTree;
using Pathing::Grid;
using Pathing::Node;

namespace GridDisplay {

    auto drawRectangle(float width, float height, bool wireframe) -> void;
    auto drawSquare(float size, bool wireframe) -> void;
    auto displayGrid(Grid &grid) -> void;
    auto displayPath(std::vector<Node *> path, Grid &grid) -> void;
    auto setGridSquare(glm::ivec2 bottomLeft, glm::ivec2 topRight, Grid &grid,
                       bool walkable) -> void;
    auto loadBSP(Pathing::Grid &grid, int subdivisions) -> void;

};
