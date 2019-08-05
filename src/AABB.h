//  AABH.h
//  Header file for the AABB class
//  Dynamic Array used to store the co-ordinates of the bounding boxes used for
//  collsion detection.  The array is only used initially before being copied
//  into AABB Linked Lists. The array is then terminated.
//
//  I created this class originally before using linked lists to store the BB
//  info. But decided to keep it has the stored data can be easily copied across
//  into different linked lists in any prefered order. (i.e. the data is copied
//  into across into linked lists for different quadrants)
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef AABB_H
#    define AABB_H

#    include <cmath>
#    include "Glut.hpp"

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
    // dynamic array to store info
    BoundingBox *m_BBox = nullptr;
    // number of BB created (i.e. array size)
    int m_NoOfBoxes = 0;
    // deletes arrays and clears memory
    void ClearBB(BoundingBox *&tempArray);

    // Privatised copy constructor and assignment operator
    AABB(const AABB &aabb) = default;
    AABB &operator=(const AABB &aabb) = default;

  public:
    AABB() = default;
    ~AABB() {
        ClearBB(m_BBox);
    }

    void SetMaxX(const int &tempIndex, const GLfloat &tempX);
    void SetMinX(const int &tempIndex, const GLfloat &tempX);
    void SetMaxY(const int &tempIndex, const GLfloat &tempY);
    void SetMinY(const int &tempIndex, const GLfloat &tempY);
    void SetMaxZ(const int &tempIndex, const GLfloat &tempZ);
    void SetMinZ(const int &tempIndex, const GLfloat &tempZ);
    void SetNoBoundingBoxes(const int &tempSize);

    GLfloat GetMaxX(const int &tempIndex);
    GLfloat GetMinX(const int &tempIndex);
    GLfloat GetMaxY(const int &tempIndex);
    GLfloat GetMinY(const int &tempIndex);
    GLfloat GetMaxZ(const int &tempIndex);
    GLfloat GetMinZ(const int &tempIndex);
    int GetNoBoundingBoxes();
};

#endif
