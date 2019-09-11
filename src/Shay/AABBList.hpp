#pragma once

/**
 * @class AABBList
 * @brief AABB collision list array
 *
 * Updated Shay's Linklist format to a vector improving access speeds.
 */

#include <cstddef>
#include <vector>

#include "AABBNode.hpp"
#include "Stonk/OpenGl.hpp"

namespace Shay {

    /**
     * @class AABBList
     * @brief A class used for storing a number of Axis Aligned Bounding Boxes
     */
    class AABBList {
      public:
        /**
         * @brief  Default constructor, set to default
         */
        AABBList() = default;

        /**
         * @brief  Copy constructor, set to default
         */
        AABBList(AABBList &&) = default;

        /**
         * @brief  Const copy constructor, set to default
         */
        AABBList(const AABBList &) = default;

        /**
         * @brief  Assignment operator overload, set to default
         */
        AABBList &operator=(AABBList &&) = default;

        /**
         * @brief  Const assignment operator overload, set to default
         */
        AABBList &operator=(const AABBList &) = default;

        bool AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                        GLfloat maxZ, GLfloat minZ);

        void SetData(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                     GLfloat maxZ, GLfloat minZ);

        GLfloat GetMaxX(std::size_t ptrCount);
        GLfloat GetMinX(std::size_t ptrCount);
        GLfloat GetMaxY(std::size_t ptrCount);
        GLfloat GetMinY(std::size_t ptrCount);
        GLfloat GetMaxZ(std::size_t ptrCount);
        GLfloat GetMinZ(std::size_t ptrCount);
        std::size_t GetListSize();

      private:
        /// A vector used to store AABB's
        std::vector<AABBNode> nodes{};
        void Delete();
        void Clear();
    };
}
