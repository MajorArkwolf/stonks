#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace Stonk {
    /**
     * @brief Base class for 3D entities.
     */
    struct Entity {
        glm::vec3 position     = {};
        glm::vec3 velocity     = {};
        glm::vec3 acceleration = {};
        glm::vec3 rotation     = {};
        double scale           = {};
    };
}
