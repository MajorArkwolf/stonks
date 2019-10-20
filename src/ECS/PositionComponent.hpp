#pragma once

#include <glm/vec3.hpp>
#include "Akuma/Floor.hpp"
#include "Components.hpp"

/* This will need to handle all positions of entities. */
class PositionComponent : public Component {
  public:
    PositionComponent() = default;
    PositionComponent(float x, float y, float z) {
        this->position.x = x;
        this->position.y = y;
        this->position.y = z;
    }
    PositionComponent(float x, float z) {
        this->position.x = x;
        this->position.y = 1;
        this->position.y = z;
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

	void setPos(Pathing::Node* newTile) {
        position.x = newTile->x + 0.5f;
        position.y = newTile->y + 0.5f;
        currentTile = newTile;
	}

	void setNode(Pathing::Node* newTile) {
        currentTile = newTile;
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
    void setZPos(float z) {
        this->position.z = z;
    }
    void setRotationN() {
        rotation = 0;
    }
    void setRotationNE() {
        rotation = 45;
    }
    void setRotationE() {
        rotation = 90;
    }
    void setRotationSE() {
        rotation = 135;
    }
    void setRotationS() {
        rotation = 180;
    }
    void setRotationSW() {
        rotation = 225;
    }
    void setRotationW() {
        rotation = 270;
    }
    void setRotationNW() {
        rotation = 315;
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

	GLfloat getRotation() {
        return rotation;
	}

    ~PositionComponent() = default;

  private:
    GLfloat rotation   = 0;
    glm::vec3 position = {0.0, 0, 0.0};
    Pathing::Node *currentTile = nullptr;
};
