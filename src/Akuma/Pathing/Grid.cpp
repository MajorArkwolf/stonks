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

Grid::Grid(unsigned _gridSizeX, unsigned _gridSizeY) {
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
    for (unsigned x = 0; x < gridSizeX; x++) {
        for (unsigned y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].gCost  = 0;
            nodeGrid[x][y].hCost  = 0;
            nodeGrid[x][y].parent = nullptr;
        }
    }
}

void Pathing::Grid::resetGrid() {
    for (unsigned x = 0; x < gridSizeX; x++) {
        for (unsigned y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].gCost    = 0;
            nodeGrid[x][y].hCost    = 0;
            nodeGrid[x][y].walkable = 0;
        }
    }
}

Node *Pathing::Grid::getNode(glm::uvec2 pos) {
    return &nodeGrid[pos.x][pos.y];
}

void Grid::resizeGrid(unsigned _gridSizeX, unsigned _gridSizeY) {
    nodeGrid.resize(_gridSizeX);

    for (auto &array : nodeGrid) {
        array.resize(_gridSizeY);
    }

    gridSizeX = _gridSizeX;
    gridSizeY = _gridSizeY;

    for (unsigned x = 0; x < gridSizeX; x++) {
        for (unsigned y = 0; y < gridSizeY; y++) {
            nodeGrid[x][y].x = x;
            nodeGrid[x][y].y = y;
        }
    }
}

vector<Node *> Grid::getNeighbours(Node &node) {
    return this->getNeighbours(node, 1, 1);
}

vector<Node *> Grid::getNeighbours(Node &node, int radius, bool oct) {
    vector<Node *> newList;
    long long int nodeX = node.x;
    long long int nodeY = node.y;

    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x != 0 || y != 0) {
                if (!(nodeX + x <= -1 || nodeX + x >= gridSizeX ||
                      nodeY + y <= -1 || nodeY + y >= gridSizeY)) {
                    if (!oct) {
                        if ((y == 0 || x == 0)) {
                            newList.push_back(&nodeGrid[static_cast<unsigned>(
                                nodeX + x)][static_cast<unsigned>(nodeY + y)]);
                        }
                    } else {
                        newList.push_back(&nodeGrid[static_cast<unsigned>(
                            nodeX + x)][static_cast<unsigned>(nodeY + y)]);
                    }
                }
            }
        }
    }

    return newList;
}
