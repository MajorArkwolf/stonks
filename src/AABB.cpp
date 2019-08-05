//  AABB.cpp
//
//  Implementation file for AABB Class
//  Defines all the methods declared, but not defined, in AABB.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "AABB.h"

void AABB::SetNoBoundingBoxes(const int &size) {
    m_BBox.clear();
    m_BBox.resize(size);
}

void AABB::SetMaxX(const int &tempIndex, const GLfloat &tempX) {
    m_BBox[tempIndex].max.x = tempX;
}
void AABB::SetMinX(const int &tempIndex, const GLfloat &tempX) {
    m_BBox[tempIndex].min.x = tempX;
}
void AABB::SetMaxY(const int &tempIndex, const GLfloat &tempY) {
    m_BBox[tempIndex].max.y = tempY;
}
void AABB::SetMinY(const int &tempIndex, const GLfloat &tempY) {
    m_BBox[tempIndex].min.y = tempY;
}
void AABB::SetMaxZ(const int &tempIndex, const GLfloat &tempZ) {
    m_BBox[tempIndex].max.z = tempZ;
}
void AABB::SetMinZ(const int &tempIndex, const GLfloat &tempZ) {
    m_BBox[tempIndex].min.z = tempZ;
}


GLfloat AABB::GetMaxX(const int &tempIndex) {
    return m_BBox[tempIndex].max.x;
}
GLfloat AABB::GetMinX(const int &tempIndex) {
    return m_BBox[tempIndex].min.x;
}
GLfloat AABB::GetMaxY(const int &tempIndex) {
    return m_BBox[tempIndex].max.y;
}
GLfloat AABB::GetMinY(const int &tempIndex) {
    return m_BBox[tempIndex].min.y;
}
GLfloat AABB::GetMaxZ(const int &tempIndex) {
    return m_BBox[tempIndex].max.z;
}
GLfloat AABB::GetMinZ(const int &tempIndex) {
    return m_BBox[tempIndex].min.z;
}
int AABB::GetNoBoundingBoxes() {
    return m_BBox.size();
}
