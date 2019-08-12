//  AABBList.cpp
//
//  Implementation file for AABBList Class
//  Defines all the methods declared, but not defined, in AABBList.h
//
//  Peter Crabbe, Augest 2019
//--------------------------------------------------------------------------------------

#include "AABBList.h"

bool AABBList::AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY,
                          GLfloat minY, GLfloat maxZ, GLfloat minZ) {
    /// Creates a temp node.
    AABBNode newNode{};

    // adds the values to the node
    newNode.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    // Places the node at the end of the vector.
    nodes.push_back(newNode);

    return true;
}

GLfloat AABBList::GetMaxX(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxX();
    else
        return 0;
}

GLfloat AABBList::GetMinX(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinX();
    else
        return 0;
}

GLfloat AABBList::GetMaxY(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxY();
    else
        return 0;
}

GLfloat AABBList::GetMinY(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinY();
    else
        return 0;
}

GLfloat AABBList::GetMaxZ(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMaxZ();
    else
        return 0;
}

GLfloat AABBList::GetMinZ(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetMinZ();
    else
        return 0;
}

void AABBList::SetData(const int &ptrCount, const GLfloat maxX,
                       const GLfloat minX, const GLfloat maxY, const GLfloat minY,
                       const GLfloat maxZ, const GLfloat minZ) {
    AABBNode temp{};
    temp.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    nodes.push_back(temp);
}

int AABBList::GetListSize() {
    int size = int(nodes.size());
    return size;
}
