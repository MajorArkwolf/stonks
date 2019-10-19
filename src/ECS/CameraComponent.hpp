#pragma once

#include <glm/vec3.hpp>

#include "../Akuma/Camera.hpp"
#include "Components.hpp"

/* This will need to handle input to the player */
class CameraComponent : public Component {
  public:
    CameraComponent()  = default;
    ~CameraComponent() = default;
    void init() {
        UpdateCameraLook();
        if (this->entity->hasComponent<PositionComponent>()) {
            lastPosition =
                this->entity->getComponent<PositionComponent>().getPos();
        }
        camera.position.y = 25;
    }
    void update() {
        UpdateCameraLook();
        UpdateCameraPosition();
    }
    void draw() {}

    auto UpdateCameraLook() -> void {
        if (this->entity->hasComponent<PositionComponent>()) {
            camera.look = this->entity->getComponent<PositionComponent>().getPos();
        }
    }

    auto UpdateCameraPosition() -> void {
        if (this->entity->hasComponent<PositionComponent>()) {
            glm::vec3 entityPosition =
                this->entity->getComponent<PositionComponent>().getPos();
            camera.position.x +=
                static_cast<double>(entityPosition.x - lastPosition.z);
            camera.position.z +=
                static_cast<double>(entityPosition.z - lastPosition.z);
            lastPosition = entityPosition;
        }
    }
    glm::vec3 lastPosition{};
    Player::Camera camera;
};
