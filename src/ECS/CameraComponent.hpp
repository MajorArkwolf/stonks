#pragma once

#include <glm/vec3.hpp>

#include "../Akuma/Camera.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"

/* This will need to handle input to the player */
class CameraComponent : public Component {
  public:
    CameraComponent();
    ~CameraComponent();
    void init();
    void update();
    void draw();

    auto UpdateCameraLook() -> void;

    auto UpdateCameraPosition() -> void;

    auto rotateCamera(double amount) -> void;

    auto zoomCamera(double amount) -> void;
    double distanceFromEntity = 10;
    double currentRotation    = 0;
    glm::vec3 lastPosition{};
    Player::Camera camera;
};
