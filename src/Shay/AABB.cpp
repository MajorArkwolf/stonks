#include "AABB.h"

using Shay::AABB;

void AABB::SetNoBoundingBoxes(size_t size) {
    m_BBox.clear();
    m_BBox.resize(size);
}

void AABB::SetMaxX(size_t index, GLfloat tempX) {
    m_BBox[index].max.x = tempX;
}
void AABB::SetMinX(size_t index, GLfloat tempX) {
    m_BBox[index].min.x = tempX;
}
void AABB::SetMaxY(size_t index, GLfloat tempY) {
    m_BBox[index].max.y = tempY;
}
void AABB::SetMinY(size_t index, GLfloat tempY) {
    m_BBox[index].min.y = tempY;
}
void AABB::SetMaxZ(size_t index, GLfloat tempZ) {
    m_BBox[index].max.z = tempZ;
}
void AABB::SetMinZ(size_t index, GLfloat tempZ) {
    m_BBox[index].min.z = tempZ;
}

GLfloat AABB::GetMaxX(size_t index) {
    return m_BBox[index].max.x;
}
GLfloat AABB::GetMinX(size_t index) {
    return m_BBox[index].min.x;
}
GLfloat AABB::GetMaxY(size_t index) {
    return m_BBox[index].max.y;
}
GLfloat AABB::GetMinY(size_t index) {
    return m_BBox[index].min.y;
}
GLfloat AABB::GetMaxZ(size_t index) {
    return m_BBox[index].max.z;
}
GLfloat AABB::GetMinZ(size_t index) {
    return m_BBox[index].min.z;
}
size_t AABB::GetNoBoundingBoxes() {
    return m_BBox.size();
}
