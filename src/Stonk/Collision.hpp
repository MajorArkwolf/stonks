#pragma once

#include <glm/vec3.hpp>

namespace Stonk {
    /**
     * @brief Axis-aligned bounding box.
     */
    struct BoundingBox {

        /// Start coordinate of the bounding box
        glm::vec3 min{};

        /// End coordinate of the bounding box
        glm::vec3 max{};

        static auto isColliding(const BoundingBox &lhs, const BoundingBox &rhs)
            -> bool;
        auto isColliding(const BoundingBox &rhs) -> bool;
    };

    /**
     * @ Stonk collision subsystem.
     */
    // struct Collision {};
}
