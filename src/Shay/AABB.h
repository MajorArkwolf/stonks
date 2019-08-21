#pragma once

/**
 * @class AABB
 * @brief  Stores data relating to collision information
 *
 * Collision detection used in the program.
 */

#include <cmath>
#include <vector>

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class AABB {
      private:
        struct XYZ {
            GLfloat x = 0.0, y = 0.0, z = 0.0;
        };

        struct BoundingBox {
            XYZ max{};
            XYZ min{};
        };

        std::vector<BoundingBox> m_BBox{};
        AABB(const AABB &aabb) = default;
        size_t currentAABB;
        AABB &operator=(const AABB &aabb) = default;

      public:
        AABB() = default;
        void SetMaxX(GLfloat tempX);
        void SetMinX(GLfloat tempX);
        void SetMaxY(GLfloat tempY);
        void SetMinY(GLfloat tempY);
        void SetMaxZ(GLfloat tempZ);
        void SetMinZ(GLfloat tempZ);
        GLfloat GetMaxX();
        GLfloat GetMinX();
        auto SetAABBIndex(size_t index) -> void;
        GLfloat GetMaxY();
        GLfloat GetMinY();
        GLfloat GetMaxZ();
        GLfloat GetMinZ();
        size_t GetNoBoundingBoxes();
        auto FinishAABB() -> void;
    };
}
