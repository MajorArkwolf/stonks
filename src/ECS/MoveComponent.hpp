#pragma once

#include "Components.hpp"
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
        if (this->isMoving == true) {
            this->entity->getComponent<PositionComponent>().setPos(moveTo);
            this->isMoving = false;
        }
        
        
	}
    void draw() {}

	void moveEntity(const glm::vec3& movingTo) {
        this->isMoving = true;
        this->moveTo = movingTo;
	}

	void moveEntityToNode(const Pathing::Node &newNode) {
        this->isMoving = true;
        this->moveTo.x = float(newNode.x) + 0.5f;
        this->moveTo.z = float(newNode.y) + 0.5f;
	}


  private:
    bool isMoving = false;
    glm::vec3 moveTo = {0, 0, 0};
};
