#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../Akuma/Floor.hpp"
#include "../Akuma/Pathing/Pathfinding.hpp"
#include "Components.hpp"
#include "../Akuma/RNG/Dice.hpp"
#include "StatComponent.hpp"
#include "PositionComponent.hpp"

/* This will need to handle input to the player */
class EnemyComponent : public Component {
  public:
    enum Facing { N, NE, E, SE, S, SW, W, NW };
    EnemyComponent()  = default;
    ~EnemyComponent() = default;
    void init() {}
    void update() {
        if (this->entity->hasComponent<TurnComponent>()) {
            if (this->entity->getComponent<TurnComponent>().CheckTurn()) {
				//combatCheck
                moveAction();




                //facing = facingBuffer;
                //setTurnAngle();
            }
            
        }
    }
    void draw() {}
    void setFacing(Facing newFace) {
        facingBuffer = newFace;
    }

    void setFacing(int i) {
        switch (i) {
            case 0: {
                facingBuffer = N;
                break;
            }
            case 1: {
                facingBuffer = NE;
                break;
            }
            case 2: {
                facingBuffer = E;
                break;
            }
            case 3: {
                facingBuffer = SE;
                break;
            }
            case 4: {
                facingBuffer = S;
                break;
            }
            case 5: {
                facingBuffer = SW;
                break;
            }
            case 6: {
                facingBuffer = W;
                break;
            }
            case 7: {
                facingBuffer = NW;
                break;
            }
            default: {
                facingBuffer = N;
                break;
            }
        }
    }

	void SetPlayerTarget(Entity *currentPlayer) {
        player = currentPlayer;
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

  private:
    Dice diceroller;
    int turn            = 0;
    Facing facingBuffer = N;
    Facing facing       = N;
    bool lockedToPlayer = false;
    Entity *player      = nullptr;

    void determineFacingDirection(Pathing::Node* nextNode) {
        auto *currentNode =
            this->entity->getComponent<PositionComponent>().getNode();
        int x = nextNode->x - currentNode->x;
        int y = nextNode->y - currentNode->y;

        if (x = -1) {
            if (y = -1) {
                facingBuffer = SW;
            } else if (y = 0) {
                facingBuffer = W;
            } else if (y = 1) {
                facingBuffer = NW;
            }
        } else if (x = 0) {
            if (y = -1) {
                facingBuffer = S;
            } else if (y = 0) {
                facingBuffer = N; // default always face north
            } else if (y = 1) {
                facingBuffer = W;
            }
        } else if (x = 1) {
            if (y = -1) {
                facingBuffer = SW;
            } else if (y = 0) {
                facingBuffer = E;
            } else if (y = 1) {
                facingBuffer = NE;
            }
        } else {
            std::cout << "Values were out! X= " << x << "Y= " << y
                      << '\n'; // Debug code, remove later
        }
    }

	auto setTurnAngle() -> void {
        if (this->entity->hasComponent<PositionComponent>()) {
            switch (facing) {
                case N:
                    this->entity->getComponent<PositionComponent>().setRotationN();
                    break;
                case NE:
                    this->entity->getComponent<PositionComponent>().setRotationNE();
                    break;
                case E:
                    this->entity->getComponent<PositionComponent>().setRotationE();
                    break;
                case SE:
                    this->entity->getComponent<PositionComponent>().setRotationSE();
                    break;
                case S:
                    this->entity->getComponent<PositionComponent>().setRotationS();
                    break;
                case SW:
                    this->entity->getComponent<PositionComponent>().setRotationSW();
                    break;
                case W:
                    this->entity->getComponent<PositionComponent>().setRotationW();
                    break;
                case NW:
                    this->entity->getComponent<PositionComponent>().setRotationNW();
                    break;
            }
        }
	}

	void detectPlayer() {
        if (this->entity->hasComponent<StatComponent>()) {
            auto distance = DistanceBetween();                
            auto myIntel =
                this->entity->getComponent<StatComponent>().getIntelligenceMod();
            auto playerStealth =
                player->getComponent<StatComponent>().getDexterityMod();
            if (diceroller.Roll(1, 20) + myIntel >
                diceroller.Roll(1, 20) + playerStealth + distance) {
                lockedToPlayer = true;
                std::cout << "Player Detected" << '\n';
			}
		}
	}

	auto DistanceBetween() -> unsigned int {
        Grid grid =
            this->entity->getComponent<FloorComponent>().getFloor()->getGrid();
        auto *myNode = this->entity->getComponent<PositionComponent>().getNode();
        auto *playerNode = player->getComponent<PositionComponent>().getNode();
        auto pathToPlayer =
            Pathing::Pathfinding::findPath(grid, *myNode, *playerNode, true);
        return pathToPlayer.size();
	}

	auto goToPlayer() -> void {
        if (this->entity->hasComponent<MoveComponent>()) {
            Grid grid =
                this->entity->getComponent<FloorComponent>().getFloor()->getGrid();
            auto *myNode =
                this->entity->getComponent<PositionComponent>().getNode();
            auto *playerNode = player->getComponent<PositionComponent>().getNode();
            //Pathing::Pathfinding::findPath(grid, *myNode, *playerNode, true).at(1);
            if (true) {
                this->entity->getComponent<MoveComponent>().moveEntityToNode(
                    Pathing::Pathfinding::findPath(grid, *myNode, *playerNode, true)
                        .at(1));
			}
		}
	}

	auto moveAction() -> void {
        if (lockedToPlayer) {
            //goToPlayer();
		} else {
            detectPlayer();            
		}
	}
};
