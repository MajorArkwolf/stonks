#pragma once

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Stonk {
    /**
     * @brief Stonk camera subsystem.
     */
    struct Camera {
        /// The current position of the camera
        glm::vec3 position = {};

        /// The current look position of the camera
        glm::vec3 look = {0.0, 0.0, 0.0};

        /// The current tilt values of the camera
        glm::vec3 tilt = {0.0, 1.0, 0.0};

        /// The current angle values of the camera
        glm::vec2 angles = {glm::pi<double>(), 0};
    };
}
