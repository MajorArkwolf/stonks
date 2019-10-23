#include "ModelComponent.hpp"

ModelComponent::ModelComponent()  = default;
ModelComponent::~ModelComponent() = default;
void ModelComponent::init() {
    this->modelId  = 0;
    this->hasModel = false;
    this->hasScale = this->entity->hasComponent<ScaleComponent>();
    if (hasScale) {
        this->scale = &this->entity->getComponent<ScaleComponent>();
    }
    this->hasPosition = this->entity->hasComponent<PositionComponent>();
    if (hasPosition) {
        this->pos = &this->entity->getComponent<PositionComponent>();
    }
}
void ModelComponent::setModel(std::string filename) {
    hasModel = true;
    modelId  = ModelManager::GetModelID(filename);
}
void ModelComponent::update() {}
void ModelComponent::draw() {
    glm::vec3 entityScale{1, 1, 1};
    glm::vec3 entityPos{0, 0, 0};
    float entityRotation = 0;
    if (hasModel) {
        if (hasScale) {
            entityScale = this->entity->getComponent<ScaleComponent>().getScale();
        }
        if (this->entity->hasComponent<PositionComponent>()) {
            entityPos = this->entity->getComponent<PositionComponent>().getPos();
            entityRotation =
                this->entity->getComponent<PositionComponent>().getRotation();
        }
        ModelManager::DrawModel(this->modelId, entityRotation, entityScale,
                                entityPos);
    }
}
