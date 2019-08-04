//  AABBNode.cpp
//
//  Implementation file for AABBNode Class
//  Defines all the methods declared, but not defined, in AABBNode.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "AABBNode.h"

//----------------------------------------------------------------


//----------------------------------------------------------------

void AABBNode::SetData(const GLfloat maxX, const GLfloat minX,
                       const GLfloat maxY, const GLfloat minY,
                       const GLfloat maxZ, const GLfloat minZ) {
    m_BBox.max.x = maxX;
    m_BBox.min.x = minX;
    m_BBox.max.y = maxY;
    m_BBox.min.y = minY;
    m_BBox.max.z = maxZ;
    m_BBox.min.z = minZ;
}

//----------------------------------------------------------------
