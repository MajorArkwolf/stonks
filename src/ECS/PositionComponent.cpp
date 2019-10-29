#include "PositionComponent.hpp"

/**
 * @brief  Defaulted Constructor
 */
PositionComponent::PositionComponent()  = default;

/**
 * @brief  Defaulted Destructor
 */
PositionComponent::~PositionComponent() = default;

/**
 * @brief  Unused
 */
void PositionComponent::init() {}

/**
 * @brief  Unused
 */
void PositionComponent::update() {}

/**
 * @brief  Unused
 */
void PositionComponent::draw() {}

/**
 * @brief   sets Position (not used anymore)
 * @param   newPos new Position
 */
void PositionComponent::setPos(glm::vec3 newPos) {
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
}

/**
 * @brief   sets Position based on tile location.
 * @param   newTile Sets the location based on the tile
 */
void PositionComponent::setPos(Pathing::Node *newTile) {
    this->position.x  = static_cast<float>(newTile->x);
    this->position.z  = static_cast<float>(newTile->y);
    this->currentTile = newTile;
}

/**
 * @brief   sets Position based on tile location.
 * @param   newTile Sets the location based on the tile
 */
void PositionComponent::setNode(Pathing::Node *newTile) {
    this->position.x            = static_cast<float>(newTile->x);
    this->position.z            = static_cast<float>(newTile->y);
    this->currentTile           = newTile;
    this->currentTile->occupant = this->entity;
    this->currentTile->occupied = true;
}

void PositionComponent::setNodeSoft(Pathing::Node *newTile) {
    this->currentTile = newTile;
	this->currentTile->occupant = this->entity;
    this->currentTile->occupied = true;
}

/**
 * @brief   sets Position based on float location.
 * @param   x float
 * @param   y float
 * @param   z float
 */
void PositionComponent::setPos(float x, float y, float z) {
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

/**
 * @brief   sets Position based on float location.
 * @param   x float
 * @param   z float
 */
void PositionComponent::setPos(float x, float z) {
    this->position.x = x;
    this->position.z = z;
}

/**
 * @brief   sets X Position based on float location.
 * @param   x float
 */
void PositionComponent::setXPos(float x) {
    this->position.x = x;
}

/**
 * @brief   sets y Position based on float location.
 * @param   y float
 */
void PositionComponent::setYPos(float y) {
    this->position.y = y;
}

/**
 * @brief   sets Z Position based on float location.
 * @param   z float
 */
void PositionComponent::setZPos(float z) {
    this->position.z = z;
}

/**
 * @brief   sets the rotation of the entity N
 */
void PositionComponent::setRotationN() {
    this->rotation = 0;
}

/**
 * @brief   sets the rotation of the entity NE
 */
void PositionComponent::setRotationNE() {
    this->rotation = 45;
}

/**
 * @brief   sets the rotation of the entity E
 */
void PositionComponent::setRotationE() {
    this->rotation = 90;
}

/**
 * @brief   sets the rotation of the entity SE
 */
void PositionComponent::setRotationSE() {
    this->rotation = 135;
}

/**
 * @brief   sets the rotation of the entity S
 */
void PositionComponent::setRotationS() {
    this->rotation = 180;
}

/**
 * @brief   sets the rotation of the entity SW
 */
void PositionComponent::setRotationSW() {
    this->rotation = 225;
}

/**
 * @brief   sets the rotation of the entity W
 */
void PositionComponent::setRotationW() {
    this->rotation = 270;
}

/**
 * @brief   sets the rotation of the entity NW
 */
void PositionComponent::setRotationNW() {
    this->rotation = 315;
}

/**
 * @brief   returns the current node the entity is standing on
 * @return a node tile
 */
Pathing::Node *PositionComponent::getNode() {
    return this->currentTile;
}

/**
 * @brief   returns the entity location
 * @return vec3 location
 */
glm::vec3 PositionComponent::getPos() {
    return this->position;
}

/**
 * @brief   returns the X entity location
 * @return X location
 */
float PositionComponent::getXPos() {
    return this->position.x;
}

/**
 * @brief   returns the Y entity location
 * @return Y location
 */
float PositionComponent::getYPos() {
    return this->position.y;
}

/**
 * @brief   returns the Z entity location
 * @return Z location
 */
float PositionComponent::getZPos() {
    return this->position.z;
}

/**
 * @brief   returns the entity rotation
 * @return rotation of a float
 */
float PositionComponent::getRotation() {
    return this->rotation;
}

/**
 * @brief   Removes the entity from a given position.
 */
void PositionComponent::removePosition() {
    currentTile->occupant = nullptr;
    currentTile->occupied = false;
}
