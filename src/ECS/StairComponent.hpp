#pragma once
#include "Akuma/Floor.hpp"
#include "ECS.hpp"

/* This will need to handle input to the player */
class StairComponent : public Component {
  public:
    StairComponent()  = default;
    ~StairComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

    bool checkStairActive();
    void SetStairActive();
    void resetStairCase();

	void setNodes(Pathing::Node *node1, Pathing::Node *node2, Pathing::Node *node3,
                  Pathing::Node *node4);

  private:
    Pathing::Node *occupiedNodes[4] = {nullptr};
    bool stairCaseActivate = false;
};
