#include "PlainLinkedList.hpp"

#include <cstddef>

#include "PlainNode.hpp"

using Shay::PlainLinkedList;
using Shay::PlainNode;

using Slope = PlainNode::Slope;
using std::size_t;

/**
 * @brief  Adds a slope to the end of the vector
 *
 * @param tempType Slope type
 * @param tempXs X start location
 * @param tempXe X end location
 * @param tempYs Y start location
 * @param tempYe Y end location
 * @param tempZs Z start location
 * @param tempZe Z end location
 * @return Returns TRUE if successfully added to vector
 */

bool PlainLinkedList::AddToStart(Slope tempType, GLfloat tempXs, GLfloat tempXe,
                                 GLfloat tempYs, GLfloat tempYe, GLfloat tempZs,
                                 GLfloat tempZe) {
    PlainNode newNode{};

    // add the value to the node
    newNode.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
    // reset the address of the first node
    nodes.push_back(newNode);

    return true;
}

/**
 * @brief  Returns the type of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return Slope type
 */
Slope PlainLinkedList::GetType(size_t ptrCount) {
    return nodes[ptrCount].GetType();
}

/**
 * @brief  Returns the X start coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return X start coordinate
 */
GLfloat PlainLinkedList::GetXstart(size_t ptrCount) {
    return nodes[ptrCount].GetXstart();
}

/**
 * @brief  Returns the X end coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return X end coordinate
 */
GLfloat PlainLinkedList::GetXend(size_t ptrCount) {
    return nodes[ptrCount].GetXend();
}

/**
 * @brief  Returns the Y start coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return Y start coordinate
 */
GLfloat PlainLinkedList::GetYstart(size_t ptrCount) {
    return nodes[ptrCount].GetYstart();
}

/**
 * @brief  Returns the Y end coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return Y end coordinate
 */
GLfloat PlainLinkedList::GetYend(size_t ptrCount) {
    return nodes[ptrCount].GetYend();
}

/**
 * @brief  Returns the Z start coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return Z start coordinate
 */
GLfloat PlainLinkedList::GetZstart(size_t ptrCount) {
    return nodes[ptrCount].GetZstart();
}

/**
 * @brief  Returns the Z end coordinate of a slope at in the vector at the given index
 * @param ptrCount Index of vector to read from
 * @return Z end coordinate
 */
GLfloat PlainLinkedList::GetZend(size_t ptrCount) {
    return nodes[ptrCount].GetZend();
}

/**
 * @brief  Modifies an existing slope within the plain vector
 *
 * @param ptrCount Index location within vector of slope to modify
 * @param tempType Slope type
 * @param tempXs X start location
 * @param tempXe X end location
 * @param tempYs Y start location
 * @param tempYe Y end location
 * @param tempZs Z start location
 * @param tempZe Z end location
 */
void PlainLinkedList::SetData(size_t ptrCount, Slope tempType, GLfloat tempXs,
                              GLfloat tempXe, GLfloat tempYs, GLfloat tempYe,
                              GLfloat tempZs, GLfloat tempZe) {
    PlainNode temp{};

    temp.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
    nodes[ptrCount] = temp;
}

/**
 * @brief  Returns the current number of slopes within the vector
 * @return The size of the vector
 */
size_t PlainLinkedList::GetListSize() {
    return nodes.size();
}
