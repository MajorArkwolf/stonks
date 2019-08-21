#pragma once

#include <cstddef>

#include "AABB.h"
#include "AABBList.h"

namespace Shay {
    class Collision {
      public:
        Collision() = default;

        bool Collide(GLfloat endX, GLfloat endY, GLfloat endZ);
        void CreateLinkedList();
        auto FinishAABB() -> void;

        Collision(const Collision &coll) = delete;
        Collision &operator=(const Collision &coll) = delete;

        void SetAABBMaxX(float tempX);
        void SetAABBMinX(float tempX);
        void SetAABBMaxY(float tempY);
        void SetAABBMinY(float tempY);
        void SetAABBMaxZ(float tempZ);
        void SetAABBMinZ(float tempZ);
        void SetWorldX(float tempX);
        void SetWorldZ(float tempZ);
        float GetAABBMaxX();
        float GetAABBMinX();
        float GetAABBMaxY();
        float GetAABBMinY();
        float GetAABBMaxZ();
        float GetAABBMinZ();
        std::size_t GetNoBoundingBoxes();

      private:
        AABB m_AABB               = {};
        AABBList m_list[4]        = {};
        std::size_t m_listSize[4] = {};
        float m_worldSizeX        = 0.0;
        float m_worldSizeZ        = 0.0;

        bool CheckCollision(std::size_t index, GLfloat endX, GLfloat endY,
                            GLfloat endZ);
    };
}
