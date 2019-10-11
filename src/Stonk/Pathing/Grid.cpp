#include "Grid.hpp"

using Pathing::Grid;
using Pathing::Node;

void Pathing::Grid::initialiseSelections() {
    selected[0]  = 1;
    selected[1]  = 1;
    pathStart[0] = 0;
    pathStart[1] = 0;
    pathEnd[0]   = gridSizeX - 1;
    pathEnd[1]   = gridSizeY - 1;
}

Grid::Grid() {
    this->resizeGrid(this->gridSizeX, this->gridSizeY);
    initialiseSelections();
}

Grid::Grid(int _gridSizeX, int _gridSizeY) {
    this->resizeGrid(_gridSizeX, _gridSizeY);
    initialiseSelections();
}

Node &Pathing::Grid::getStartNode() {
    return this->nodeGrid[pathStart[0]][pathStart[1]];
}

Node &Pathing::Grid::getEndNode() {
    return this->nodeGrid[pathEnd[0]][pathEnd[1]];
}

Node &Pathing::Grid::getSelectedNode() {
    return this->nodeGrid[selected[0]][selected[1]];
}

void Pathing::Grid::resetGridCosts() {
    for (auto x = 0; x < gridSizeX; x++) {
        for (auto y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].gCost  = 0;
            nodeGrid[x][y].hCost  = 0;
            nodeGrid[x][y].parent = nullptr;
        }
    }
}

void Pathing::Grid::resetGrid() {
    for (auto x = 0; x < gridSizeX; x++) {
        for (auto y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].gCost    = 0;
            nodeGrid[x][y].hCost    = 0;
            nodeGrid[x][y].walkable = 0;
        }
    }
}

Node *Pathing::Grid::getNode(glm::ivec2 pos) {
    return &nodeGrid[pos.x][pos.y];
}

void Grid::resizeGrid(int _gridSizeX, int _gridSizeY) {
    nodeGrid.resize(_gridSizeX);

    for (auto &array : nodeGrid) {
        array.resize(_gridSizeY);
    }

    gridSizeX = _gridSizeX, gridSizeY = _gridSizeY;

    for (auto x = 0; x < gridSizeX; x++) {
        for (auto y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].x = x;
            nodeGrid[x][y].y = y;
        }
    }
}

vector<Node *> Grid::getNeighbours(Node &node) {
    return this->getNeighbours(node, 1);
}

vector<Node *> Grid::getNeighbours(Node &node, int radius) {
    vector<Node *> newList;
    long long int nodeX = node.x;
    long long int nodeY = node.y;

    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x != 0 || y != 0) {
                if (!(nodeX + x <= -1 || nodeX + x >= gridSizeX ||
                      nodeY + y <= -1 || nodeY + y >= gridSizeY)) {
                    if ((y == 0 || x == 0)) {

                        newList.push_back(&nodeGrid[nodeX + x][nodeY + y]);
                    }
                }
            }
        }
    }

    return newList;
}
