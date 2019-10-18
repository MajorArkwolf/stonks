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
        this->offset = {0,0,0};
        this->hasScale = this->entity->hasComponent<ScaleComponent>();
        if (hasScale) {
            this->scale = this->entity->getComponent<ScaleComponent>();
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
                ModelManager::DrawModel(this->modelId, this->scale.getScale(), this->offset);
            } else {
                ModelManager::DrawModel(this->modelId, this->offset);
            }
        }
    }
    auto offset() -> glm::vec3& {
        return this->offsetVec;
    }
private:
    size_t modelId;
    bool hasModel;
    glm::vec3 offsetVec;
    bool hasScale;
    ScaleComponent& scale;
};
