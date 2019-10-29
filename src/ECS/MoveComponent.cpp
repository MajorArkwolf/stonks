#include "MoveComponent.hpp"

#include "DeadComponent.hpp"
#include "PositionComponent.hpp"
#include "Stonk/Engine.hpp"
#include "TurnComponent.hpp"

/**
 * @brief  Default Constructor
 */
MoveComponent::MoveComponent() = default;

/**
 * @brief  Default Destructor
 */
MoveComponent::~MoveComponent() = default;

/**
 * @brief  Unused
 */
void MoveComponent::init() {
    setTime();
}

/**
 * @brief  WHen the movetoken is passed to this function, it executes a move then ends the turn of that entity
 */
void MoveComponent::update() {
    if (!this->entity->hasComponent<DeadComponent>()) {
        auto &e = this->entity->getComponent<PositionComponent>();
        if (this->turnToken == true && startMovement == false) {
            e.getNode()->occupied = false;
            e.getNode()->occupant = nullptr;
            e.setNodeSoft(goingToNode);
            startMovement = true;
            startToEnd    = moveTo - e.getPos();
            setTime();
        } else if (this->turnToken == true && startMovement == true) {
            glm::vec3 movement;
            movement.x = startToEnd.x * static_cast<float>(getDeltaTime()) * 2.5f;
            movement.z =
                startToEnd.z * static_cast<float>(getDeltaTime()) * 2.5f;
            movement   = e.getPos() + movement;
            movement.y = 0;
            e.setPos(movement);

            glm::vec3 currentToEnd = moveTo - e.getPos();
            if (checkSigns(startToEnd.x, currentToEnd.x) ||
                checkSigns(startToEnd.z, currentToEnd.z)) {
                e.setPos(moveTo);
                this->moveTo = {0, 0, 0};
                this->startToEnd    = {0, 0, 0};
                this->goingToNode   = nullptr;
                this->turnToken     = false;
                this->startMovement = false;
	            this->entity->getComponent<TurnComponent>().endYourTurn();
            }
        }
    }
    setTime();
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
    this->moveTo.x        = float(newNode->x)/* + 0.5f*/;
    this->moveTo.z        = float(newNode->y)/* + 0.5f*/;
    goingToNode           = newNode;
    goingToNode->occupied = true;
    goingToNode->occupant = this->entity;
}

void MoveComponent::setTime() {
    auto &e = Stonk::Engine::get();
    time    = e.getTime();
}

double MoveComponent::getDeltaTime() {
    auto &e      = Stonk::Engine::get();
    auto newTime = e.getTime();
    return (newTime - time);
}

bool MoveComponent::checkSigns(float num1, float num2) {
    //int i = static_cast<int>(num1);
    //int x = static_cast<int>(num2);
    if ((num2 * num1) >= 0) {
        return false;
    } else {
        return true;
	}
}
