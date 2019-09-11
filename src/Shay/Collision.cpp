#include "Collision.hpp"

#include <cstddef>

using Shay::Collision;
using std::size_t;

/**
 * @brief Creates a linked list for each quadrant and then copies the bounding box data from
 *  AABB (array) to the required linked list.
 *  I initially just created AABB, then decided to place the bounding box info into a list.
 *  I kept the array has it allows for the data to be copied into the list in any reuired
 *  order.
 */
void Collision::CreateLinkedList() {
    size_t tempNoBoxes = GetNoBoundingBoxes();
    // initilize list size for each quadrant
    m_listSize[0] = 0;
    m_listSize[1] = 0;
    m_listSize[2] = 0;
    m_listSize[3] = 0;

    for (size_t count = 0; count < tempNoBoxes; count++) {
        this->m_AABB.SetAABBIndex(count);
        GLfloat maxX = GetAABBMaxX();
        GLfloat minX = GetAABBMinX();
        GLfloat maxY = GetAABBMaxY();
        GLfloat minY = GetAABBMinY();
        GLfloat maxZ = GetAABBMaxZ();
        GLfloat minZ = GetAABBMinZ();
        // 1st quadrant
        if (((minX <= m_worldSizeX / 2.0f) || (maxX <= m_worldSizeX / 2.0f)) &&
            ((minZ <= m_worldSizeZ / 2.0f) || (maxZ <= m_worldSizeZ / 2.0f))) {
            // increment list size
            m_listSize[0]++;
            // add bb data to list
            m_list[0].AddToStart(maxX, minX, maxY, minY, maxZ, minZ);
        }
        // 2nd quadrant
        if (((minX <= m_worldSizeX / 2.0f) || (maxX <= m_worldSizeX / 2.0f)) &&
            ((minZ >= m_worldSizeZ / 2.0f) || (maxZ >= m_worldSizeZ / 2.0f))) {
            // increment list size
            m_listSize[1]++;
            // add bb data to list
            m_list[1].AddToStart(maxX, minX, maxY, minY, maxZ, minZ);
        }
        // 3rd quadrant
        if (((minX >= m_worldSizeX / 2.0f) || (maxX >= m_worldSizeX / 2.0f)) &&
            ((minZ <= m_worldSizeZ / 2.0f) || (maxZ <= m_worldSizeZ / 2.0f))) {
            // increment list size
            m_listSize[2]++;
            // add bb data to list
            m_list[2].AddToStart(maxX, minX, maxY, minY, maxZ, minZ);
        }
        // 4th quadrant
        if (((minX >= m_worldSizeX / 2.0f) || (maxX >= m_worldSizeX / 2.0f)) &&
            ((minZ >= m_worldSizeZ / 2.0f) || (maxZ >= m_worldSizeZ / 2.0f))) {
            // increment list size
            m_listSize[3]++;
            // add bb data to list
            m_list[3].AddToStart(maxX, minX, maxY, minY, maxZ, minZ);
        }
    }
}

/**
 * @brief   Returns TRUE if a collsion occurs.
 * The parameters passed to this function are the co-ordinates of the camera.
 *  At present this function uses if statements to split the world into
 * quadrants this is to be improved (for the project) so that the quadrants (or
 * levels) are stored in a list or tree data structure.
 *
 * @param endX The end X coordinate
 * @param endY The end Y coordinate
 * @param endZ The end Z coordinate
 * @return Returns TRUE if a collision occurs
 */
bool Collision::Collide(GLfloat endX, GLfloat endY, GLfloat endZ) {
    bool Collision = false;
    // check 1st quadrant (1st linked list)
    if (((endX <= m_worldSizeX / 2.0f) || (endX <= m_worldSizeX / 2.0f)) &&
        ((endZ <= m_worldSizeZ / 2.0f) || (endZ <= m_worldSizeZ / 2.0f))) {
        Collision = CheckCollision(0, endX, endY, endZ);
    }
    // check 2nd quadrant (2nd linked list)
    if (((endX <= m_worldSizeX / 2.0f) || (endX <= m_worldSizeX / 2.0f)) &&
        ((endZ >= m_worldSizeZ / 2.0f) || (endZ >= m_worldSizeZ / 2.0f))) {
        Collision = CheckCollision(1, endX, endY, endZ);
    }
    // check 3rd quadrant (3rd linked list)
    if (((endX >= m_worldSizeX / 2.0f) || (endX >= m_worldSizeX / 2.0f)) &&
        ((endZ <= m_worldSizeZ / 2.0f) || (endZ <= m_worldSizeZ / 2.0f))) {
        Collision = CheckCollision(2, endX, endY, endZ);
    }
    // check 4th quadrant (4th linked list)
    if (((endX >= m_worldSizeX / 2.0f) || (endX >= m_worldSizeX / 2.0f)) &&
        ((endZ >= m_worldSizeZ / 2.0f) || (endZ >= m_worldSizeZ / 2.0f))) {
        Collision = CheckCollision(3, endX, endY, endZ);
    }
    return Collision;
}

/**
 * @brief   Returns TRUE if a collsion occurs.
 * The parameters passed to this function are the co-ordinates of the camera.
 *  At present this function uses if statements to split the world into
 * quadrants this is to be improved (for the project) so that the quadrants (or
 * levels) are stored in a list or tree data structure.
 *
 * @param index The index location to check for a collision in
 * @param endX The end X coordinate
 * @param endY The end Y coordinate
 * @param endZ The end Z coordinate
 * @return Returns TRUE if a collision occurs
 */
bool Collision::CheckCollision(size_t index, GLfloat endX,
                               [[maybe_unused]] GLfloat endY, GLfloat endZ) {
    bool CollisionFound = false;
    for (size_t count = 0; count < m_listSize[index]; count++) {
        if (((endX < m_list[index].GetMaxX(count)) &&
             (endX > m_list[index].GetMinX(count))) &&
            ((endZ < m_list[index].GetMaxZ(count)) &&
             (endZ > m_list[index].GetMinZ(count)))) {
            CollisionFound = true;
        }
    }
    return CollisionFound;
}

/**
 * @brief  Finishes current AABB by incrementing AABB count
 */

auto Collision::Collision::FinishAABB() -> void {
    m_AABB.FinishAABB();
}

/**
 * @brief Sets the maximum X value for the AABB
 * @param tempX The X value to set as maximum
 */
void Collision::SetAABBMaxX(float tempX) {
    m_AABB.SetMaxX(tempX);
}

/**
 * @brief Sets the minimum X value for the AABB
 * @param tempX The X value to set as minimum
 */
void Collision::SetAABBMinX(float tempX) {
    m_AABB.SetMinX(tempX);
}

/**
 * @brief Sets the maximum Y value for the AABB
 * @param tempY The Y value to set as maximum
 */
void Collision::SetAABBMaxY(float tempY) {
    m_AABB.SetMaxY(tempY);
}

/**
 * @brief Sets the minimum Y value for the AABB
 * @param tempY The Y value to set as minimum
 */
void Collision::SetAABBMinY(float tempY) {
    m_AABB.SetMinY(tempY);
}

/**
 * @brief Sets the maximum Z value for the AABB
 * @param tempZ The Z value to set as maximum
 */
void Collision::SetAABBMaxZ(float tempZ) {
    m_AABB.SetMaxZ(tempZ);
}

/**
 * @brief Sets the minimum Z value for the AABB
 * @param tempZ The Z value to set as minimum
 */
void Collision::SetAABBMinZ(float tempZ) {
    m_AABB.SetMinZ(tempZ);
}

/**
 * @brief Sets X value of the world size
 * @param tempX The X value to set as world size
 */
void Collision::SetWorldX(float tempX) {
    m_worldSizeX = tempX;
}

/**
 * @brief Sets Z value of the world size
 * @param tempZ The Z value to set as world size
 */
void Collision::SetWorldZ(float tempZ) {
    m_worldSizeZ = tempZ;
}

/**
 * @brief Gets the maximum X value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMaxX() {
    return m_AABB.GetMaxX();
}

/**
 * @brief Gets the minimum X value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMinX() {
    return m_AABB.GetMinX();
}

/**
 * @brief Gets the maximum Y value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMaxY() {
    return m_AABB.GetMaxY();
}

/**
 * @brief Gets the minimum Y value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMinY() {
    return m_AABB.GetMinY();
}

/**
 * @brief Gets the maximum Z value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMaxZ() {
    return m_AABB.GetMaxZ();
}
/**
 * @brief Gets the minimum Z value for the AABB
 * @return The coordinate value
 */
float Collision::GetAABBMinZ() {
    return m_AABB.GetMinZ();
}

/**
 * @brief Returns the number of bounding boxes
 * @return The number of bounding boxes
 */
size_t Collision::GetNoBoundingBoxes() {
    return m_AABB.GetNoBoundingBoxes();
}
