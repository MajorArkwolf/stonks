#include "ModelComponent.hpp"
#include "DeadComponent.hpp"

/**
 * @brief  Default Constructor
 */
ModelComponent::ModelComponent()  = default;

/**
 * @brief  Default Destructor
 */
ModelComponent::~ModelComponent() = default;

/**
 * @brief  gets all the model information from other components
 */
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

/**
 * @brief  gets all the model information from other components
 * @param  filename the location to the model
 */
void ModelComponent::setModel(std::string filename) {
    hasModel = true;
    modelId  = ModelManager::GetModelID(filename);
}

/**
 * @brief  Removes the model to stop it from being drawn
 */
void ModelComponent::unSetModel() {
    hasModel = false;
    modelId  = 0;
}

/**
 * @brief  Unused
 */
void ModelComponent::update() {}

/**
 * @brief  Draws the model
 */
void ModelComponent::draw() {
    if (!this->entity->hasComponent<DeadComponent>()) {
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
}
