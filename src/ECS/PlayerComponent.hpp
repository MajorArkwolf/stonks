#pragma once

#include "Components.h"
#include "SDL.h"

/* This will need to handle input to the player */
class PlayerComponent : public Component {
  public:
    PlayerComponent() = default;
    ~PlayerComponent() = default;
    void init() {}
    void update() {}
    void draw() {}

}