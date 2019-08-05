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

#ifndef AABB_H
#define AABB_H

#include <cmath>
#include <vector>

#include "Glut.hpp"

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
     * @brief Copy assignment.
     * @param aabb Other AABB.
     */
    AABB &operator=(const AABB &aabb) = default;

  public:
    AABB() = default;
    ~AABB() {
        m_BBox.clear();
    }

    void SetMaxX(const int &tempIndex, const GLfloat &tempX);
    void SetMinX(const int &tempIndex, const GLfloat &tempX);
    void SetMaxY(const int &tempIndex, const GLfloat &tempY);
    void SetMinY(const int &tempIndex, const GLfloat &tempY);
    void SetMaxZ(const int &tempIndex, const GLfloat &tempZ);
    void SetMinZ(const int &tempIndex, const GLfloat &tempZ);
    void SetNoBoundingBoxes(const int &size);

    GLfloat GetMaxX(const int &tempIndex);
    GLfloat GetMinX(const int &tempIndex);
    GLfloat GetMaxY(const int &tempIndex);
    GLfloat GetMinY(const int &tempIndex);
    GLfloat GetMaxZ(const int &tempIndex);
    GLfloat GetMinZ(const int &tempIndex);
    int GetNoBoundingBoxes();
};

#endif
