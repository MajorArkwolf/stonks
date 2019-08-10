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

#include "OpenGl.hpp"

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
     * @brief Setter for Max X variable.
     * @param index Access to element in vector.
     * @param tempX Sets the value.
     */
    void SetMaxX(size_t index, GLfloat tempX);

    /**
     * @brief Setter for Min X variable.
     * @param index Access to element in vector.
     * @param temp Sets the value.
     */
    void SetMinX(size_t index, GLfloat tempX);

    /**
     * @brief Setter for Max Y variable.
     * @param index Access to element in vector.
     * @param temp Sets the value.
     */
    void SetMaxY(size_t index, GLfloat tempY);

    /**
     * @brief Setter for Min Y variable.
     * @param index Access to element in vector.
     * @param temp Sets the value.
     */
    void SetMinY(size_t index, GLfloat tempY);

    /**
     * @brief Setter for Max Z variable.
     * @param index Access to element in vector.
     * @param temp Sets the value.
     */
    void SetMaxZ(size_t index, GLfloat tempZ);

    /**
     * @brief Setter for Min Z variable.
     * @param index Access to element in vector.
     * @param temp Sets the value.
     */
    void SetMinZ(size_t index, GLfloat tempZ);

    /**
     * @brief Setter for Min Z variable.
     * @param size returns the size of the vector.
     */
    void SetNoBoundingBoxes(size_t size);

    /**
     * @brief Getter for Max X variable.
     * @param index Access to element in vector.
     * @return MaxX GLfloat used for collision.
     */
    GLfloat GetMaxX(size_t index);

    /**
     * @brief Getter for Min X variable.
     * @param index Access to element in vector.
     * @return MinX GLfloat used for collision.
     */
    GLfloat GetMinX(size_t index);

    /**
     * @brief Getter for Max Y variable.
     * @param index Access to element in vector.
     * @return MaxY GLfloat used for collision.
     */
    GLfloat GetMaxY(size_t index);

    /**
     * @brief Getter for Min Y variable.
     * @param index Access to element in vector.
     * @return MinY GLfloat used for collision.
     */
    GLfloat GetMinY(size_t index);

    /**
     * @brief Getter for Max z variable.
     * @param index Access to element in vector.
     * @return MaxZ GLfloat used for collision.
     */
    GLfloat GetMaxZ(size_t index);

    /**
     * @brief Getter for Min Z variable.
     * @param index Access to element in vector.
     * @return MinZ GLfloat used for collision.
     */
    GLfloat GetMinZ(size_t index);

    /**
     * @brief Getter for vector size.
     * @return size used to determine size of array.
     */
    size_t GetNoBoundingBoxes();
};

#endif
