#include "CameraComponent.hpp"

#include <math.h>
void CameraComponent::init() {
    UpdateCameraLook();
    if (this->entity->hasComponent<PositionComponent>()) {
        lastPosition = this->entity->getComponent<PositionComponent>().getPos();
    }
    camera.position.y = 25;
}
void CameraComponent::update() {
    UpdateCameraLook();
    UpdateCameraPosition();
}
void CameraComponent::draw() {}

auto CameraComponent::UpdateCameraLook() -> void {
    if (this->entity->hasComponent<PositionComponent>()) {
        camera.look = this->entity->getComponent<PositionComponent>().getPos();
    }
}

auto CameraComponent::UpdateCameraPosition() -> void {
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

auto CameraComponent::rotateCamera(double amount) -> void {
    currentRotation += amount;
}

auto CameraComponent::zoomCamera(double amount) -> void {
    double minDist = 3;
    double maxDist = 25;

    distanceFromEntity -= amount;

    if (distanceFromEntity > maxDist) {
        distanceFromEntity = maxDist;
    } else if (distanceFromEntity < minDist) {
        distanceFromEntity = minDist;
    }
}
