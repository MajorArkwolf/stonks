#pragma once

#include "ECS.hpp"

class DeadComponent : public Component {
  public:
    DeadComponent();
    ~DeadComponent();
    void init();
    void update();
    void draw();
};
