#include "Floor.hpp"

#include <algorithm>

#include "Pathing/Pathfinding.hpp"

Akuma::Floor::Floor() {
    auto size = defaultGridSize;
    size.x -= 1;
    size.y -= 1;
    this->grid = Grid(defaultGridSize.x, defaultGridSize.y);
    this->tree = BSPTree(size, defaultSubdivisions);
    loadGrid();
}

Akuma::Floor::Floor(glm::uvec2 size, int subdivisions) {
    this->grid = Grid(size.x - 1, size.y - 1);
    this->tree = BSPTree(size, subdivisions);
    loadGrid();
}

Akuma::Floor::Floor(unsigned sizeX, unsigned sizeY, int subdivisions) {
    glm::vec2 size = {sizeX - 1, sizeY - 1};
    this->grid     = Grid(sizeX, sizeY);
    this->tree     = BSPTree(size, subdivisions);
    loadGrid();
}

auto Akuma::Floor::getGridSize() -> glm::uvec2 {
    glm::uvec2 size = {grid.gridSizeX, grid.gridSizeY};
    return size;
}

auto Akuma::Floor::getRoomList() -> std::vector<BSP::Node *> {
    return tree.getRooms();
}

auto Akuma::Floor::getGrid() -> Pathing::Grid {
    return grid;
}

auto Akuma::Floor::getBSP() -> BSP::BSPTree {
    return tree;
}

auto Akuma::Floor::getGridNode(unsigned x, unsigned y) -> Pathing::Node * {
    return &grid.nodeGrid[x][y];
}

auto Akuma::Floor::loadGrid() -> void {

    glm::vec2 bottomLeft = {0, 0};
    glm::vec2 topRight   = {grid.gridSizeX, grid.gridSizeY};
    setGridSquare(bottomLeft, topRight, 0);

    auto roomList = tree.getRooms();

    for (auto n : roomList) {
        setGridSquare(n->gridBottomLeft, n->gridTopRight, 1);
    }

    std::vector<std::vector<Pathing::Node *>> paths;
    std::vector<std::vector<std::vector<Pathing::Node *>>> allPaths;
    Grid blankGrid = Grid(grid.gridSizeX, grid.gridSizeY);

    if (!roomList.empty()) {
        for (unsigned i = 0, j = 0; i < roomList.size(); i++) {
            auto startPoint = roomList[i]->getCentrePoint();
            j               = i;
            for (; j < roomList.size(); j++) {
                auto endPoint  = roomList[j]->getCentrePoint();
                auto startNode = blankGrid.getNode(startPoint);
                auto endNode   = blankGrid.getNode(endPoint);
                paths.push_back(Pathing::Pathfinding::findPath(
                    blankGrid, *startNode, *endNode, 0));
            }
            std::sort(paths.begin(), paths.end(),
                      [](const std::vector<Pathing::Node *> &a,
                         const std::vector<Pathing::Node *> &b) {
                          return a.size() < b.size();
                      });
            allPaths.push_back(paths);
            paths.clear();
        }
    }

    for (unsigned i = 0; i < allPaths.size(); i++) {
        for (unsigned j = 0; j < allPaths[i].size() && j < 2; j++) {
            for (unsigned k = 0; k < allPaths[i][j].size(); k++) {
                glm::uvec2 pos = {allPaths[i][j][k]->x, allPaths[i][j][k]->y};
                grid.getNode(pos)->setWalkable(1);
            }
        }
    }
}

auto Akuma::Floor::setGridSquare(glm::uvec2 bottomLeft, glm::uvec2 topRight,
                                 bool walkable) -> void {
    for (auto i = bottomLeft.x; i < topRight.x; i++) {
        for (auto j = bottomLeft.y; j < topRight.y; j++) {
            grid.nodeGrid[static_cast<size_t>(i)][static_cast<size_t>(j)].setWalkable(
                walkable);
        }
    }
}
