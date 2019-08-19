#pragma once

#include "AABB.h"
#include "AABBList.h"

namespace Shay {
    class Collision {
      public:
        Collision() = default;

        //----------------------------------------------------------------------------------
        //  Set Methods
        //----------------------------------------------------------------------------------
        // sets initial co-ordinates of bounding boxes (these set the co-ords is AABB, the array,
        // the values for the list are copied from the array using CreateLinkedList).
        void SetAABBMaxX(const float &tempX) {
            m_AABB.SetMaxX(tempX);
        }
        void SetAABBMinX(const float &tempX) {
            m_AABB.SetMinX(tempX);
        }
        void SetAABBMaxY(const float &tempY) {
            m_AABB.SetMaxY(tempY);
        }
        void SetAABBMinY(const float &tempY) {
            m_AABB.SetMinY(tempY);
        }
        void SetAABBMaxZ(const float &tempZ) {
            m_AABB.SetMaxZ(tempZ);
        }
        void SetAABBMinZ(const float &tempZ) {
            m_AABB.SetMinZ(tempZ);
        }

        // sets the actual world co-ordinates
        void SetWorldX(const float &tempX) {
            m_worldSizeX = tempX;
        }
        void SetWorldZ(const float &tempZ) {
            m_worldSizeZ = tempZ;
        }

        //----------------------------------------------------------------------------------
        //  Returns Methods
        //----------------------------------------------------------------------------------
        // returns co-ordinates of bounding boxes
        float GetAABBMaxX() {
            return m_AABB.GetMaxX();
        }
        float GetAABBMinX() {
            return m_AABB.GetMinX();
        }
        float GetAABBMaxY() {
            return m_AABB.GetMaxY();
        }
        float GetAABBMinY() {
            return m_AABB.GetMinY();
        }
        float GetAABBMaxZ() {
            return m_AABB.GetMaxZ();
        }
        float GetAABBMinZ() {
            return m_AABB.GetMinZ();
        }

        // returns number of bounding boxes
        int GetNoBoundingBoxes() {
            return m_AABB.GetNoBoundingBoxes();
        }

        // returns TRUE if a collsion occurred
        bool Collide(GLfloat endX, GLfloat endY, GLfloat endZ);

        // reads the BB info from AABB (dynamic array) and creates a Linked List
        // containing BB data
        void CreateLinkedList();

        auto FinishAABB() -> void;

      private:
        // initially stores BB info in AABB (dynamic array) before copying to Linked List
        AABB m_AABB = {};

        // lists to store bounding box info in each quadrant
        AABBList m_list[4] = {};

        // Stores the list size of each linked list
        // Set to 4 has the world is split into 4 quadrants
        int m_listSize[4] = {};

        // stores world co-ordinates
        float m_worldSizeX = 0.0;
        float m_worldSizeZ = 0.0;

        // checks if collsion occurred (called from Collide)
        bool CheckCollision(int index, GLfloat endX, GLfloat endY, GLfloat endZ);

        //----------------------------------------------------------------------------------

        // Privatised copy constructor and assignment operator
        Collision(const Collision &coll) = delete;
        Collision &operator=(const Collision &coll) = delete;
    };
};
