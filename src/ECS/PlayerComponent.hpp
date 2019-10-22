#pragma once

#include "../Akuma/Floor.hpp"
#include "ECS.hpp"
#include "TurnComponent.hpp"
#include "PositionComponent.hpp"
#include "MoveComponent.hpp"

/* This will need to handle input to the player */
class PlayerComponent : public Component {
  public:
    enum class Facing { N, NE, E, SE, S, SW, W, NW };
    PlayerComponent()  = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {
        if (this->entity->hasComponent<TurnComponent>()) {
            if (this->entity->getComponent<TurnComponent>().CheckTurn()) {
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
            issueMovementToEntity();
        }
    }
    void draw() {}
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
        if (this->entity->getComponent<TurnComponent>().CheckTurn()) {
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

    void moveEntity() {
        if (this->entity->getComponent<TurnComponent>().CheckTurn()) {
            if (!issueMovement) {
                issueMovement = true;
            }
        }
    }

  private:
    bool issueMovement  = false;
    int turn            = 0;
    Facing facingBuffer = Facing::N;
    Facing facing       = Facing::N;

    void issueMovementToEntity() {
        if (issueMovement) {
            Floor *floor = this->entity->getComponent<FloorComponent>().getFloor();
            Pathing::Node *currentNode =
                this->entity->getComponent<PositionComponent>().getNode();
            auto facingNode = getNodeFacing(currentNode->x, currentNode->y);
            auto newNode = floor->getGridNode(facingNode);
            if (newNode->walkable) {
                this->entity->getComponent<MoveComponent>().moveEntityToNode(newNode);

			}
            issueMovement = false;
        }
    }

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
};
