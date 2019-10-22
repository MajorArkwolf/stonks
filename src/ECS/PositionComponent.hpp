#pragma once

#include <glm/vec3.hpp>
#include "ECS.hpp"
#include "Akuma/Floor.hpp"


/* This will need to handle all positions of entities. */
class PositionComponent : public Component {
  public:
    PositionComponent() = default;
    ~PositionComponent() = default;

    void init() {}
    void update() {}
    void draw() {}

    void setPos(glm::vec3 newPos) {
        this->position.x = newPos.x;
        this->position.y = newPos.y;
        this->position.z = newPos.z;
    }

	void setPos(Pathing::Node* newTile) {
        this->position.x  = static_cast<float>(newTile->x);
        this->position.z  = static_cast<float>(newTile->y);
        this->currentTile = newTile;
	}

	void setNode(Pathing::Node* newTile) {
        this->currentTile = newTile;
	}

    void setPos(float x, float y, float z) {
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
    }
    void setPos(float x, float z) {
        this->position.x = x;
        this->position.z = z;
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
        this->rotation = 0;
    }
    void setRotationNE() {
        this->rotation = 45;
    }
    void setRotationE() {
        this->rotation = 90;
    }
    void setRotationSE() {
        this->rotation = 135;
    }
    void setRotationS() {
        this->rotation = 180;
    }
    void setRotationSW() {
        this->rotation = 225;
    }
    void setRotationW() {
        this->rotation = 270;
    }
    void setRotationNW() {
        this->rotation = 315;
    }

	Pathing::Node* getNode() {
        return this->currentTile;
	}

    glm::vec3 getPos() {
        return this->position;
    }

    float getXPos() {
        return this->position.x;
    }

    float getYPos() {
        return this->position.y;
    }
    float getZPos() {
        return this->position.z;
    }

	float getRotation() {
        return this->rotation;
	}

  private:
    float rotation             = 0.0f;
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    Pathing::Node *currentTile = nullptr;
};
