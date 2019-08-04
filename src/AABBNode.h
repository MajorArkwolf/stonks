/**
 * @class AABBNode
 * @brief  Stores data relating to collision information
 *
 * Used inside of the AABBList file
 *
 * @author Peter Crabbe
 * @version 02
 * @date 04/08/2019
 *
 */

#ifndef AABBNODE_H
#define AABBNODE_H

#include "Glut.hpp"

class AABBNode {
  public:
    /**
     * @brief Default constructor, not required
     */
    AABBNode() = default;

    /**
     * @brief Default Copy Constructor
     * @param AABBNode &newNode
     */
    AABBNode(const AABBNode &newNode) = default;

    /**
     * @brief Default Copy assignment
     * @param AABBNode &newNode
     */
    AABBNode &operator=(const AABBNode &newNode) = default;

    /*
     * @brief Gets the Max X value from the node
     * @param GLfloat
     */
    GLfloat GetMaxX();

    /*
     * @brief Gets the Min X value from the node
     * @param GLfloat
     */
    GLfloat GetMinX();

    /*
     * @brief Gets the Max Y value from the node
     * @param GLfloat
     */
    GLfloat GetMaxY();

    /*
     * @brief Gets the Min Y value from the node
     * @param GLfloat
     */
    GLfloat GetMinY();

    /*
     * @brief Gets the Max Z value from the node
     * @param GLfloat
     */
    GLfloat GetMaxZ();

    /*
     * @brief Gets the Min Z value from the node
     * @param GLfloat
     */
    GLfloat GetMinZ();

    /**
     * @brief  Sets the data at the given point in the array.
     *
     * @param  const int &ptrCount
     * @param  const GLfloat maxX
     * @param  const GLfloat minX
     * @param  const GLfloat maxY
     * @param  const GLfloat minY
     * @param  const GLfloat maxZ
     * @param  const GLfloat minZ
     * @return bool
     */
    void SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                 const GLfloat minY, const GLfloat maxZ, const GLfloat minZ);

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
    /// stores above info
    BoundingBox m_BBox{};
};

#endif
