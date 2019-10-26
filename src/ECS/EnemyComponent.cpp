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

/**
 * @brief  Default Constructor
 */
EnemyComponent::EnemyComponent()  = default;

/**
 * @brief  Default Destructor
 */
EnemyComponent::~EnemyComponent() = default;

/**
 * @brief  Unused
 */
void EnemyComponent::init() {}

/**
 * @brief  On update, does a dead check a turn check and then if all passed it allows the enemy to take there turn.
 */
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

/**
 * @brief  Unused
 */
void EnemyComponent::draw() {}

/**
 * @brief  Sets the facing direction to the buffer
 * @param newFace the direction to face
 */
void EnemyComponent::setFacing(Facing newFace) {
    facingBuffer = newFace;
}

/**
 * @brief  Pushes the buffer into the facing direction
 */
void EnemyComponent::updateFacing() {
    facing = facingBuffer;
}

/**
 * @brief  Uses an int value to determine the facing direction
 * @param i used to determine direction, 0 being N and 7 being NW
 */
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

/**
 * @brief  Sets the entity the player they will target
 * @param currentPlayer the only player in the game
 */
void EnemyComponent::SetPlayerTarget(Entity *currentPlayer) {
    player = currentPlayer;
}

/**
 * @brief  Clamps the value if it goes over or under 0-7
 * @param  i used to add onto the existing turn variable
 */
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

/**
 * @brief  Determines the facing direction to the next node
 * @param  nextNode the next node to move to
 */
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

/**
 * @brief  After getting the facing direction, it sets it using fixed values
 */
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

/**
 * @brief  Check to see if the enemy has located the player.
 */
void EnemyComponent::detectPlayer() {
    if (this->entity->hasComponent<StatComponent>()) {
        auto distance = DistanceBetween();
        auto myIntel =
            this->entity->getComponent<StatComponent>().getIntelligenceMod();
        auto playerStealth =
            player->getComponent<StatComponent>().getDexterityMod();
        auto result = diceroller.Roll(1, 20);
        if (result + myIntel >
            diceroller.Roll(1, 20) + playerStealth + static_cast<int>(distance) || result == 20) {
            lockedToPlayer = true;
            // Play Sound here
        }
    }
    this->entity->getComponent<TurnComponent>().endYourTurn();
}

/**
 * @brief  Determines the distance between the player and the enemy
 * @return the distance
 */
auto EnemyComponent::DistanceBetween() -> unsigned int {
    return static_cast<unsigned int>(
        Pathing::Pathfinding::findPath(
            this->entity->getComponent<FloorComponent>().getFloor()->getGrid(),
            *this->entity->getComponent<PositionComponent>().getNode(),
            *player->getComponent<PositionComponent>().getNode(), true)
            .size());
}

/**
 * @brief  moves the enemy towards the current players position using a*
 */
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

/**
 * @brief  Used to determine if the player needs to be found or moved towards
 */
auto EnemyComponent::moveAction() -> void {
    if (lockedToPlayer) {
        goToPlayer();
    } else {
        detectPlayer();
    }
}

/**
 * @brief  Checks to see if the player is within range of combat
 */
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

/**
 * @brief  Checks to see if the enemy is dead and if so to drop an item for the player.
 */
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
                } while (lookUp <= 2);
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
        }
    }
}
