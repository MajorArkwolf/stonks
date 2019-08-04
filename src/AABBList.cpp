//  AABBList.cpp
//
//  Implementation file for AABBList Class
//  Defines all the methods declared, but not defined, in AABBList.h
//
//  Peter Crabbe, Augest 2019
//--------------------------------------------------------------------------------------

#include "AABBList.h"

//--------------------------------------------------------------------------------------

void AABBList::Clear() {
    delete nodes;
}

//--------------------------------------------------------------------------------------

bool AABBList::AddToStart(GLdouble maxX, GLdouble minX, GLdouble maxY,
                                GLdouble minY, GLdouble maxZ, GLdouble minZ) {
    ///Create a temp node
	AABBNode newNode;

    // add the value to the node
    newNode.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    // set the address of the net node
    newNode->SetNext(m_first->GetNext());
    // reset the address of the first node
    m_first->SetNext(newNode);

    return true;
}

//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMaxX(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMaxX();
    else
        return 0;
}
//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMinX(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMinX();
    else
        return 0;
}

//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMaxY(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMaxY();
    else
        return 0;
}

//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMinY(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMinY();
    else
        return 0;
}

//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMaxZ(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMaxZ();
    else
        return 0;
}

//--------------------------------------------------------------------------------------

GLdouble AABBList::GetMinZ(int ptrCount) {
    if (nodes[ptrCount])
        return nodes[ptrCount].GetMinZ();
    else
        return 0;
}

//--------------------------------------------------------------------------------------

void AABBList::SetData(const int &ptrCount, const GLdouble maxX,
                             const GLdouble minX, const GLdouble maxY,
                             const GLdouble minY, const GLdouble maxZ,
                             const GLdouble minZ) {
    AABBNode temp = new AABBNode{};
    temp.SetData(maxX, minX, maxY, minY, maxZ, minZ);
    nodes.push_back(temp);
}

//--------------------------------------------------------------------------------------

int AABBList::GetListSize() {
    return nodes.size;
}

//--------------------------------------------------------------------------------------
