#pragma once
#include <glm/vec3.hpp>

#include "../ObjLoader/ModelManager.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"
#include "ScaleComponent.hpp"
/* Models */
class ModelComponent : public Component {
  public:
    ModelComponent()  = default;
    ~ModelComponent() = default;

    void init() {
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
    void setModel(std::string filename) {
        hasModel = true;
        modelId  = ModelManager::GetModelID(filename);
    }
    void update() {}
    void draw() {
        glm::vec3 entityScale{1, 1, 1};
        glm::vec3 entityPos{0, 0, 0};
        float entityRotation = 0;
        if (hasModel) {
            if (hasScale) {
                entityScale =
                    this->entity->getComponent<ScaleComponent>().getScale();
            }
            if (this->entity->hasComponent<PositionComponent>()) {
                entityPos =
                    this->entity->getComponent<PositionComponent>().getPos();
                entityRotation =
                    this->entity->getComponent<PositionComponent>().getRotation();
            }
            ModelManager::DrawModel(this->modelId, entityRotation, entityScale,
                                    entityPos);
        }
    }

  private:
    size_t modelId = 0;
    bool hasModel  = false;
    bool hasScale  = false;
    ScaleComponent *scale = nullptr;
    bool hasPosition = false;
    PositionComponent *pos = nullptr;
};
