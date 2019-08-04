//  PlainNode.cpp
//
//  Implementation file for PlainNode Class
//  Defines all the methods declared, but not defined, in PlainNode.h
//
//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#include "PlainNode.h"

//----------------------------------------------------------------

void PlainNode::Clear() {
    m_next = nullptr;
}

//----------------------------------------------------------------

void PlainNode::SetData(const int tempType, const GLfloat tempXs,
                        const GLfloat tempXe, const GLfloat tempYs,
                        const GLfloat tempYe, const GLfloat tempZs,
                        const GLfloat tempZe) {
    m_type        = tempType;
    m_xPlainStart = tempXs;
    m_xPlainEnd   = tempXe;
    m_yPlainStart = tempYs;
    m_yPlainEnd   = tempYe;
    m_zPlainStart = tempZs;
    m_zPlainEnd   = tempZe;
}

//----------------------------------------------------------------
