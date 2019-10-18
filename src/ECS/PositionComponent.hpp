#pragma once

#include "Components.hpp"
#include <glm/vec2.hpp>

/* This will need to handle all positions of entities. */
class PositionComponent : public Component {
  public:
    PositionComponent() = default;
    PositionComponent(float x, float y) {
        this->position.x = x;
        this->position.y = y;
    }
    PositionComponent(glm::vec3 newPos) {
        this->position.x = newPos.x;
        this->position.y = newPos.y;
        this->position.z = newPos.z;
    }
    void init() {}
    void update() {}
    void draw() {}

    void setPos(glm::vec3 newPos) {
        this->position.x = newPos.x;
        this->position.y = newPos.y;
        this->position.z = newPos.z;
    }

    void setPos(float x, float y) {
        this->position.x = x;
        this->position.y = y;
    }

    void setXPos(float x) {
        this->position.x = x;
    }

    void setYPos(float y) {
        this->position.y = y;
    }

    glm::vec3 getPos() {
        return this->position;
    }

    GLfloat getXPos() {
        return this->position.x;
    }

    GLfloat getYPos() {
        return this->position.y;
    }
	GLfloat getZPos() {
        return this->position.z;
	}

    ~PositionComponent() = default;

  private:
    glm::vec3 position = {1, 1, 1};
};