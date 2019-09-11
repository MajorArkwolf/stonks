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
        /**
         * @brief Sets the max X value for the bounding box
         * @param tempX The maxmimum x-coordinate
         */
        void SetMaxX(GLfloat tempX);

        /**
         * @brief Sets the min X value for the bounding box
         * @param tempX The minimum x-coordinate
         */
        void SetMinX(GLfloat tempX);

        /**
         * @brief Sets the max Y value for the bounding box
         * @param tempY The maxmimum y-coordinate
         */
        void SetMaxY(GLfloat tempY);

        /**
         * @brief Sets the min Y value for the bounding box
         * @param tempY The minimum y-coordinate
         */
        void SetMinY(GLfloat tempY);

        /**
         * @brief Sets the max Z value for the bounding box
         * @param tempZ The maxmimum z-coordinate
         */
        void SetMaxZ(GLfloat tempZ);

        /**
         * @brief Sets the min Z value for the bounding box
         * @param tempZ The minimum z-coordinate
         */
        void SetMinZ(GLfloat tempZ);

        /**
         * @brief Returns the Max X coordinate of the bounding box
         * @return The max X coordinate
         */
        GLfloat GetMaxX();

        /**
         * @brief Returns the min X value for the bounding box
         * @return The min X coordinate
         */
        GLfloat GetMinX();

        /**
         * @brief Sets the index for the bounding box
         * @param index The index number to set the bounding box to
         */
        auto SetAABBIndex(size_t index) -> void;

        /**
         * @brief Returns the max Y value for the bounding box
         * @return The max Y coordinate
         */
        GLfloat GetMaxY();

        /**
         * @brief Returns the min Y value for the bounding box
         * @return The min Y coordinate
         */
        GLfloat GetMinY();

        /**
         * @brief Returns the max Z value for the bounding box
         * @return The max Z coordinate
         */
        GLfloat GetMaxZ();

        /**
         * @brief Returns the min Z value for the bounding box
         * @return The min Z coordinate
         */

        GLfloat GetMinZ();

        /**
         * @brief Returns the number of bounding boxes
         * @return The bounding box index number
         */
        size_t GetNoBoundingBoxes();

        /**
         * @brief Finishes the AABB, what does this do
         */
        auto FinishAABB() -> void;
    };
}
