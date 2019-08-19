#pragma once

/**
 * @class AABB
 * @brief  Stores data relating to collision information
 *
 * Collission detection used in the program.
 *
 * @author Peter Crabbe
 * @version 02
 * @date 04/08/2019
 *
 */

#include <cmath>
#include <vector>

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class AABB {
      private:
        /// stores x,y,z co-ordinates
        struct XYZ {
            GLfloat x = 0.0, y = 0.0, z = 0.0;
        };
        /// stores max and min values of co-ordinates
        struct BoundingBox {
            XYZ max{};
            XYZ min{};
        };
        /// dynamic array to store info
        std::vector<BoundingBox> m_BBox{};

        /**
         * @brief Copy constructor.
         * @param aabb Other AABB.
         */
        AABB(const AABB &aabb) = default;

        /**
         * @brief Current AABB being edited
         */
        size_t currentAABB;

        /**
         * @brief Copy assignment.
         * @param aabb Other AABB.
         */
        AABB &operator=(const AABB &aabb) = default;

      public:
        /**
         * @brief Default constructor.
         */
        AABB() = default;

        /**
         * @brief Setter for Max X variable.
         * @param index Access to element in vector.
         * @param tempX Sets the value.
         */
        void SetMaxX(GLfloat tempX);

        /**
         * @brief Setter for Min X variable.
         * @param index Access to element in vector.
         * @param temp Sets the value.
         */
        void SetMinX(GLfloat tempX);

        /**
         * @brief Setter for Max Y variable.
         * @param index Access to element in vector.
         * @param temp Sets the value.
         */
        void SetMaxY(GLfloat tempY);

        /**
         * @brief Setter for Min Y variable.
         * @param index Access to element in vector.
         * @param temp Sets the value.
         */
        void SetMinY(GLfloat tempY);

        /**
         * @brief Setter for Max Z variable.
         * @param index Access to element in vector.
         * @param temp Sets the value.
         */
        void SetMaxZ(GLfloat tempZ);

        /**
         * @brief Setter for Min Z variable.
         * @param index Access to element in vector.
         * @param temp Sets the value.
         */
        void SetMinZ(GLfloat tempZ);

        /**
         * @brief Sets the index of the current AABB to be modified or viewed
         */
        auto SetAABBIndex(size_t index) -> void;

        /**
         * @brief Getter for Max X variable.
         * @param index Access to element in vector.
         * @return MaxX GLfloat used for collision.
         */
        GLfloat GetMaxX();

        /**
         * @brief Getter for Min X variable.
         * @param index Access to element in vector.
         * @return MinX GLfloat used for collision.
         */
        GLfloat GetMinX();

        /**
         * @brief Getter for Max Y variable.
         * @param index Access to element in vector.
         * @return MaxY GLfloat used for collision.
         */
        GLfloat GetMaxY();

        /**
         * @brief Getter for Min Y variable.
         * @param index Access to element in vector.
         * @return MinY GLfloat used for collision.
         */
        GLfloat GetMinY();

        /**
         * @brief Getter for Max z variable.
         * @param index Access to element in vector.
         * @return MaxZ GLfloat used for collision.
         */
        GLfloat GetMaxZ();

        /**
         * @brief Getter for Min Z variable.
         * @param index Access to element in vector.
         * @return MinZ GLfloat used for collision.
         */
        GLfloat GetMinZ();

        /**
         * @brief Getter for vector size.
         * @return size used to determine size of array.
         */
        size_t GetNoBoundingBoxes();

		/**
		 * @brief Finish the current AABB
		 */
		auto FinishAABB() -> void;
    };
};
