#pragma once

#include "ECS.hpp"
#include "TurnComponent.hpp"
#include "PositionComponent.hpp"
#include "StatComponent.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../Akuma/Floor.hpp"
#include "../Akuma/Pathing/Pathfinding.hpp"
#include "../Akuma/RNG/Dice.hpp"

/* This will need to handle input to the player */
class EnemyComponent : public Component {
  public:
    enum class Facing { N, NE, E, SE, S, SW, W, NW };
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
    Facing facingBuffer = Facing::N;
    Facing facing       = Facing::N;
    bool lockedToPlayer = false;
    Entity *player      = nullptr;

	//This function is scuffed and wont face the player all the time, cant debug
	//as I dont have enough data to see what the entities are actually doing.
    void determineFacingDirection(Pathing::Node* nextNode) {
        auto *currentNode =
            this->entity->getComponent<PositionComponent>().getNode();
        int x = static_cast<int>(nextNode->x - currentNode->x);
        int y = static_cast<int>(nextNode->y - currentNode->y);

        if (x == -1) {
            if (y == -1) {
                facingBuffer = Facing::SW;
            } else if (y == 0) {
                facingBuffer = Facing::W;
            } else if (y == 1) {
                facingBuffer = Facing::N;
            }
        } else if (x == 0) {
            if (y == -1) {
                facingBuffer = Facing::S;
            } else if (y == 0) {
                facingBuffer = Facing::NW; // default always face north
            } else if (y == 1) {
                facingBuffer = Facing::E;
            }
        } else if (x == 1) {
            if (y == -1) {
                facingBuffer = Facing::SW;
            } else if (y == 0) {
                facingBuffer = Facing::E;
            } else if (y == 1) {
                facingBuffer = Facing::NE;
            }
        }
    }

	auto setTurnAngle() -> void {
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
	}

	void detectPlayer() {
        if (this->entity->hasComponent<StatComponent>()) {
            auto distance = DistanceBetween();                
            auto myIntel =
                this->entity->getComponent<StatComponent>().getIntelligenceMod();
            auto playerStealth =
                player->getComponent<StatComponent>().getDexterityMod();
            if (diceroller.Roll(1, 20) + myIntel >
                diceroller.Roll(1, 20) + playerStealth + static_cast<int>(distance)) {
                lockedToPlayer = true;
			}
		}
	}

	auto DistanceBetween() -> unsigned int {            
        return static_cast<unsigned int>(Pathing::Pathfinding::findPath(
                   this->entity->getComponent<FloorComponent>().getFloor()->getGrid(),
                   *this->entity->getComponent<PositionComponent>().getNode(),
                   *player->getComponent<PositionComponent>().getNode(), true).size());
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
