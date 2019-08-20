#include "PlainLinkedList.h"

#include <cstddef>

#include "PlainNode.h"

using Shay::PlainLinkedList;
using Shay::PlainNode;

using Slope = PlainNode::Slope;
using std::size_t;

bool PlainLinkedList::AddToStart(Slope tempType, GLfloat tempXs, GLfloat tempXe,
                                 GLfloat tempYs, GLfloat tempYe, GLfloat tempZs,
                                 GLfloat tempZe) {
    PlainNode newNode{};

    // add the value to the node
    newNode.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
    // reset the address of the first node
    nodes.push_back(newNode);

    return true;
}

Slope PlainLinkedList::GetType(size_t ptrCount) {
    return nodes[ptrCount].GetType();
}

GLfloat PlainLinkedList::GetXstart(size_t ptrCount) {
    return nodes[ptrCount].GetXstart();
}

GLfloat PlainLinkedList::GetXend(size_t ptrCount) {
    return nodes[ptrCount].GetXend();
}

GLfloat PlainLinkedList::GetYstart(size_t ptrCount) {
    return nodes[ptrCount].GetYstart();
}

GLfloat PlainLinkedList::GetYend(size_t ptrCount) {
    return nodes[ptrCount].GetYend();
}

GLfloat PlainLinkedList::GetZstart(size_t ptrCount) {
    return nodes[ptrCount].GetZstart();
}

GLfloat PlainLinkedList::GetZend(size_t ptrCount) {
    return nodes[ptrCount].GetZend();
}

void PlainLinkedList::SetData(size_t ptrCount, Slope tempType, GLfloat tempXs,
                              GLfloat tempXe, GLfloat tempYs, GLfloat tempYe,
                              GLfloat tempZs, GLfloat tempZe) {
    PlainNode temp{};

    temp.SetData(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
    nodes[ptrCount] = temp;
}

size_t PlainLinkedList::GetListSize() {
    return nodes.size();
}
