#include "FloorComponent.hpp"

/**
 * @brief  Default Constructor
 */
FloorComponent::FloorComponent()  = default;

/**
 * @brief  Default Destructor
 */
FloorComponent::~FloorComponent() = default;

/**
 * @brief  Unused
 */
void FloorComponent::init() {}

/**
 * @brief  Unused
 */
void FloorComponent::update() {}

/**
 * @brief  Unused
 */
void FloorComponent::draw() {}

/**
 * @brief  Sets the floor so entities 3
 * @param newFloor sets the floor
 */
void FloorComponent::setFloor(Floor &newFloor) {
    this->floor = &newFloor;
    floorSet    = true;
}

/**
 * @brief  Sets the floor so entities 3
 * @return returns the floor
 */
Floor *FloorComponent::getFloor() {
    if (floorSet == true) {
        return floor;
    } else {
        return nullptr;
    }
}
