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
                // combatCheck
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

	void updateFacing() {
        facing = facingBuffer;
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

	//This function is scuffed and wont face the player all the time, cant debug
	//as I dont have enough data to see what the entities are actually doing.
    void determineFacingDirection(Pathing::Node* nextNode) {
        auto *currentNode =
            this->entity->getComponent<PositionComponent>().getNode();
        int x = nextNode->x - currentNode->x;
        int y = nextNode->y - currentNode->y;
        //int x = currentNode->x - nextNode->x;
        //int y = currentNode->y - nextNode->y;

        if (x == -1) {
            if (y == -1) {
                facingBuffer = SW;
            } else if (y == 0) {
                facingBuffer = W;
            } else if (y == 1) {
                facingBuffer = N;
            }
        } else if (x == 0) {
            if (y == -1) {
                facingBuffer = S;
            } else if (y == 0) {
                facingBuffer = NW; // default always face north
            } else if (y == 1) {
                facingBuffer = E;
            }
        } else if (x == 1) {
            if (y == -1) {
                facingBuffer = SW;
            } else if (y == 0) {
                facingBuffer = E;
            } else if (y == 1) {
                facingBuffer = NE;
            }
        } else {
            std::cout << "Values were out! X= " << x << "Y= " << y
                      << '\n'; // Debug code, remove later
        }
        std::cout << "x= " << x << " y= " << y << " direction= " << facingBuffer
                  << '\n';
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
        return Pathing::Pathfinding::findPath(
                   this->entity->getComponent<FloorComponent>().getFloor()->getGrid(),
                   *this->entity->getComponent<PositionComponent>().getNode(),
                   *player->getComponent<PositionComponent>().getNode(), true).size();
	}

	auto goToPlayer() -> void {
        auto *playerNode = player->getComponent<PositionComponent>().getNode();
        if (this->entity->hasComponent<MoveComponent>()) {
            auto e = Pathing::Pathfinding::findPath(
                this->entity->getComponent<FloorComponent>().getFloor()->getGrid(),
                *this->entity->getComponent<PositionComponent>().getNode(),
                *playerNode, true);
            if (e.size() > 1) {
                if (e.at(0) != playerNode) {
                    determineFacingDirection(e.at(0));
                    updateFacing();
                    setTurnAngle();
                    if (!e.at(0)->occupied) {
                        this->entity->getComponent<MoveComponent>().moveEntityToNode(
                            e.at(0));
                    }
                }                
			}
		}
	}
	auto moveAction() -> void {
        if (lockedToPlayer) {
            goToPlayer();
		} else {
            detectPlayer();            
		}
	}
};
