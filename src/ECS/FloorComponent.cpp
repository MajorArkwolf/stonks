#include "FloorComponent.hpp"
FloorComponent::FloorComponent()  = default;
FloorComponent::~FloorComponent() = default;
void FloorComponent::init() {}
void FloorComponent::update() {}
void FloorComponent::draw() {}
void FloorComponent::setFloor(Floor &newFloor) {
    this->floor = &newFloor;
    floorSet    = true;
}
Floor *FloorComponent::getFloor() {
    if (floorSet == true) {
        return floor;
    } else {
        return nullptr;
    }
}
