#include "Components.hpp"
#include "Stonk/OpenGl.hpp"
#include <glm/vec3.hpp>

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


    auto getXScale() -> GLfloat {
        return scale.x;
    }
    auto getYScale() -> GLfloat {
        return scale.y;
    }
    auto getZScale() -> GLfloat {
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
     * @param temp GLfloat object
     */
	auto setXScale(GLfloat temp) -> void {
        scale.x = temp;
	}
    /**
     * @brief Sets the Y scale of the object
     * @param temp GLfloat object
     */
    auto setYScale(GLfloat temp) -> void {
        scale.y = temp;
    }
    /**
     * @brief Sets the Z scale of the object
     * @param temp GLfloat object
     */
    auto setZScale(GLfloat temp) -> void {
        scale.z = temp;
    }

  private:
	 ///vec to hold the scale propreties
    glm::vec3 scale = {0, 0, 0};
};
