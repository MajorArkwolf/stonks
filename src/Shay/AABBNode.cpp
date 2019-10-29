#include "AABBNode.hpp"

using Shay::AABBNode;

/**
 * @brief  Sets the parameters of this bounding box
 * @param maxX Maximum X coordinate of the bounding box
 * @param minX Minimum X coordinate of the bounding box
 * @param maxY Maximum Y coordinate of the bounding box
 * @param minY Minimum Y coordinate of the bounding box
 * @param maxZ Maximum Z coordinate of the bounding box
 * @param minZ Minimum Z coordinate of the bounding box
 */
void AABBNode::SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                       const GLfloat minY, const GLfloat maxZ, const GLfloat minZ) {
    m_BBox.max.x = maxX;
    m_BBox.min.x = minX;
    m_BBox.max.y = maxY;
    m_BBox.min.y = minY;
    m_BBox.max.z = maxZ;
    m_BBox.min.z = minZ;
}

/**
 * @brief Returns the Max X coordinate of the bounding box
 * @return The max X coordinate
 */
GLfloat AABBNode::GetMaxX() {
    return m_BBox.max.x;
}

/**
 * @brief Returns the min X value for the bounding box
 * @return The min X coordinate
 */
GLfloat AABBNode::GetMinX() {
    return m_BBox.min.x;
}

/**
 * @brief Returns the max Y value for the bounding box
 * @return The max Y coordinate
 */
GLfloat AABBNode::GetMaxY() {
    return m_BBox.max.y;
}

/**
 * @brief Returns the min Y value for the bounding box
 * @return The min Y coordinate
 */
GLfloat AABBNode::GetMinY() {
    return m_BBox.min.y;
}

/**
 * @brief Returns the max Z value for the bounding box
 * @return The max Z coordinate
 */
GLfloat AABBNode::GetMaxZ() {
    return m_BBox.max.z;
}

/**
 * @brief Returns the min Z value for the bounding box
 * @return The min Z coordinate
 */
GLfloat AABBNode::GetMinZ() {
    return m_BBox.min.z;
}
