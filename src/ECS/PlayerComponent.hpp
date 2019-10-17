#pragma once

#include "Components.hpp"

/* This will need to handle input to the player */
class PlayerComponent : public Component {
  public:
    PlayerComponent()  = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {}
    void draw() {}
};