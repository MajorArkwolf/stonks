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
    }
    void update() {
        UpdateCameraLook();
    }
    void draw() {
        camera.position = glm::vec3{0.0f, 50.0f, 0.0f};
        gluLookAt(camera.position.x, camera.position.y, camera.position.z,
                  camera.look.x, camera.look.y, camera.look.z, 1,
                  0, 1);
    }

    auto UpdateCameraLook() -> void {
        if (this->entity->hasComponent<PositionComponent>()) {
            camera.look = this->entity->getComponent<PositionComponent>().getPos();
        }
    }

  private:
    Player::Camera camera;
};
