#pragma once

#include "Components.hpp"
#include <glm/vec3.hpp>
#include "Pathing/Node.hpp"

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
        this->entity->getComponent<PositionComponent>().setPos(moveTo);
        isMoving = false;
	}
    void draw() {}

	void moveEntity(const glm::vec3& movingTo) {
        isMoving = true;
        moveTo = movingTo;
	}

	void moveEntityToNode(const Pathing::Node &newNode) {
        isMoving = true;
        moveTo.x = newNode.x + 0.5;
        moveTo.z = newNode.y + 0.5;
	}


  private:
    bool isMoving = false;
    glm::vec3 moveTo = {0, 0, 0};
};
