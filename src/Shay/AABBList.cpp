#include "AABBList.hpp"

#include <cstddef>

using Shay::AABBList;
using std::size_t;

/**
 * @brief  Creates a new AABB from the passed in parameters and adds it to the vector
 * @param maxX Maximum X coordinate of the bounding box
 * @param minX Minimum X coordinate of the bounding box
 * @param maxY Maximum Y coordinate of the bounding box
 * @param minY Minimum Y coordinate of the bounding box
 * @param maxZ Maximum Z coordinate of the bounding box
 * @param minZ Minimum Z coordinate of the bounding box
 */
bool AABBList::AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY,
                          GLfloat minY, GLfloat maxZ, GLfloat minZ) {
    // Creates a temp node.
    AABBNode newNode{};

    // adds the values to the node
    newNode.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    // Places the node at the end of the vector.
    nodes.push_back(newNode);

    return true;
}

/**
 * @brief  Returns the max X value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMaxX(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxX();
    else
        return 0;
}

/**
 * @brief  Returns the min X value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMinX(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinX();
    else
        return 0;
}

/**
 * @brief  Returns the max Y value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMaxY(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxY();
    else
        return 0;
}

/**
 * @brief  Returns the min Y value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMinY(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinY();
    else
        return 0;
}

/**
 * @brief  Returns the max Z value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMaxZ(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxZ();
    else
        return 0;
}

/**
 * @brief  Returns the min Z value at from the AABB at the given vector index
 * @param ptrCount The index of the vector to read from
 */
GLfloat AABBList::GetMinZ(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinZ();
    else
        return 0;
}

/**
 * @brief  Creates a new AABB from the passed in parameters and adds it to the vector
 * @param maxX Maximum X coordinate of the bounding box
 * @param minX Minimum X coordinate of the bounding box
 * @param maxY Maximum Y coordinate of the bounding box
 * @param minY Minimum Y coordinate of the bounding box
 * @param maxZ Maximum Z coordinate of the bounding box
 * @param minZ Minimum Z coordinate of the bounding box
 */
void AABBList::SetData(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                       GLfloat maxZ, GLfloat minZ) {
    AABBNode temp{};
    temp.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    nodes.push_back(temp);
}

/**
 * @brief  Returns the number of AABB's in the vector
 */
size_t AABBList::GetListSize() {
    size_t size = size_t(nodes.size());
    return size;
}

/**
 * @brief  Deletes all AABB's from the vector
 */
void AABBList::Delete() {
    nodes.clear();
}

/**
 * @brief  Deletes all AABB's from the vector
 */
void AABBList::Clear() {
    nodes.clear();
}
