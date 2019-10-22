#pragma once
#include <glm/vec3.hpp>
#include "ECS.hpp"


class ScaleComponent : public Component {
  public:
    /**
     * @brief Default Constructor for Scale Component
     */
    ScaleComponent()   = default;
    /**
     * @brief Default Destructor for Scale Component
     */
    ~ScaleComponent() = default;

	ScaleComponent(glm::vec3 temp) {
        scale = temp;
	}
    /**
     * @brief Init function inheritred from component
     */
    void init() {}
    /**
     * @brief Update function inheritred from component
     */
    void update() {}
    /**
     * @brief Draw function inheritred from component
     */
    void draw() {}


    auto getXScale() -> float {
        return scale.x;
    }
    auto getYScale() -> float {
        return scale.y;
    }
    auto getZScale() -> float {
        return scale.z;
    }
	auto getScale() -> glm::vec3{
        return scale;
	}
    /**
     * @brief Sets the of the object
     * @param temp Vec3 object
     */
	auto setScale(glm::vec3 temp) {
        scale.x = temp.x;
        scale.y = temp.y;
        scale.z = temp.z;
	}
    /**
     * @brief Sets X scale of the object
     * @param temp float object
     */
	auto setXScale(float temp) -> void {
        scale.x = temp;
	}
    /**
     * @brief Sets the Y scale of the object
     * @param temp float object
     */
    auto setYScale(float temp) -> void {
        scale.y = temp;
    }
    /**
     * @brief Sets the Z scale of the object
     * @param temp float object
     */
    auto setZScale(float temp) -> void {
        scale.z = temp;
    }

  private:
	 ///vec to hold the scale propreties
    glm::vec3 scale = {0, 0, 0};
};
