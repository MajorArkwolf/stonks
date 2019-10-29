#include "CameraComponent.hpp"
#include "PositionComponent.hpp"
#include <cmath>

/**
 * @brief  Default Constructor
 */
CameraComponent::CameraComponent()  = default;

/**
 * @brief  Default Destructor
 */
CameraComponent::~CameraComponent() = default;

/**
 * @brief  intitalizes the camera
 */
void CameraComponent::init() {
    UpdateCameraLook();
    if (this->entity->hasComponent<PositionComponent>()) {
        lastPosition = this->entity->getComponent<PositionComponent>().getPos();
    }
    camera.position.y = 25;
}

/**
 * @brief  updates the camera based on the new location
 */
void CameraComponent::update() {
    UpdateCameraLook();
    UpdateCameraPosition();
}

/**
 * @brief  Unused
 */
void CameraComponent::draw() {}

/**
 * @brief  Update the camera look location
 */
auto CameraComponent::UpdateCameraLook() -> void {
    if (this->entity->hasComponent<PositionComponent>()) {
        camera.look = this->entity->getComponent<PositionComponent>().getPos();
    }
}

/**
 * @brief  Update the camera position
 */
auto CameraComponent::UpdateCameraPosition() -> void {
    if (this->entity->hasComponent<PositionComponent>()) {
        glm::dvec3 entityPosition =
            this->entity->getComponent<PositionComponent>().getPos();

        auto radians      = currentRotation * ((std::atan(1) * 4) / 180);
        camera.position.x = std::cos(radians) * distanceFromEntity;
        camera.position.z = std::sin(radians) * distanceFromEntity;
        camera.position.y = distanceFromEntity;

        camera.position.x += entityPosition.x;
        camera.position.z += entityPosition.z;
    }
}

/**
 * @brief  rotate the camera
 * @param  amount the amount of rotation change by
 */
auto CameraComponent::rotateCamera(double amount) -> void {
    currentRotation += amount;
}

/**
 * @brief  zoom the camera
 * @param  amount the amount to zoom the camera
 */
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
