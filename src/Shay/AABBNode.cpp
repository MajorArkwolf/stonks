//  AABBNode.cpp
//
//  Implementation file for AABBNode Class
//  Defines all the methods declared, but not defined, in AABBNode.h
//
//  Shay Leary, March 2005
//	Fixed by Peter Crabbe, 04/08/2019
//--------------------------------------------------------------------------------------

#include "AABBNode.h"

void AABBNode::SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                       const GLfloat minY, const GLfloat maxZ, const GLfloat minZ) {
    m_BBox.max.x = maxX;
    m_BBox.min.x = minX;
    m_BBox.max.y = maxY;
    m_BBox.min.y = minY;
    m_BBox.max.z = maxZ;
    m_BBox.min.z = minZ;
}

GLfloat AABBNode::GetMaxX() {
    return m_BBox.max.x;
}

GLfloat AABBNode::GetMinX() {
    return m_BBox.min.x;
}
GLfloat AABBNode::GetMaxY() {
    return m_BBox.max.y;
}
GLfloat AABBNode::GetMinY() {
    return m_BBox.min.y;
}
GLfloat AABBNode::GetMaxZ() {
    return m_BBox.max.z;
}
GLfloat AABBNode::GetMinZ() {
    return m_BBox.min.z;
}
