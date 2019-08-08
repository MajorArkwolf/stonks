#include "Collision.hpp"

auto BoundingBox::isColliding(const BoundingBox &lhs, const BoundingBox &rhs)
    -> bool {
    return lhs.min.x < rhs.max.x && //
           lhs.max.y > rhs.min.y && //
           lhs.min.y < rhs.max.y && //
           lhs.max.z > rhs.min.z && //
           lhs.min.z < rhs.max.z;
}

auto BoundingBox::isColliding(const BoundingBox &rhs) -> bool {
    return BoundingBox::isColliding(*this, rhs);
}
