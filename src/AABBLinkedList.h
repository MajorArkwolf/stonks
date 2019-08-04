//  AABBLinkedList.h
//  Header file for the AABBLinkedList class
//  Linked List used to store nodes (AABBNode) which contain the co-ordinates of the
//  boundings boxes which are used for the collsion detection.
//
//	The program splits the world into four quadrants and creates a linked list to
//  store the bounding box details for each
//
//  Author:  Shay Leary
//  March 2005
//--------------------------------------------------------------------------------------

#ifndef AABBLINKED_LIST_H
#    define AABBLINKED_LIST_H

//--------------------------------------------------------------------------------------

#    include "AABBNode.h"
#    include "Glut.hpp"

//--------------------------------------------------------------------------------------

class AABBLinkedList {
  public:
    // constructor creates pointer to first node
    AABBLinkedList() {
        m_first = new AABBNode;
    }

    ~AABBLinkedList() {
        Clear();
    }

    //----------------------------------------------------------------------------------

    // clears linked list and frees memory
    void Clear();

    // add a node to the start of the linked list
    bool AddToStart(GLfloat maxX, GLfloat minX, GLfloat maxY, GLfloat minY,
                    GLfloat maxZ, GLfloat minZ);

    //  set the values of the node data
    void SetData(const int &ptrCount, const GLfloat maxX, const GLfloat minX,
                 const GLfloat maxY, const GLfloat minY, const GLfloat maxZ,
                 const GLfloat minZ);

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLfloat GetMaxX(int ptrCount);
    GLfloat GetMinX(int ptrCount);
    GLfloat GetMaxY(int ptrCount);
    GLfloat GetMinY(int ptrCount);
    GLfloat GetMaxZ(int ptrCount);
    GLfloat GetMinZ(int ptrCount);

    // Return size of list
    int GetListSize();

    // Return the address of the link to the next node in the list
    AABBNode *GetNext() const {
        return m_first->GetNext();
    }
    // Return the address of the link to the first node in the list
    AABBNode *GetFirst() const {
        return m_first;
    }

    //--------------------------------------------------------------------------------------

  private:
    // pointer to first node in list
    AABBNode *m_first;

    // used to clear memory
    void Delete(AABBNode *before);

    // Privatised copy constructor and assignment operator
    AABBLinkedList(const AABBLinkedList &ll) = delete;
    AABBLinkedList &operator=(const AABBLinkedList &ll) = delete;
};

#endif

//--------------------------------------------------------------------------------------
