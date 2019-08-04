//  AABBNODE.h
//  Header file for the AABBNODE class
//  Stores details for each bounding box used for collsion detection.  Each node
//  is stored in each link of the AABB Linked List

//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef AABBNODE_H
#    define AABBNODE_H

#    include "Glut.hpp"

//--------------------------------------------------------------------------------------

class AABBNode {
  public:
    AABBNode() = default;
    AABBNode(const AABBNode &newNode) = default;
    AABBNode &operator=(const AABBNode &newNode) = default;

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

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    void SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                 const GLfloat minY, const GLfloat maxZ, const GLfloat minZ);

  private:
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
};

#endif
//--------------------------------------------------------------------------------------
