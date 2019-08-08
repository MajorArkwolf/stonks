/**
 * @class PlainNode
 * @brief  Stores data relating to collision information
 *
 * Used inside of the PlainLinkedList
 *
 * @author Peter Crabbe
 * @version 02
 * @date 04/08/2019
 *
 */

#ifndef PLAINNODE_H
#define PLAINNODE_H

#include <cmath>
#include <iostream>

#include "Gl.hpp"

class PlainNode {

  public:
    /**
     * @brief Default constructor, not required
     */
    PlainNode() {
        Clear();
    }

    /**
     * @brief Default Destructor, not required
     */
    ~PlainNode() {
        Clear();
    }

    /**
     * @brief Copy Constructor, defaulted
     */
    PlainNode(const PlainNode &newNode) = default;

    /**
     * @brief Copy assignment, defaulted
     */
    PlainNode &operator=(const PlainNode &newNode) = default;

    // Depreciated, to be deleted when safe to do so.
    void Clear();

    /*
     * @brief Gets the Type value from the node
     */
    GLfloat GetType();

    /*
     * @brief Gets the X start value from the node
     */
    GLfloat GetXstart();

    /*
     * @brief Gets the X end value from the node
     */
    GLfloat GetXend();

    /*
     * @brief Gets the Y start value from the node
     */
    GLfloat GetYstart();

    /*
     * @brief Gets the Y end value from the node
     */
    GLfloat GetYend();

    /*
     * @brief Gets the Z start value from the node
     */
    GLfloat GetZstart();

    /*
     * @brief Gets the Z end value from the node
     */
    GLfloat GetZend();

    /**
     * @brief  Sets the data at the given point in the array.
     */
    void SetData(const int tempType, const GLfloat tempXs, const GLfloat tempXe,
                 const GLfloat tempYs, const GLfloat tempYe,
                 const GLfloat tempZs, const GLfloat tempZe);

    /**
     * @brief  Deprecated code, to be deleted.
     */
    void SetNext(PlainNode *next) {
        // m_next = next;
    }

  private:
    /// Stores type of plain:
    /// (0: flat plane)
    /// (1: incline from z to y)
    /// (2: incline from x to y)
    GLfloat m_type = 0;

    /// stores start and end co-ordinates of plane on x, y and z axis
    GLfloat m_xPlainStart = 0, m_xPlainEnd = 0;
    GLfloat m_yPlainStart = 0, m_yPlainEnd = 0;
    GLfloat m_zPlainStart = 0, m_zPlainEnd = 0;
};

#endif
