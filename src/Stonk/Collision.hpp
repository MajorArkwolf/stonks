#pragma once

#include <glm/vec3.hpp>

/**
 * @brief Axis-aligned bounding box.
 */
struct BoundingBox {
    glm::vec3 min{};
    glm::vec3 max{};

    static auto isColliding(const BoundingBox &lhs, const BoundingBox &rhs) -> bool;
    auto isColliding(const BoundingBox &rhs) -> bool;
};

/**
 * @ Stonk collision subsystem.
 */
// struct Collision {};
