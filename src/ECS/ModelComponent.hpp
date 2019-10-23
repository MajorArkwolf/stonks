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

    void init();
    void setModel(std::string filename);
    void update();
    void draw();

  private:
    size_t modelId         = 0;
    bool hasModel          = false;
    bool hasScale          = false;
    ScaleComponent *scale  = nullptr;
    bool hasPosition       = false;
    PositionComponent *pos = nullptr;
};
