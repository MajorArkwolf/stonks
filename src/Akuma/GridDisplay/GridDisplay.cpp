#pragma once

#include "GridDisplay.hpp"

#include <algorithm>
#include <iostream>

#include "Stonk/OpenGl.hpp"

namespace GridDisplay {

    void displayGrid(Grid &grid) {
        for (int x = 0; x < grid.gridSizeX; x++) {
            for (int y = 0; y < grid.gridSizeY; y++) {
                glPushMatrix();
                glTranslatef(x - 0.5f * grid.gridSizeX,
                             y - 0.5f * grid.gridSizeY, 0);
                drawSquare(1, 1);
                if (!grid.nodeGrid[x][y].walkable) {
                    glPushMatrix();
                    glColor3f(0.7f, 0.7f, 0.7f);
                    glTranslatef(0.f, 0.f, -0.01f);
                    drawSquare(1.f, 0.f);
                    glColor3f(1.f, 1.f, 1.f);
                    glPopMatrix();
                }
                if (x == grid.selected[0] && y == grid.selected[1]) {
                    glColor3f(1.f, 0.f, 0.f);
                    drawSquare(0.8f, 0.f);
                    glColor3f(1.f, 1.f, 1.f);
                }
                if (x == grid.pathStart[0] && y == grid.pathStart[1]) {
                    glColor3f(0.f, 1.f, 0.f);
                    drawSquare(0.8f, 0.f);
                    glColor3f(1.f, 1.f, 1.f);
                }
                if (x == grid.pathEnd[0] && y == grid.pathEnd[1]) {
                    glColor3f(0.f, 0.f, 1.f);
                    drawSquare(0.8f, 0.f);
                    glColor3f(1.f, 1.f, 1.f);
                }
                glPopMatrix();
            }
        }
    }

    auto displayPath(std::vector<Node *> path, Grid &grid) -> void {
        for (auto n : path) {
            glPushMatrix();
            glTranslatef(n->x - 0.5f * grid.gridSizeX,
                         n->y - 0.5f * grid.gridSizeY, 0);
            glColor3f(1.f, 1.f, 0.f);
            drawSquare(0.7f, 0.f);
            glColor3f(1.f, 1.f, 1.f);
            glPopMatrix();
        }
    }

    auto setGridSquare(glm::ivec2 bottomLeft, glm::ivec2 topRight, Grid &grid,
                       bool walkable) -> void {
        for (auto i = bottomLeft.x; i < topRight.x; i++) {
            for (auto j = bottomLeft.y; j < topRight.y; j++) {
                grid.nodeGrid[i][j].setWalkable(walkable);
            }
        }
    }

    auto loadBSP(Pathing::Grid &grid, int subdivisions) -> void {

        glm::vec2 bottomLeft = {0, 0};
        glm::vec2 topRight   = {grid.gridSizeX, grid.gridSizeY};
        setGridSquare(bottomLeft, topRight, grid, 0);

        auto tree     = BSPTree(grid, subdivisions);
        auto roomList = tree.getRooms();

        for (auto n : roomList) {
            setGridSquare(n->gridBottomLeft, n->gridTopRight, grid, 1);
        }

        std::vector<std::vector<Node *>> paths;
        std::vector<std::vector<std::vector<Node *>>> allPaths;
        Grid blankGrid = Grid(grid.gridSizeX, grid.gridSizeY);

        if (!roomList.empty()) {
            for (auto i = 0, j = 0; i < roomList.size(); i++) {
                auto startPoint = roomList[i]->getCentrePoint();
                j               = i;
                for (j; j < roomList.size(); j++) {
                    auto endPoint  = roomList[j]->getCentrePoint();
                    auto startNode = blankGrid.getNode(startPoint);
                    auto endNode   = blankGrid.getNode(endPoint);
                    paths.push_back(Pathing::Pathfinding::findPath(
                        blankGrid, *startNode, *endNode));
                }
                std::sort(paths.begin(), paths.end(),
                          [](const std::vector<Node *> &a,
                             const std::vector<Node *> &b) {
                              return a.size() < b.size();
                          });
                allPaths.push_back(paths);
                paths.clear();
            }
        }

        for (auto i = 0; i < allPaths.size(); i++) {
            for (auto j = 0; j < allPaths[i].size() && j < 2; j++) {
                for (auto k = 0; k < allPaths[i][j].size(); k++) {
                    glm::vec2 pos = {allPaths[i][j][k]->x, allPaths[i][j][k]->y};
                    grid.getNode(pos)->setWalkable(1);
                }
            }
        }
    }

    void drawSquare(float size, bool wireframe) {
        drawRectangle(size, size, wireframe);
    }

    auto drawRectangle(float _width, float _height, bool wireframe) -> void {
        if (wireframe) {
            glBegin(GL_LINE_LOOP);
        } else {
            glBegin(GL_POLYGON);
        }
        glVertex3f(-0.5f * _width, 0.5f * _height, 0);
        glVertex3f(0.5f * _width, 0.5f * _height, 0);
        glVertex3f(0.5f * _width, -0.5f * _height, 0);
        glVertex3f(-0.5f * _width, -0.5f * _height, 0);
        glEnd();
    }
}
