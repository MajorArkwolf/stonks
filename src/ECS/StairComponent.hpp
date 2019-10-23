#pragma once

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

  private:
    bool stairCaseActivate = false;
};
