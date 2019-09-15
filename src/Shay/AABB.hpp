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

    /**
     * @class AABB
     * @brief A class used to store information about an Axis Aligned Bounding Box
     */
    class AABB {
      private:
        /**
         * @brief A struct used to contain a 3d coordinate ( Should really have called it a 3d vector)s
         */
        struct XYZ {
            GLfloat x = 0.0, y = 0.0, z = 0.0;
        };

        /**
         * @brief A struct for containg the maximum and minimum positions for the bounding box
         */
        struct BoundingBox {
            XYZ max{};
            XYZ min{};
        };

        /// A vector of bounding boxes
        std::vector<BoundingBox> m_BBox{};

        /**
         * @brief Copy constructor, set to default
         */
        AABB(const AABB &aabb) = default;

        /// The current number of AABB's
        size_t currentAABB;

        /**
         * @brief Overloaded assignment operator, set to default
         */
        AABB &operator=(const AABB &aabb) = default;

      public:
        /**
         * @brief Default constructor, set to default
         */
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
