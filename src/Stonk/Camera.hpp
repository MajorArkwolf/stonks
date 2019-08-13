#pragma once

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Stonk {
    /**
     * @brief Stonk camera subsystem.
     */
    struct Camera {
        glm::vec3 position = {};
        glm::vec3 look     = {0.0, 0.0, 0.0};
        glm::vec3 tilt     = {0.0, 1.0, 0.0};
        glm::vec2 angles   = {glm::pi<double>(), 0};
    };
};
