#include "AABB.h"

using Shay::AABB;

void AABB::SetMaxX(GLfloat tempX) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.x = tempX;
}
void AABB::SetMinX(GLfloat tempX) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.x = tempX;
}
void AABB::SetMaxY(GLfloat tempY) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.y = tempY;
}
void AABB::SetMinY(GLfloat tempY) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.y = tempY;
}
void AABB::SetMaxZ(GLfloat tempZ) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].max.z = tempZ;
}
void AABB::SetMinZ(GLfloat tempZ) {
    if (this->currentAABB >= m_BBox.size()) {
        m_BBox.push_back({});
    }
    m_BBox[this->currentAABB].min.z = tempZ;
}
auto AABB::SetAABBIndex(size_t index) -> void  {
    this->currentAABB = index;
}
auto AABB::FinishAABB() -> void {
    this->currentAABB++;
}
GLfloat AABB::GetMaxX() {
    return m_BBox[this->currentAABB].max.x;
}
GLfloat AABB::GetMinX() {
    return m_BBox[this->currentAABB].min.x;
}
GLfloat AABB::GetMaxY() {
    return m_BBox[this->currentAABB].max.y;
}
GLfloat AABB::GetMinY() {
    return m_BBox[this->currentAABB].min.y;
}
GLfloat AABB::GetMaxZ() {
    return m_BBox[this->currentAABB].max.z;
}
GLfloat AABB::GetMinZ() {
    return m_BBox[this->currentAABB].min.z;
}
size_t AABB::GetNoBoundingBoxes() {
    return m_BBox.size();
}
