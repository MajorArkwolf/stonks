//  AABBLinkedList.h
//  Header file for the AABBLink class
//
//  Instead of using a link list, lets spice things up with a vector
//	The program splits the world into four quadrants and creates a linked list to
//  store the bounding box details for each
//
//  Author:  Peter
//  Augest 2019
//--------------------------------------------------------------------------------------

#ifndef AABBLIST_H
#    define AABBLIST_H

//--------------------------------------------------------------------------------------

#    include <vector>

#    include "AABBNode.h"
#    include "Glut.hpp"

//--------------------------------------------------------------------------------------

class AABBList {
  public:
    // constructor creates pointer to first node
    AABBList() = default;

    ~AABBList() = default;

    //----------------------------------------------------------------------------------
	
    // add a node to the start of the linked list
    bool AddToStart(GLdouble maxX, GLdouble minX, GLdouble maxY, GLdouble minY,
                    GLdouble maxZ, GLdouble minZ);

    //  set the values of the node data
    void SetData(const int &ptrCount, const GLdouble maxX, const GLdouble minX,
                 const GLdouble maxY, const GLdouble minY, const GLdouble maxZ,
                 const GLdouble minZ);

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLdouble GetMaxX(int ptrCount);
    GLdouble GetMinX(int ptrCount);
    GLdouble GetMaxY(int ptrCount);
    GLdouble GetMinY(int ptrCount);
    GLdouble GetMaxZ(int ptrCount);
    GLdouble GetMinZ(int ptrCount);

    // Return size of list
    int GetListSize();

    //--------------------------------------------------------------------------------------

  private:
	//Vector storing the nodes
    std::vector<AABBNode> nodes{};

    // used to clear memory
    void Delete(){}
    void Clear() {}

    // Privatised copy constructor and assignment operator
    AABBList(const AABBList &ll) = delete;
    AABBList &operator=(const AABBList &ll) = delete;
};

#endif

//--------------------------------------------------------------------------------------
