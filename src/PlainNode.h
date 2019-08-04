//  PlainNode.h
//  Header file for the PlainNode class
//  Stores details for each plain.  Each node is stored in each link of the Plain Linked List

//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#ifndef PLAINNODE_H
#    define PLAINNODE_H

//--------------------------------------------------------------------------------------

#    include <cmath>
#    include <iostream>

#    include "Glut.hpp"

class PlainNode {

  public:
    PlainNode() {
        Clear();
    }
    ~PlainNode() {
        Clear();
    }

    //----------------------------------------------------------------------------------

    void Clear();

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLfloat GetType() {
        return m_type;
    }
    GLfloat GetXstart() {
        return m_xPlainStart;
    }
    GLfloat GetXend() {
        return m_xPlainEnd;
    }
    GLfloat GetYstart() {
        return m_yPlainStart;
    }
    GLfloat GetYend() {
        return m_yPlainEnd;
    }
    GLfloat GetZstart() {
        return m_zPlainStart;
    }
    GLfloat GetZend() {
        return m_zPlainEnd;
    }

    // Return the address of the link to the next node in the list
    PlainNode *GetNext() const {
        return m_next;
    }

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    void SetData(const int tempType, const GLfloat tempXs, const GLfloat tempXe,
                 const GLfloat tempYs, const GLfloat tempYe,
                 const GLfloat tempZs, const GLfloat tempZe);

    // Set the address of the link to the next node in the list
    void SetNext(PlainNode *next) {
        m_next = next;
    }

  private:
    // The address of the next node in the list
    PlainNode *m_next = nullptr;

    // Stores type of plain:
    // (0: flat plane)
    // (1: incline from z to y)
    // (2: incline from x to y)
    GLfloat m_type = 0;

    // stores start and end co-ordinates of plane on x, y and z axis
    GLfloat m_xPlainStart = 0, m_xPlainEnd = 0;
    GLfloat m_yPlainStart = 0, m_yPlainEnd = 0;
    GLfloat m_zPlainStart = 0, m_zPlainEnd = 0;

    //----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    PlainNode(const PlainNode &newNode) = delete;
    PlainNode &operator=(const PlainNode &newNode) = delete;
};

#endif

//--------------------------------------------------------------------------------------
