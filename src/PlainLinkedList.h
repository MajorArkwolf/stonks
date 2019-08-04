/**
 * @class PlainLinkedList
 * @brief  PlainLinkedList collision list array
 *
 * Updated Shay's Linklist format to a vector improving access speeds.
 *
 * @author Peter Crabbe
 * @version 02
 * @date 04/08/2019
 *
 */

#ifndef PLAINLINKED_LIST_H
#define PLAINLINKED_LIST_H
#include <vector>

#include "PlainNode.h"

class PlainLinkedList {
  public:
    /**
     * @brief Default constructor, not required
     */
    PlainLinkedList() = default;

    /**
     * @brief Copy Constructor, not required
     */
    PlainLinkedList(const PlainLinkedList &array) = default;

    /**
     * @brief Copy assignment
     */
    PlainLinkedList &operator=(const PlainLinkedList &array) = default;

    /// No longer used, to be removed when safe to do so.
    void Clear();

    /**
     * @brief  Attempts to add to the vector, then will push into the last spot
     *
     * @param  const int tempType
     * @param  const GLfloat tempXs
     * @param  const GLfloat tempXe
     * @param  const GLfloat tempYs
     * @param  const GLfloat tempYe
     * @param  const GLfloat tempZs
     * @param  const GLfloat tempZe
     * @return bool
     */
    bool AddToStart(const int tempType, const GLfloat tempXs, const GLfloat tempXe,
                    const GLfloat tempYs, const GLfloat tempYe,
                    const GLfloat tempZs, const GLfloat tempZe);

    /**
     * @brief  Sets a given value at a set point
     *
     * @param  const int &ptrCount
     * @param  const int tempType
     * @param  const GLfloat tempXs
     * @param  const GLfloat tempXe
     * @param  const GLfloat tempYs
     * @param  const GLfloat tempYe
     * @param  const GLfloat tempZs
     * @param  const GLfloat tempZe
     */
    void SetData(const int &ptrCount, const int tempType, const GLfloat tempXs,
                 const GLfloat tempXe, const GLfloat tempYs, const GLfloat tempYe,
                 const GLfloat tempZs, const GLfloat tempZe);

    /**
     * @brief Gets the Type value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetType(int ptrCount);

    /**
     * @brief Gets the X start value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetXstart(int ptrCount);

    /**
     * @brief Gets the X end value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetXend(int ptrCount);

    /**
     * @brief Gets the Y start value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetYstart(int ptrCount);

    /**
     * @brief Gets the Y end value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetYend(int ptrCount);

    /**
     * @brief Gets the Z start value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetZstart(int ptrCount);

    /**
     * @brief Gets the Z end value at the given point in the array
     * @param int ptrCount
     * @return GLfloat
     */
    GLfloat GetZend(int ptrCount);

    /**
     * @brief Returns the size of the vector as an int.
     * @return GLfloat
     */
    int GetListSize();

  private:
    /// Vector used to store nodes.
    std::vector<PlainNode> nodes{};

    /// Depreciated code, to be removed when safe to do so.
    void Delete(PlainNode *before){};
};
#endif
