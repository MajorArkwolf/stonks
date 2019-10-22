#pragma once

#include "../Akuma/Floor.hpp"
#include "Akuma\Akuma.hpp"
#include "CombatComponent.hpp"
#include "ECS.hpp"
#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "TurnComponent.hpp"

/* This will need to handle input to the player */
class PlayerComponent : public Component {
  public:
    enum class Facing { N, NE, E, SE, S, SW, W, NW };
    PlayerComponent()  = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {
        if (this->entity->hasComponent<TurnComponent>()) {
            if (this->entity->getComponent<TurnComponent>().checkTurn()) {
                facing = facingBuffer;
            }
            if (this->entity->hasComponent<PositionComponent>()) {
                switch (facing) {
                    case Facing::N:
                        this->entity->getComponent<PositionComponent>().setRotationN();
                        break;
                    case Facing::NE:
                        this->entity->getComponent<PositionComponent>().setRotationNE();
                        break;
                    case Facing::E:
                        this->entity->getComponent<PositionComponent>().setRotationE();
                        break;
                    case Facing::SE:
                        this->entity->getComponent<PositionComponent>().setRotationSE();
                        break;
                    case Facing::S:
                        this->entity->getComponent<PositionComponent>().setRotationS();
                        break;
                    case Facing::SW:
                        this->entity->getComponent<PositionComponent>().setRotationSW();
                        break;
                    case Facing::W:
                        this->entity->getComponent<PositionComponent>().setRotationW();
                        break;
                    case Facing::NW:
                        this->entity->getComponent<PositionComponent>().setRotationNW();
                        break;
                }
            }
            commandExecution();
        }
    }
    void draw() {
        if (this->entity->hasComponent<PositionComponent>()) {

            if (this->entity->hasComponent<FloorComponent>()) {

                if (this->entity->hasComponent<TurnComponent>()) {

                    Floor *floor =
                        this->entity->getComponent<FloorComponent>().getFloor();
                    Pathing::Node *currentNode =
                        this->entity->getComponent<PositionComponent>().getNode();
                    auto gridSize = floor->getGridSize();
                    std::vector<Pathing::Node *> playerSurroundings =
                        floor->getNeighbours(*currentNode);

                    glLineWidth(3);
                    glPushMatrix();
                    glTranslatef(gridSize.x / 2, 0, (gridSize.y / 2));
                    for (auto n : playerSurroundings) {
                        if (n->walkable) {

                            glPushMatrix();
                            glTranslatef(n->x - 0.5f * gridSize.x, 0,
                                         (n->y - 0.5f * gridSize.y));
                            glPushMatrix();
                            glTranslatef(0.f, 0.04f, 0.f);
                            glEnable(GL_COLOR_MATERIAL);
                            glColor3f(1, 1, 0);

                            drawSquare(1, 1);
                            glColor3f(1, 1, 1);
                            glDisable(GL_COLOR_MATERIAL);
                            glPopMatrix();

                            glPopMatrix();
                        }
                    }
                    glPopMatrix();
                    glLineWidth(1);
                }
            }
        }
    }
    void setFacing(Facing newFace) {
        facingBuffer = newFace;
    }

    void setFacing(int i) {
        switch (i) {
            case 0: {
                facingBuffer = Facing::N;
                break;
            }
            case 1: {
                facingBuffer = Facing::NE;
                break;
            }
            case 2: {
                facingBuffer = Facing::E;
                break;
            }
            case 3: {
                facingBuffer = Facing::SE;
                break;
            }
            case 4: {
                facingBuffer = Facing::S;
                break;
            }
            case 5: {
                facingBuffer = Facing::SW;
                break;
            }
            case 6: {
                facingBuffer = Facing::W;
                break;
            }
            case 7: {
                facingBuffer = Facing::NW;
                break;
            }
            default: {
                facingBuffer = Facing::N;
                break;
            }
        }
    }

    void turnEntity(int i) {
        if (this->entity->getComponent<TurnComponent>().checkTurn()) {
            if (turn + i > 7) {
                turn = 0;
            } else if (turn + i < 0) {
                turn = 7;
            } else {
                turn += i;
            }
            setFacing(turn);
        }
    }

    void issueAction() {
        if (this->entity->getComponent<TurnComponent>().checkTurn()) {
            if (!issuedAction) {
                issuedAction = true;
            }
        }
    }
    void skipTurn() {
        if (this->entity->getComponent<TurnComponent>().checkTurn()) {
            this->entity->getComponent<TurnComponent>().endYourTurn();
        }
    }

  private:
    bool issuedAction   = false;
    int turn            = 0;
    Facing facingBuffer = Facing::N;
    Facing facing       = Facing::N;

    glm::uvec2 getNodeFacing(unsigned int x, unsigned int y) {
        glm::uvec2 newNode = {x, y};
        switch (turn) {
            case 0: {
                newNode.y++;
                break;
            }
            case 1: {
                newNode.x++;
                newNode.y++;
                break;
            }
            case 2: {
                newNode.x++;
                break;
            }
            case 3: {
                newNode.x++;
                newNode.y--;
                break;
            }
            case 4: {
                newNode.y--;
                break;
            }
            case 5: {
                newNode.x--;
                newNode.y--;
                break;
            }
            case 6: {
                newNode.x--;
                break;
            }
            case 7: {
                newNode.x--;
                newNode.y++;
                break;
            }
            default: {
                newNode.y++;
                break;
            }
        }
        return newNode;
    }

    void commandExecution() {
        if (issuedAction) {
            Floor *floor = this->entity->getComponent<FloorComponent>().getFloor();
            Pathing::Node *currentNode =
                this->entity->getComponent<PositionComponent>().getNode();
            auto facingNode = getNodeFacing(currentNode->x, currentNode->y);
            auto newNode    = floor->getGridNode(facingNode);
            if (newNode->occupied) {
                if (true /*check hostile enemy*/) {
                    issuedAction = false;
                    this->entity->getComponent<CombatComponent>().attackEntity(
                        newNode->occupant);
                }
            } else if (newNode->walkable) {
                this->entity->getComponent<MoveComponent>().moveEntityToNode(newNode);
                issuedAction = false;
            }
        }
    }
    /**
     * @brief Draws a square on screen matching the given parameters
     * @param size The size of the square to create
     * @param wireframe Whether to draw a wireframe square or a polygon
     */
    auto drawSquare(float size, bool wireframe) -> void {
        drawRectangle(size, size, wireframe);
    }

    /**
     * @brief Draws a rectangle on screen matching the given parameters
     * @param _height The height of the rectangle to create
     * @param _width The width of the rectangle to create
     * @param wireframe Whether to draw a wireframe or polygon
     */
    auto drawRectangle(float _width, float _height, bool wireframe) -> void {
        if (wireframe) {
            glBegin(GL_LINE_LOOP);
        } else {
            glBegin(GL_POLYGON);
        }
        glVertex3f(-0.5f * _width, 0, 0.5f * _height);
        glVertex3f(0.5f * _width, 0, 0.5f * _height);
        glVertex3f(0.5f * _width, 0, -0.5f * _height);
        glVertex3f(-0.5f * _width, 0, -0.5f * _height);
        glEnd();
    }
};
