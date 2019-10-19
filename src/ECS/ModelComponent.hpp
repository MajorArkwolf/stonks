#pragma once
#include <glm/vec3.hpp>

#include "../ObjLoader/ModelManager.hpp"
#include "Components.hpp"
/* Models */
class ModelComponent : public Component {
public:
    void init() {
        this->modelId = 0;
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
        modelId = ModelManager::GetModelID(filename);
    }
    void update() {}
    void draw() {
        if (hasModel) {
            if (hasScale) {
                ModelManager::DrawModel(this->modelId, this->scale->getScale(), this->pos->getPos());
            } else {
                ModelManager::DrawModel(this->modelId, this->pos->getPos());
            }
        }
    }

private:
    size_t modelId = 0;
    bool hasModel = false;
    bool hasScale = false;
    ScaleComponent * scale;
    bool hasPosition = false;
    PositionComponent * pos;
};
