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
    /**
     * @brief Default constructor.
     */
    AABB() = default;

    /**
     * @brief Default constructor.
     */
    ~AABB() {
        m_BBox.clear();
    }

    /**
     * @brief Setter for Max X variable.
	 * @param tempIndex Access to element in vector.
	 * @param temp Sets the value to
     */
    void SetMaxX(size_t index, GLfloat tempX);
    void SetMinX(size_t index, GLfloat tempX);
    void SetMaxY(size_t index, GLfloat tempY);
    void SetMinY(size_t index, GLfloat tempY);
    void SetMaxZ(size_t index, GLfloat tempZ);
    void SetMinZ(size_t index, GLfloat tempZ);
    void SetNoBoundingBoxes(size_t size);

    GLfloat GetMaxX(size_t index);
    GLfloat GetMinX(size_t index);
    GLfloat GetMaxY(size_t index);
    GLfloat GetMinY(size_t index);
    GLfloat GetMaxZ(size_t index);
    GLfloat GetMinZ(size_t index);
    size_t GetNoBoundingBoxes();
};

#endif
