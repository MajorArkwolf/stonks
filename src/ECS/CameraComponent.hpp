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
            glm::dvec3 entityPosition =
                this->entity->getComponent<PositionComponent>().getPos();

            auto radians      = currentRotation * ((atan(1) * 4) / 180);
            camera.position.x = std::cos(radians) * distanceFromEntity;
            camera.position.z = std::sin(radians) * distanceFromEntity;
            camera.position.y = distanceFromEntity;

            camera.position.x += entityPosition.x;
            camera.position.z += entityPosition.z;

        }
    }

    auto rotateCamera(double amount) -> void {
        currentRotation += amount;
    }

    auto zoomCamera(double amount) -> void {
        double minDist  = 3;
        double maxDist  = 25;

        distanceFromEntity -= amount;

        if (distanceFromEntity > maxDist) {
            distanceFromEntity = maxDist;
        } else if (distanceFromEntity < minDist) {
            distanceFromEntity = minDist;
        }
    }
    double distanceFromEntity = 10;
    double currentRotation    = 0;
    glm::vec3 lastPosition{};
    Player::Camera camera;
};
