#pragma once
#include <glm/vec3.hpp>

#include "../ObjLoader/ModelManager.hpp"
#include "ECS.hpp"
#include "PositionComponent.hpp"
#include "ScaleComponent.hpp"
/**
 * @brief ECS model component
 */
class ModelComponent : public Component {
  public:
    /**
     * @brief ctor
     */
    ModelComponent();
    /**
     * @brief dtor
     */
    ~ModelComponent();
    /**
     * @brief Init
     */
    void init();
    /**
     * @brief Set model
     */
    void setModel(std::string filename);
    /**
     * @brief Update
     */
    void update();
    /**
     * @brief Draw
     */
    void draw();
    void unSetModel();
  private:
    /**
     * The model ID used by this component
     */
    size_t modelId = 0;
    /**
     * Is a model loaded?
     */
    bool hasModel = false;
    /**
     * Has a scale component been found?
     */
    bool hasScale = false;
    /**
     * Scale component
     */
    ScaleComponent *scale = nullptr;
    /**
     * Has a position component been found?
     */
    bool hasPosition = false;
    /**
     * Position component
     */
    PositionComponent *pos = nullptr;
};
