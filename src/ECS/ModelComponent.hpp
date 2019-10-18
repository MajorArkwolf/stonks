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
        this->scale = 1;
    }
    void setModel(std::string filename) {
        hasModel = true;
        modelId = ModelManager::GetModelID(filename);
    }
    void update() {}
    void draw() {
        if (hasModel) {
            ModelManager::DrawModel(this->modelId, this->scale, this->offset);
        }
    }
    auto offset() -> glm::vec3& {
        return this->offset;
    }
    auto scale() -> float& {
        return this->scale;
    }
private:
    size_t modelId;
    bool hasModel;
    glm::vec3 offset;
    float scale;
};
