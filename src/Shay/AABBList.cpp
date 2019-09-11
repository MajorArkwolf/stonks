#include "AABBList.hpp"

#include <cstddef>

using Shay::AABBList;
using std::size_t;


bool AABBList::AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY,
                          GLfloat minY, GLfloat maxZ, GLfloat minZ) {
    // Creates a temp node.
    AABBNode newNode{};

    // adds the values to the node
    newNode.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    // Places the node at the end of the vector.
    nodes.push_back(newNode);

    return true;
}

GLfloat AABBList::GetMaxX(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxX();
    else
        return 0;
}

GLfloat AABBList::GetMinX(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinX();
    else
        return 0;
}

GLfloat AABBList::GetMaxY(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxY();
    else
        return 0;
}

GLfloat AABBList::GetMinY(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinY();
    else
        return 0;
}

GLfloat AABBList::GetMaxZ(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxZ();
    else
        return 0;
}

GLfloat AABBList::GetMinZ(size_t ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinZ();
    else
        return 0;
}

void AABBList::SetData(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                       GLfloat maxZ, GLfloat minZ) {
    AABBNode temp{};
    temp.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    nodes.push_back(temp);
}

size_t AABBList::GetListSize() {
    size_t size = size_t(nodes.size());
    return size;
}

void AABBList::Delete() {
    nodes.clear();
}

void AABBList::Clear() {
    nodes.clear();
}
