#pragma once

#include "Components.hpp"

/* This will need to handle input to the player */
class CameraComponent : public Component {
  public:
    CameraComponent()  = default;
    ~CameraComponent() = default;
    void init() {}
    void update() {}
    void draw() {}
};
