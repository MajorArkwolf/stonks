#include "PositionComponent.hpp"

PositionComponent::PositionComponent()  = default;
PositionComponent::~PositionComponent(){
    currentTile->occupant = nullptr;
    currentTile->occupied = false;
};
void PositionComponent::init() {}
void PositionComponent::update() {}
void PositionComponent::draw() {}

void PositionComponent::setPos(glm::vec3 newPos) {
    this->position.x = newPos.x;
    this->position.y = newPos.y;
    this->position.z = newPos.z;
}

void PositionComponent::setPos(Pathing::Node *newTile) {
    this->position.x  = static_cast<float>(newTile->x);
    this->position.z  = static_cast<float>(newTile->y);
    this->currentTile = newTile;
}

void PositionComponent::setNode(Pathing::Node *newTile) {
    this->position.x            = static_cast<float>(newTile->x);
    this->position.z            = static_cast<float>(newTile->y);
    this->currentTile           = newTile;
    this->currentTile->occupant = this->entity;
    this->currentTile->occupied = true;
}

void PositionComponent::setPos(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}
void PositionComponent::setPos(float x, float z) {
    this->position.x = x;
    this->position.z = z;
}

void PositionComponent::setXPos(float x) {
    this->position.x = x;
}

void PositionComponent::setYPos(float y) {
    this->position.y = y;
}
void PositionComponent::setZPos(float z) {
    this->position.z = z;
}
void PositionComponent::setRotationN() {
    this->rotation = 0;
}
void PositionComponent::setRotationNE() {
    this->rotation = 45;
}
void PositionComponent::setRotationE() {
    this->rotation = 90;
}
void PositionComponent::setRotationSE() {
    this->rotation = 135;
}
void PositionComponent::setRotationS() {
    this->rotation = 180;
}
void PositionComponent::setRotationSW() {
    this->rotation = 225;
}
void PositionComponent::setRotationW() {
    this->rotation = 270;
}
void PositionComponent::setRotationNW() {
    this->rotation = 315;
}

Pathing::Node *PositionComponent::getNode() {
    return this->currentTile;
}

glm::vec3 PositionComponent::getPos() {
    return this->position;
}

float PositionComponent::getXPos() {
    return this->position.x;
}

float PositionComponent::getYPos() {
    return this->position.y;
}
float PositionComponent::getZPos() {
    return this->position.z;
}

float PositionComponent::getRotation() {
    return this->rotation;
}
