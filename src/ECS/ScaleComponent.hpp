#pragma once
#include <glm/vec3.hpp>

#include "ECS.hpp"

class ScaleComponent : public Component {
  public:
    /**
     * @brief Default Constructor for Scale Component
     */
    ScaleComponent();
    /**
     * @brief Default Destructor for Scale Component
     */
    ~ScaleComponent();

    ScaleComponent(glm::vec3 temp);
    /**
     * @brief Init function inheritred from component
     */
    void init();
    /**
     * @brief Update function inheritred from component
     */
    void update();
    /**
     * @brief Draw function inheritred from component
     */
    void draw();

    auto getXScale() -> float;
    auto getYScale() -> float;
    auto getZScale() -> float;
    auto getScale() -> glm::vec3;
    /**
     * @brief Sets the of the object
     * @param temp Vec3 object
     */
    auto setScale(glm::vec3 temp) -> void;
    /**
     * @brief Sets X scale of the object
     * @param temp float object
     */
    auto setXScale(float temp) -> void;
    /**
     * @brief Sets the Y scale of the object
     * @param temp float object
     */
    auto setYScale(float temp) -> void;
    /**
     * @brief Sets the Z scale of the object
     * @param temp float object
     */
    auto setZScale(float temp) -> void;

  private:
    /// vec to hold the scale propreties
    glm::vec3 scale = {0, 0, 0};
};
