#pragma once

#include "ECS.hpp"
#include "PositionComponent.hpp"
#include "TurnComponent.hpp"
#include <glm/vec3.hpp>
#include "Akuma/Pathing/Node.hpp"

/* This will need to handle input to the player */
class MoveComponent : public Component {
  public:
    MoveComponent()    = default;
    ~MoveComponent() = default;
    void init() {}
    void update() {
        /*if (component is facing direction)
		then do move,
		else (tell rotation system to start rotating object)
		*/
        //if (this->entity->hasComponent<PositionComponent>()) {
        //    this->entity->getComponent<PositionComponent>().setPos(moveTo);
        //}
        //isMoving = true;
        if (this->turnToken == true) {
			this->entity->getComponent<PositionComponent>().getNode()->occupied =
                false;
            this->entity->getComponent<PositionComponent>().getNode()->occupant =
                nullptr;
            this->entity->getComponent<PositionComponent>().setPos(goingToNode);
            this->goingToNode = nullptr;
            this->turnToken   = false;
            this->entity->getComponent<TurnComponent>().endYourTurn();
        }
        
        
	}
    void draw() {}

	void moveEntity(const glm::vec3& movingTo) {
        this->turnToken = true;
        this->moveTo = movingTo;
	}

	void moveEntityToNode(Pathing::Node *newNode) {
        this->turnToken       = true;
        this->moveTo.x = float(newNode->x) + 0.5f;
        this->moveTo.z = float(newNode->y) + 0.5f;
        goingToNode    = newNode;
        goingToNode->occupied = true;
        goingToNode->occupant = this->entity;
	}


  private:
    Pathing::Node *goingToNode = nullptr;
    bool turnToken = false;
    glm::vec3 moveTo = {0, 0, 0};
};
