#pragma once
#include <glm/vec3.hpp>
#include "Components.h"
#include "SDL.h"


/* This will need to handle all positions of entities. */
class PositionComponent : public Component {
  public:
    PositionComponent() = default;
	PositionComponent(int x, int y) {
        this->position.xPos = x;
        this->position.yPos = y;
	}
	PositionComponent(glm::vec2 newPos) {
        this->position.xPos = newPos.xPos;
        this->position.yPos = newPos.yPos;
	}    
    void init() {}
    void update() {}
    void draw() {}

	void setPos(Vec2d newPos) {
        this->position.xPos = newPos.xPos;
        this->position.yPos = newPos.yPos;
	}

	void setPos(int x, int y) {
        this->position.xPos = x;
        this->position.yPos = y;
	}

	void setXPos(int x) {
        this->position.xPos = x;
	}

	void setXPos(int y) {
        this->position.yPos = y;
    }

	void getPos() {
        return position;
	}

	void getXPos() {
        return this->position.xPos;
	}

	void getYPos() {
        return this->position.yPos;
    }

    ~PositionComponent() = default;
  private:
    glm::vec3 position;
}