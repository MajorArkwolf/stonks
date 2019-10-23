#include "ScaleComponent.hpp"

ScaleComponent::ScaleComponent()  = default;
ScaleComponent::~ScaleComponent() = default;

ScaleComponent::ScaleComponent(glm::vec3 temp) {
    scale = temp;
}
void ScaleComponent::init() {}
void ScaleComponent::update() {}
void ScaleComponent::draw() {}

auto ScaleComponent::getXScale() -> float {
    return scale.x;
}
auto ScaleComponent::getYScale() -> float {
    return scale.y;
}
auto ScaleComponent::getZScale() -> float {
    return scale.z;
}
auto ScaleComponent::getScale() -> glm::vec3 {
    return scale;
}
auto ScaleComponent::setScale(glm::vec3 temp) -> void {
    scale.x = temp.x;
    scale.y = temp.y;
    scale.z = temp.z;
}
auto ScaleComponent::setXScale(float temp) -> void {
    scale.x = temp;
}
auto ScaleComponent::setYScale(float temp) -> void {
    scale.y = temp;
}
auto ScaleComponent::setZScale(float temp) -> void {
    scale.z = temp;
}
