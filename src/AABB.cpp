//  AABB.cpp
//
//  Implementation file for AABB Class
//  Defines all the methods declared, but not defined, in AABB.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "AABB.h"

#include <iostream>

//--------------------------------------------------------------------------------------

void AABB::SetNoBoundingBoxes(const int &tempSize) {
    m_BBox      = new BoundingBox[static_cast<size_t>(tempSize)];
    m_NoOfBoxes = tempSize;
}

//--------------------------------------------------------------------------------------

void AABB::ClearBB(BoundingBox *&tempArray) {
    tempArray = NULL;
    if (tempArray == NULL) {
        delete[] tempArray;
    }
}

//--------------------------------------------------------------------------------------
