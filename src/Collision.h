//  collsion.h
//  Header file for the collision class
//
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef COLLISION_H
#    define COLLISION_H

//--------------------------------------------------------------------------------------

#    include "AABB.h"
#    include "AABBList.h"

//--------------------------------------------------------------------------------------

class Collision {
  public:
    Collision() {}
    virtual ~Collision() {}

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    // sets initial co-ordinates of bounding boxes (these set the co-ords is AABB, the array,
    // the values for the list are copied from the array using CreateLinkedList).
    void SetAABBMaxX(const int &tempIndex, const float &tempX) {
        m_AABB.SetMaxX(tempIndex, tempX);
    }
    void SetAABBMinX(const int &tempIndex, const float &tempX) {
        m_AABB.SetMinX(tempIndex, tempX);
    }
    void SetAABBMaxY(const int &tempIndex, const float &tempY) {
        m_AABB.SetMaxY(tempIndex, tempY);
    }
    void SetAABBMinY(const int &tempIndex, const float &tempY) {
        m_AABB.SetMinY(tempIndex, tempY);
    }
    void SetAABBMaxZ(const int &tempIndex, const float &tempZ) {
        m_AABB.SetMaxZ(tempIndex, tempZ);
    }
    void SetAABBMinZ(const int &tempIndex, const float &tempZ) {
        m_AABB.SetMinZ(tempIndex, tempZ);
    }

    // sets the actual world co-ordinates
    void SetWorldX(const float &tempX) {
        m_worldSizeX = tempX;
    }
    void SetWorldZ(const float &tempZ) {
        m_worldSizeZ = tempZ;
    }

    // set number of bounding boxes
    void SetNoBoundingBoxes(const int &tempSize) {
        m_AABB.SetNoBoundingBoxes(tempSize);
    }

    //----------------------------------------------------------------------------------
    //  Returns Methods
    //----------------------------------------------------------------------------------
    // returns co-ordinates of bounding boxes
    float GetAABBMaxX(const int &tempIndex) {
        return m_AABB.GetMaxX(tempIndex);
    }
    float GetAABBMinX(const int &tempIndex) {
        return m_AABB.GetMinX(tempIndex);
    }
    float GetAABBMaxY(const int &tempIndex) {
        return m_AABB.GetMaxY(tempIndex);
    }
    float GetAABBMinY(const int &tempIndex) {
        return m_AABB.GetMinY(tempIndex);
    }
    float GetAABBMaxZ(const int &tempIndex) {
        return m_AABB.GetMaxZ(tempIndex);
    }
    float GetAABBMinZ(const int &tempIndex) {
        return m_AABB.GetMinZ(tempIndex);
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

#endif
//--------------------------------------------------------------------------------------
