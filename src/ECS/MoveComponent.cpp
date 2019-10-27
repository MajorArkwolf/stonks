#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "TurnComponent.hpp"
#include "DeadComponent.hpp"

/**
 * @brief  Default Constructor
 */
MoveComponent::MoveComponent()  = default;

/**
 * @brief  Default Destructor
 */
MoveComponent::~MoveComponent() = default;

/**
 * @brief  Unused
 */
void MoveComponent::init() {}

/**
 * @brief  WHen the movetoken is passed to this function, it executes a move then ends the turn of that entity
 */
void MoveComponent::update() {
    if (!this->entity->hasComponent<DeadComponent>()) {
		if (this->turnToken == true) {
			this->entity->getComponent<PositionComponent>().getNode()->occupied = false;
			this->entity->getComponent<PositionComponent>().getNode()->occupant =
				nullptr;
			this->entity->getComponent<PositionComponent>().setPos(goingToNode);
			this->goingToNode = nullptr;
			this->turnToken   = false;
			this->entity->getComponent<TurnComponent>().endYourTurn();
		}
    }
}

/**
 * @brief  Unused
 */
void MoveComponent::draw() {}

/**
 * @brief  sets the moving to location
 * @param movingTo the location to move the entity to.
 */
void MoveComponent::moveEntity(const glm::vec3 &movingTo) {
    this->turnToken = true;
    this->moveTo    = movingTo;
}

/**
 * @brief  sets the moving to a node location
 * @param newNode the node to move to.
 */
void MoveComponent::moveEntityToNode(Pathing::Node *newNode) {
    this->turnToken       = true;
    this->moveTo.x        = float(newNode->x) + 0.5f;
    this->moveTo.z        = float(newNode->y) + 0.5f;
    goingToNode           = newNode;
    goingToNode->occupied = true;
    goingToNode->occupant = this->entity;
}
