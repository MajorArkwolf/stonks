#pragma once

/**
 * @class AABBList
 * @brief AABB collision list array
 *
 * Updated Shay's Linklist format to a vector improving access speeds.
 */

#include <cstddef>
#include <vector>

#include "AABBNode.h"
#include "Stonk/OpenGl.hpp"

namespace Shay {
    class AABBList {
      public:
        AABBList() = default;

        AABBList(AABBList &&)      = default;
        AABBList(const AABBList &) = default;
        AABBList &operator=(AABBList &&) = default;
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
        std::vector<AABBNode> nodes{};
        void Delete();
        void Clear();
    };
};
