#include "Floor.hpp"

#include <algorithm>

#include "Pathing/Pathfinding.hpp"

/**
 * @brief Floor default constructor
 * Automatically initalises a new grid + bsp and loads the bsp into the grid using the default parameters
 */
Floor::Floor() {
    auto size = defaultGridSize;
    size.x -= 1;
    size.y -= 1;
    this->grid = Grid(defaultGridSize.x, defaultGridSize.y);
    this->tree = BSPTree(size, defaultSubdivisions);
    loadGrid();
}

/**
 * @brief Floor default constructor
 * Automatically initalises a new grid + bsp and loads the bsp into the grid using the passed in parameters
 * @param size An glm unsigned vec2 containing the size of the grid to create
 * @param subdivisions The number of times to subdivide the grid, 2^subdivisions = number of rooms
 */
Floor::Floor(glm::uvec2 size, int subdivisions) {
    this->grid = Grid(size.x - 1, size.y - 1);
    this->tree = BSPTree(size, subdivisions);
    loadGrid();
}

/**
 * @brief Floor default constructor
 * Automatically initalises a new grid + bsp and loads the bsp into the grid using the passed in parameters
 * @param sizeX The X size of the grid to create
 * @param sizeY The Y size of the grid to create
 * @param subdivisions The number of times to subdivide the grid, 2^subdivisions = number of rooms
 */
Floor::Floor(unsigned sizeX, unsigned sizeY, int subdivisions) {
    glm::vec2 size = {sizeX - 1, sizeY - 1};
    this->grid     = Grid(sizeX, sizeY);
    this->tree     = BSPTree(size, subdivisions);
    loadGrid();
}

/**
 * @brief Returns the size of the grid in glm unsigned vec2 form
 * @return A glm unsigned vec2 containing the grid size
 */
auto Floor::getGridSize() -> glm::uvec2 {
    glm::uvec2 size = {grid.gridSizeX, grid.gridSizeY};
    return size;
}

/**
 * @brief Returns a vector containing the BSP nodes of each room, the BSP nodes
 * contain the bottomLeft and topRight grid space positions of each room
 * @return A vector containing all rooms in node form
 */
auto Floor::getRoomList() -> std::vector<BSP::Node *> {
    return tree.getRooms();
}

/**
 * @brief Returns a reference to the grid
 * @return A reference to the grid
 */
auto Floor::getGrid() -> Pathing::Grid & {
    return grid;
}

/**
 * @brief Returns a reference to the BSP tree
 * @return A reference to the BSP tree
 */
auto Floor::getBSP() -> BSP::BSPTree & {
    return tree;
}

/**
 * @brief Returns the grid node at the given grid coordinates
 * @return The grid node at the given coordinates
 * @param x X coord
 * @param y Y coord
 * If coordinates out of bounds, returns node at (0,0)
 */
auto Floor::getGridNode(unsigned x, unsigned y) -> Pathing::Node * {
    auto size = getGridSize();
    if (x > size.x || y > size.y) {
        return &grid.nodeGrid[0][0];
    }
    return &grid.nodeGrid[x][y];
}

/**
 * @brief Returns the grid node at the given grid coordinates
 * @return The grid node at the given coordinates
 * If coordinates out of bounds, returns node at (0,0)
 * @param nodeCoords A vector containing the node coordinates
 */
auto Floor::getGridNode(glm::uvec2 nodeCoords) -> Pathing::Node * {
    auto x    = nodeCoords.x;
    auto y    = nodeCoords.y;
    auto size = getGridSize();
    if (x > size.x || y > size.y) {
        return &grid.nodeGrid[0][0];
    }
    return &grid.nodeGrid[x][y];
}

/**
 * @brief Reads from the BSP tree and sets grid values accordingly
 */
auto Floor::loadGrid() -> void {

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

/**
 * @brief Sets a square within the grid to a the passed in walkable value
 * @param bottomLeft The bottom left coordinate of the square to set
 * @param topRight The top right coordinate of the square to set
 * @param walkable The walkable value to set the given grid subset to
 */
auto Floor::setGridSquare(glm::uvec2 bottomLeft, glm::uvec2 topRight,
                          bool walkable) -> void {
    for (auto i = bottomLeft.x; i < topRight.x; i++) {
        for (auto j = bottomLeft.y; j < topRight.y; j++) {
            grid.nodeGrid[static_cast<size_t>(i)][static_cast<size_t>(j)].setWalkable(
                walkable);
        }
    }
}
/**
 * @brief Returns all neighbours of a given node given they exist
 * @return A vector of all neighbours
 * @param _node The node to return the neighbours of
 */
auto Floor::getNeighbours(Pathing::Node &_node) -> vector<Pathing::Node *> {
    return grid.getNeighbours(_node);
}

/**
 * @brief Returns the path starting and ending at the given nodes
 * @return A vector of pointers to nodes symbolising the path, from start to finish
 * @param startNode The node to start from
 * @param endNode The node to path to
 */
auto Floor::findPath(Pathing::Node &startNode, Pathing::Node &endNode)
    -> std::vector<Pathing::Node *> {
    return Pathing::Pathfinding::findPath(grid, startNode, endNode, 1);
}

/**
 * @brief Regenerates the current floor based on default parameters
 */
auto Floor::regen() -> void {
    auto size = defaultGridSize;
    size.x -= 1;
    size.y -= 1;
    this->tree = BSPTree(size, defaultSubdivisions);
    grid.resetGrid();
    loadGrid();
}

/**
 * @brief Regenerates the current floor based on given parameters
 * @param size The size of the room to create
 * @param subdivisions The amount of times to subdivide the room
 */
auto Floor::regen(glm::uvec2 size, int subdivisions) -> void {
    this->grid = Grid(size.x, size.y);
    size.x -= 1;
    size.y -= 1;
    this->tree = BSPTree(size, subdivisions);
    grid.resetGrid();
    loadGrid();

}
