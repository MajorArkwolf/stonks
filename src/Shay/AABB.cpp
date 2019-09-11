#include "AABB.hpp"

using Shay::AABB;

/**
 * @brief Sets the max X value for the bounding box
 * @param tempX The maxmimum x-coordinate
 */
void AABB::SetMaxX(GLfloat tempX) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.x = tempX;
}

/**
 * @brief Sets the min X value for the bounding box
 * @param tempX The minimum x-coordinate
 */
void AABB::SetMinX(GLfloat tempX) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.x = tempX;
}

/**
 * @brief Sets the max Y value for the bounding box
 * @param tempY The maxmimum y-coordinate
 */
void AABB::SetMaxY(GLfloat tempY) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.y = tempY;
}

/**
 * @brief Sets the min Y value for the bounding box
 * @param tempY The minimum y-coordinate
 */
void AABB::SetMinY(GLfloat tempY) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.y = tempY;
}

/**
 * @brief Sets the max Z value for the bounding box
 * @param tempZ The maxmimum z-coordinate
 */
void AABB::SetMaxZ(GLfloat tempZ) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.z = tempZ;
}

/**
 * @brief Sets the min Z value for the bounding box
 * @param tempZ The minimum z-coordinate
 */
void AABB::SetMinZ(GLfloat tempZ) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.z = tempZ;
}

/**
 * @brief Sets the index for the bounding box
 * @param index The index number to set the bounding box to
 */
auto AABB::SetAABBIndex(size_t index) -> void {
    this->currentAABB = index;
}

/**
 * @brief Finishes the AABB, what does this do
 */
auto AABB::FinishAABB() -> void {
    this->currentAABB++;
}

/**
 * @brief Returns the Max X coordinate of the bounding box
 * @return The max X coordinate
 */
GLfloat AABB::GetMaxX() {
    return m_BBox[this->currentAABB].max.x;
}

/**
 * @brief Returns the min X value for the bounding box
 * @return The min X coordinate
 */
GLfloat AABB::GetMinX() {
    return m_BBox[this->currentAABB].min.x;
}

/**
 * @brief Returns the max Y value for the bounding box
 * @return The max Y coordinate
 */
GLfloat AABB::GetMaxY() {
    return m_BBox[this->currentAABB].max.y;
}

/**
 * @brief Returns the min Y value for the bounding box
 * @return The min Y coordinate
 */
GLfloat AABB::GetMinY() {
    return m_BBox[this->currentAABB].min.y;
}

/**
 * @brief Returns the max Z value for the bounding box
 * @return The max Z coordinate
 */
GLfloat AABB::GetMaxZ() {
    return m_BBox[this->currentAABB].max.z;
}

/**
 * @brief Returns the min Z value for the bounding box
 * @return The min Z coordinate
 */
GLfloat AABB::GetMinZ() {
    return m_BBox[this->currentAABB].min.z;
}

/**
 * @brief Returns the number of bounding boxes
 * @return The bounding box index number
 */
size_t AABB::GetNoBoundingBoxes() {
    return m_BBox.size();
}
