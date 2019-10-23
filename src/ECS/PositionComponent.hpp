#pragma once

#include <glm/vec3.hpp>

#include "Akuma/Floor.hpp"
#include "ECS.hpp"

/* This will need to handle all positions of entities. */
class PositionComponent : public Component {
  public:
    PositionComponent()  = default;
    ~PositionComponent() = default;

    void init();
    void update();
    void draw();

    void setPos(glm::vec3 newPos);

    void setPos(Pathing::Node *newTile);

    void setNode(Pathing::Node *newTile);

    void setPos(float x, float y, float z);
    void setPos(float x, float z);

    void setXPos(float x);

    void setYPos(float y);
    void setZPos(float z);
    void setRotationN();
    void setRotationNE();
    void setRotationE();
    void setRotationSE();
    void setRotationS();
    void setRotationSW();
    void setRotationW();
    void setRotationNW();

    Pathing::Node *getNode();

    glm::vec3 getPos();

    float getXPos();

    float getYPos();
    float getZPos();

    float getRotation();

  private:
    float rotation             = 0.0f;
    glm::vec3 position         = {0.0f, 0.0f, 0.0f};
    Pathing::Node *currentTile = nullptr;
};
