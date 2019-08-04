//  AABBLinkedList.cpp
//
//  Implementation file for AABBLinkedList Class
//  Defines all the methods declared, but not defined, in AABBLinkedList.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "AABBLinkedList.h"

//--------------------------------------------------------------------------------------

void AABBLinkedList::Clear() {
    AABBNode *ptr = m_first;

    while (ptr->GetNext() != NULL)

        // clear memory
        Delete(ptr);
}

//--------------------------------------------------------------------------------------

void AABBLinkedList::Delete(AABBNode *before) {
    AABBNode *temp = before->GetNext();

    before->SetNext(temp->GetNext());

    delete temp;
}

//--------------------------------------------------------------------------------------

bool AABBLinkedList::AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY,
                                GLfloat minY, GLfloat maxZ, GLfloat minZ) {
    AABBNode *newNode;
    try {
        newNode = new AABBNode;
    } catch (...) {
        return false;
    }

    // add the value to the node
    newNode->SetData(maxX, minX, maxY, minY, maxZ, minZ);
    // set the address of the net node
    newNode->SetNext(m_first->GetNext());
    // reset the address of the first node
    m_first->SetNext(newNode);

    return true;
}

//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMaxX(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMaxX();
    else
        return NULL;
}
//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMinX(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMinX();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMaxY(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMaxY();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMinY(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMinY();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMaxZ(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMaxZ();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------

GLfloat AABBLinkedList::GetMinZ(int ptrCount) {
    AABBNode *ptr = (m_first);
    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }

    if (ptr->GetNext() != NULL)
        return ptr->GetNext()->GetMinZ();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------

void AABBLinkedList::SetData(const int &ptrCount, const GLfloat maxX,
                             const GLfloat minX, const GLfloat maxY,
                             const GLfloat minY, const GLfloat maxZ,
                             const GLfloat minZ) {
    AABBNode *ptr = (m_first);

    for (int count = 0; count < ptrCount; count++) {
        ptr = ptr->GetNext();
    }
    ptr->GetNext()->SetData(maxX, minX, maxY, minY, maxZ, minZ);
}

//--------------------------------------------------------------------------------------

int AABBLinkedList::GetListSize() {
    int tmpSize = 0;
    // count size of list
    for (AABBNode *ptr = (m_first); ptr->GetNext() != NULL; ptr = ptr->GetNext()) {
        tmpSize++;
    }
    return tmpSize;
}

//--------------------------------------------------------------------------------------
