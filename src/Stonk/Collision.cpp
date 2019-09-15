#include "Stonk/Collision.hpp"

using Stonk::BoundingBox;

/**
 * @brief Returns true if the passed in bounding boxes are colliding
 * @param lhs First bounding box
 * @param rhs Second bounding box
 * @return True if bounding boxes are colliding
 */
auto BoundingBox::isColliding(const BoundingBox &lhs, const BoundingBox &rhs)
    -> bool {
    return lhs.min.x < rhs.max.x && //
           lhs.max.y > rhs.min.y && //
           lhs.min.y < rhs.max.y && //
           lhs.max.z > rhs.min.z && //
           lhs.min.z < rhs.max.z;
}

/**
 * @brief Returns true if the passed in bounding box is colliding with *this* bounding box
 * @param rhs Bounding box to check against
 * @return True if bounding boxes are colliding
 */
auto BoundingBox::isColliding(const BoundingBox &rhs) -> bool {
    return BoundingBox::isColliding(*this, rhs);
}
