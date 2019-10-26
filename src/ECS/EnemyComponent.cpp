#include "EnemyComponent.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "../Akuma/Pathing/Pathfinding.hpp"
#include "../Akuma/Items/ItemManager.hpp"
#include "..//Akuma/CombatLog.hpp"

#include "PositionComponent.hpp"
#include "MoveComponent.hpp"
#include "TurnComponent.hpp"
#include "StatComponent.hpp"
#include "CombatComponent.hpp"
#include "FloorComponent.hpp"
#include "InventoryComponent.hpp"
#include "DeadComponent.hpp"

EnemyComponent::EnemyComponent()  = default;
EnemyComponent::~EnemyComponent() = default;
void EnemyComponent::init() {}
void EnemyComponent::update() {
    if (!this->entity->hasComponent<DeadComponent>()) {
		if (this->entity->hasComponent<TurnComponent>()) {
			if (this->entity->getComponent<TurnComponent>().checkTurn()) {
				this->entity->getComponent<TurnComponent>().assignAction();
				combatCheck();
				moveAction();
				// facing = facingBuffer;
				// setTurnAngle();
			}
        }
    }
}
void EnemyComponent::draw() {}
void EnemyComponent::setFacing(Facing newFace) {
    facingBuffer = newFace;
}

void EnemyComponent::updateFacing() {
    facing = facingBuffer;
}

void EnemyComponent::setFacing(int i) {
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

void EnemyComponent::SetPlayerTarget(Entity *currentPlayer) {
    player = currentPlayer;
}

void EnemyComponent::turnEntity(int i) {
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

// This function is scuffed and wont face the player all the time, cant debug
// as I dont have enough data to see what the entities are actually doing.
void EnemyComponent::determineFacingDirection(Pathing::Node *nextNode) {
    auto *currentNode = this->entity->getComponent<PositionComponent>().getNode();
    int x             = static_cast<int>(nextNode->x - currentNode->x);
    int y             = static_cast<int>(nextNode->y - currentNode->y);

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

auto EnemyComponent::setTurnAngle() -> void {
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

void EnemyComponent::detectPlayer() {
    if (this->entity->hasComponent<StatComponent>()) {
        auto distance = DistanceBetween();
        auto myIntel =
            this->entity->getComponent<StatComponent>().getIntelligenceMod();
        auto playerStealth =
            player->getComponent<StatComponent>().getDexterityMod();
        if (diceroller.Roll(1, 20) + myIntel >
            diceroller.Roll(1, 20) + playerStealth + static_cast<int>(distance)) {
            lockedToPlayer = true;
            // Play Sound here
        }
    }
    this->entity->getComponent<TurnComponent>().endYourTurn();
}

auto EnemyComponent::DistanceBetween() -> unsigned int {
    return static_cast<unsigned int>(
        Pathing::Pathfinding::findPath(
            this->entity->getComponent<FloorComponent>().getFloor()->getGrid(),
            *this->entity->getComponent<PositionComponent>().getNode(),
            *player->getComponent<PositionComponent>().getNode(), true)
            .size());
}

auto EnemyComponent::goToPlayer() -> void {
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
                } else {
                    this->entity->getComponent<TurnComponent>().endYourTurn();
                }
            } else {
                this->entity->getComponent<TurnComponent>().endYourTurn();
            }
        } else {
            this->entity->getComponent<TurnComponent>().endYourTurn();
        }
    }
}

auto EnemyComponent::moveAction() -> void {
    if (lockedToPlayer) {
        goToPlayer();
    } else {
        detectPlayer();
    }
}
auto EnemyComponent::combatCheck() -> void {
    if (lockedToPlayer) {
        auto *currentNode =
            this->entity->getComponent<PositionComponent>().getNode();
        auto *floor = this->entity->getComponent<FloorComponent>().getFloor();
        auto neighbours = floor->getNeighbours(*currentNode);
        for (auto &x : neighbours) {
            if (x->occupant == player) {
                this->entity->getComponent<CombatComponent>().attackEntity(
                    x->occupant);
                break;
            }
        }
    }
}

auto EnemyComponent::deadEnemy() -> void {
    if (this->entity->hasComponent<StatComponent>()) {
        if (!this->entity->hasComponent<DeadComponent>()) {
            this->entity->getComponent<PositionComponent>().removePosition();

            string info = "";
			this->entity->addComponentID<DeadComponent>();
            if (diceroller.Roll(1, 10) > 6) {
        		unsigned int maxSize = static_cast<unsigned int>(ItemManager::ItemManager().size());
                size_t lookUp = 0;
                do {
					lookUp = static_cast<size_t>(diceroller.Roll(1u, maxSize));
                } while (lookUp < 2);
				ItemID returnedItem = ItemManager::getItem(lookUp);
				player->getComponent<InventoryComponent>().addItemToInventory(
					returnedItem);
                info =
                    this->entity->getComponent<StatComponent>().stat.name + " has died dropping a " + returnedItem.name + ".";
            } else {
                info = this->entity->getComponent<StatComponent>().stat.name +
                       " has died, it dropped nothing of value.";
			}
            CombatLog::log().push_back(info);

			//DELETE IF DOESNT FIX.
            this->entity->getComponent<TurnComponent>().endYourTurn();
        }
    }
}
