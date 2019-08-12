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

#include "Stonk/OpenGl.hpp"

class AABBNode {
  public:
    /**
     * @brief Default constructor, not required
     */
    AABBNode() = default;

    /**
     * @brief Default Copy Constructor
     */
    AABBNode(const AABBNode &newNode) = default;

    /**
     * @brief Default Copy assignment
     */
    AABBNode &operator=(const AABBNode &newNode) = default;

    /*
     * @brief Gets the Max X value from the node
     */
    GLfloat GetMaxX();

    /*
     * @brief Gets the Min X value from the node
     */
    GLfloat GetMinX();

    /*
     * @brief Gets the Max Y value from the node
     */
    GLfloat GetMaxY();

    /*
     * @brief Gets the Min Y value from the node
     */
    GLfloat GetMinY();

    /*
     * @brief Gets the Max Z value from the node
     */
    GLfloat GetMaxZ();

    /*
     * @brief Gets the Min Z value from the node
     */
    GLfloat GetMinZ();

    /**
     * @brief  Sets the data at the given point in the array.
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
