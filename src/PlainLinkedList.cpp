//  PlainLinkedList.cpp
//
//  Implementation file for PlainLinkedList Class
//  Defines all the methods declared, but not defined, in PlainLinkedList.h
//
//  Shay Leary, April 2005
//  Modified by Peter Crabbe, 04/08/2019
//--------------------------------------------------------------------------------------

#include "PlainLinkedList.h"

void PlainLinkedList::Clear() {}

bool PlainLinkedList::AddToStart(const int tempType, const GLfloat tempXs,
                                 const GLfloat tempXe, const GLfloat tempYs,
                                 const GLfloat tempYe, const GLfloat tempZs,
                                 const GLfloat tempZe) {
    PlainNode newNode{};

    // add the value to the node
    newNode.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
    // reset the address of the first node
    nodes.push_back(newNode);

    return true;
}

GLfloat PlainLinkedList::GetType(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetType();
    else
        return 0;
}

GLfloat PlainLinkedList::GetXstart(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetXstart();
    else
        return 0;
}

GLfloat PlainLinkedList::GetXend(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetXend();
    else
        return 0;
}

GLfloat PlainLinkedList::GetYstart(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetYstart();
    else
        return 0;
}

GLfloat PlainLinkedList::GetYend(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetYend();
    else
        return 0;
}

GLfloat PlainLinkedList::GetZstart(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetZstart();
    else
        return 0;
}

GLfloat PlainLinkedList::GetZend(int ptrCount) {
    if (ptrCount <= nodes.size())
        return nodes[ptrCount].GetZend();
    else
        return 0;
}

void PlainLinkedList::SetData(const int &ptrCount, const int tempType,
                              const GLfloat tempXs, const GLfloat tempXe,
                              const GLfloat tempYs, const GLfloat tempYe,
                              const GLfloat tempZs, const GLfloat tempZe) {
    PlainNode temp{};

    temp.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs,
                            tempZe);
    nodes[ptrCount] = temp;
}

int PlainLinkedList::GetListSize() {
    return int(nodes.size());
}
