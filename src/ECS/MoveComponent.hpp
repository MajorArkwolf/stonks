#pragma once

#include <glm/vec3.hpp>

#include "Akuma/Pathing/Node.hpp"
#include "ECS.hpp"


/* This will need to handle input to the player */
class MoveComponent : public Component {
  public:
    MoveComponent();
    ~MoveComponent();
    void init();
    void update();
    void draw();

    void moveEntity(const glm::vec3 &movingTo);

    void moveEntityToNode(Pathing::Node *newNode);

  private:
    Pathing::Node *goingToNode = nullptr;
    bool turnToken             = false;
    glm::vec3 moveTo           = {0, 0, 0};
};
