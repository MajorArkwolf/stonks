#include "ScaleComponent.hpp"

/**
 * @brief  Default Constructor
 */
ScaleComponent::ScaleComponent()  = default;

/**
 * @brief  Default Destructor
 */
ScaleComponent::~ScaleComponent() = default;


/**
 * @brief  Alerternate Contructor
 */
ScaleComponent::ScaleComponent(glm::vec3 temp) {
    scale = temp;
}

/**
 * @brief  Unused
 */
void ScaleComponent::init() {}

/**
 * @brief  Unused
 */
void ScaleComponent::update() {}

/**
 * @brief  Unused
 */
void ScaleComponent::draw() {}

/**
 * @brief  returns the X scale
 * @return X value
 */
auto ScaleComponent::getXScale() -> float {
    return scale.x;
}

/**
 * @brief  returns the Y scale
 * @return Y value
 */
auto ScaleComponent::getYScale() -> float {
    return scale.y;
}

/**
 * @brief  returns the Z scale
 * @return Z value
 */
auto ScaleComponent::getZScale() -> float {
    return scale.z;
}

/**
 * @brief  returns thescale
 * @return the entire scale value
 */
auto ScaleComponent::getScale() -> glm::vec3 {
    return scale;
}

/**
 * @brief  Setter for the entire scale
 * @param vec3 new scale
 */
auto ScaleComponent::setScale(glm::vec3 temp) -> void {
    scale.x = temp.x;
    scale.y = temp.y;
    scale.z = temp.z;
}

/**
 * @brief  Sets the X scale
 * @param temp float
 */
auto ScaleComponent::setXScale(float temp) -> void {
    scale.x = temp;
}

/**
 * @brief  Sets the Y scale
 * @param temp float
 */
auto ScaleComponent::setYScale(float temp) -> void {
    scale.y = temp;
}

/**
 * @brief  Sets the Z scale
 * @param temp float
 */
auto ScaleComponent::setZScale(float temp) -> void {
    scale.z = temp;
}
