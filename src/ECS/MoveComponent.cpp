#include "MoveComponent.hpp"
#include "PositionComponent.hpp"
#include "TurnComponent.hpp"
#include "DeadComponent.hpp"

MoveComponent::MoveComponent()  = default;
MoveComponent::~MoveComponent() = default;
void MoveComponent::init() {}
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
void MoveComponent::draw() {}

void MoveComponent::moveEntity(const glm::vec3 &movingTo) {
    this->turnToken = true;
    this->moveTo    = movingTo;
}

void MoveComponent::moveEntityToNode(Pathing::Node *newNode) {
    this->turnToken       = true;
    this->moveTo.x        = float(newNode->x) + 0.5f;
    this->moveTo.z        = float(newNode->y) + 0.5f;
    goingToNode           = newNode;
    goingToNode->occupied = true;
    goingToNode->occupant = this->entity;
}
