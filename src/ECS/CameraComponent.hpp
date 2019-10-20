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
                static_cast<double>(entityPosition.x - lastPosition.x);
            camera.position.z +=
                static_cast<double>(entityPosition.z - lastPosition.z);
            lastPosition = entityPosition;
        }
    }

    auto rotateCamera(float amount) -> void{
       auto rightVec = glm::cross(glm::normalize(camera.look - camera.position),
                   camera.tilt);
        camera.position += rightVec *= amount;
        
	}

    auto zoomCamera(float amount) -> void {
        double minY     = 3;
        double maxY     = 25;
        auto currentPos = camera.position;

        camera.position += (glm::normalize(camera.look - camera.position)) *= amount;

        if (camera.position.y < minY) {
            camera.position = currentPos;
        } else if (camera.position.y > maxY) {
            camera.position = currentPos;
        }
    }
    glm::vec3 lastPosition{};
    Player::Camera camera;
};
