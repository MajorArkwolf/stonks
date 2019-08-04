//  AABBNODE.h
//  Header file for the AABBNODE class
//  Stores details for each bounding box used for collsion detection.  Each node
//  is stored in each link of the AABB Linked List

//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef AABBNODE_H
#    define AABBNODE_H

#    include <vector>

#    include "Glut.hpp"

//--------------------------------------------------------------------------------------

class AABBNode {
  public:
    AABBNode() {
        Clear();
    }
    virtual ~AABBNode() {
        Clear();
    }

    //----------------------------------------------------------------------------------

    void Clear();

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLfloat GetMaxX() {
        return m_BBox.max.x;
    }
    GLfloat GetMinX() {
        return m_BBox.min.x;
    }
    GLfloat GetMaxY() {
        return m_BBox.max.y;
    }
    GLfloat GetMinY() {
        return m_BBox.min.y;
    }
    GLfloat GetMaxZ() {
        return m_BBox.max.z;
    }
    GLfloat GetMinZ() {
        return m_BBox.min.z;
    }

    // Return the address of the link to the next node in the list
    AABBNode *GetNext() const {
        return m_next;
    }

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    void SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                 const GLfloat minY, const GLfloat maxZ, const GLfloat minZ);

    // Set the address of the link to the next node in the list
    void SetNext(AABBNode *next) {
        m_next = next;
    }

  private:
    // The address of the next node in the list
    AABBNode *m_next = nullptr;

    // stores x,y,z co-ordinates
    struct XYZ {
        GLfloat x = 0.0, y = 0.0, z = 0.0;
    };
    // stores max and min values of co-ordinates
    struct BoundingBox {
        XYZ max{};
        XYZ min{};
    };
    // stores above info
    BoundingBox m_BBox{};

    //----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    AABBNode(const AABBNode &newNode) = delete;
    AABBNode &operator=(const AABBNode &newNode) = delete;
};

#endif
//--------------------------------------------------------------------------------------
