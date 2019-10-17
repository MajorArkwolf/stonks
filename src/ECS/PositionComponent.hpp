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
    PositionComponent(glm::vec2 newPos) {
        this->position.x = newPos.x;
        this->position.y = newPos.y;
    }
    void init() {}
    void update() {}
    void draw() {}

    void setPos(glm::vec2 newPos) {
        this->position.x = newPos.x;
        this->position.y = newPos.y;
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

    glm::vec2 getPos() {
        return position;
    }

    GLfloat getXPos() {
        return this->position.x;
    }

    GLfloat getYPos() {
        return this->position.y;
    }

    ~PositionComponent() = default;

  private:
    glm::vec2 position;
};