//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world.
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#include "CameraMap.h"
#include "Collision.h"
#include "PlainLinkedList.h"

//--------------------------------------------------------------------------------------

class Camera {
  public:
    Camera();

    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    // sets initial value for bounding boxes (in the array AABB)
    void SetAABBMaxX(const int &tempIndex, const GLfloat &tempX) {
        m_colDetect.SetAABBMaxX(tempIndex, tempX);
    }
    void SetAABBMinX(const int &tempIndex, const GLfloat &tempX) {
        m_colDetect.SetAABBMinX(tempIndex, tempX);
    }
    void SetAABBMaxY(const int &tempIndex, const GLfloat &tempY) {
        m_colDetect.SetAABBMaxY(tempIndex, tempY);
    }
    void SetAABBMinY(const int &tempIndex, const GLfloat &tempY) {
        m_colDetect.SetAABBMinY(tempIndex, tempY);
    }
    void SetAABBMaxZ(const int &tempIndex, const GLfloat &tempZ) {
        m_colDetect.SetAABBMaxZ(tempIndex, tempZ);
    }
    void SetAABBMinZ(const int &tempIndex, const GLfloat &tempZ) {
        m_colDetect.SetAABBMinZ(tempIndex, tempZ);
    }

    // set step and rotation size
    void SetRotateSpeed(const GLfloat &tempSpeed) {
        m_rotateSpeed = tempSpeed;
    }
    void SetMoveSpeed(const GLfloat &tempSpeed) {
        m_moveSpeed = tempSpeed;
    }

    // COLLSION DETECTION FUNCTIONS
    // set collision detection (TRUE = on)
    void SetCollisionDetectionOn(const bool &tempCol) {
        m_CollisionDetectionOn = tempCol;
    }
    // set number of bounding boxes
    void SetNoBoundingBoxes(const int &tempSize) {
        m_colDetect.SetNoBoundingBoxes(tempSize);
    }
    // set the co-ordinates of the world
    void SetWorldCoordinates(const GLfloat &tempX, const GLfloat &tempZ);
    // creates a linked list for each quadrant of the world and places the
    // bounding box data in each.  Then clears and deletes AABB array.
    void InitiateBoundingBoxes() {
        m_colDetect.CreateLinkedList();
    }

    // sets the co-ordinate of each plain
    void SetPlains(const int tempType, const GLfloat tempXs, const GLfloat tempXe,
                   const GLfloat tempYs, const GLfloat tempYe,
                   const GLfloat tempZs, const GLfloat tempZe);

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLfloat GetLR() {
        return m_x;
    }
    GLfloat GetUD() {
        return m_y;
    }
    GLfloat GetFB() {
        return m_z;
    }
    GLfloat GetAABBMaxX(const int &tempIndex) {
        return m_colDetect.GetAABBMaxX(tempIndex);
    }
    GLfloat GetAABBMinX(const int &tempIndex) {
        return m_colDetect.GetAABBMinX(tempIndex);
    }
    GLfloat GetAABBMaxY(const int &tempIndex) {
        return m_colDetect.GetAABBMaxY(tempIndex);
    }
    GLfloat GetAABBMinY(const int &tempIndex) {
        return m_colDetect.GetAABBMinY(tempIndex);
    }
    GLfloat GetAABBMaxZ(const int &tempIndex) {
        return m_colDetect.GetAABBMaxZ(tempIndex);
    }
    GLfloat GetAABBMinZ(const int &tempIndex) {
        return m_colDetect.GetAABBMinZ(tempIndex);
    }

    // position the camera
    void Position(GLfloat const &tempX, GLfloat const &tempY,
                  GLfloat const &tempZ, GLfloat const &tempAngle);

    // check whether ok to move
    void CheckCamera();

    // Used to pass direction to move or rotate  (i.e. 1, -1 or 0)
    void DirectionFB(GLfloat tempMove);
    void DirectionLR(GLfloat tempMove);
    void DirectionUD(GLfloat tempMove);
    void DirectionRotateLR(GLfloat tempMove);
    void DirectionLookUD(GLfloat tempMove);

    // display map
    void DisplayMap(const int &screenWidth, const int &screenHeight,
                    const GLuint &tempImage);
    // display welcome screen
    void DisplayWelcomeScreen(const int &screenWidth, const int &screenHeight,
                              const int &tempExit, const GLuint &tempImage);
    // display no exit
    void DisplayNoExit(const int &screenWidth, const int &screenHeight,
                       const GLuint &tempImage);

  private:
    // steep incline increments
    GLfloat m_incrementX  = 0.0;
    GLfloat m_incrementZ  = 0.0;
    int m_No_Plains       = 0;
    int m_plainNo         = 0;
    GLfloat m_plainHeight = 0.0;

    // rotation variables
    GLfloat m_rotateAngleLR = 0.0;
    GLfloat m_deltaAngleLR  = 0.0;
    GLfloat m_rotateAngleUD = 0.0;
    GLfloat m_deltaAngleUD  = 0.0;

    // movement variables
    GLfloat m_x = 0.0, m_y = 0.0, m_z = 0.0, m_zLast = 0.0, m_xLast = 0.0;
    GLfloat m_lookX = 0.0, m_lookY = 0.0, m_lookZ = 0.0;
    GLfloat m_lookXX = 0.0, m_lookYY = 0.0, m_lookZZ = 0.0;
    GLfloat m_deltaMoveLR = 0.0;
    GLfloat m_deltaMoveFB = 0.0;
    GLfloat m_deltaMoveUD = 0.0;
    GLfloat m_direction   = 0.0;

    // movement speed (step size)
    GLfloat m_rotateSpeed = 0.0;
    GLfloat m_moveSpeed   = 0.0;

    // is it ok to move
    bool MoveFBOK();
    bool MoveLROK();
    bool MoveUDOK();
    bool RotateLROK();
    bool LookUDOK();

    // move around the world
    void MoveFB();
    void MoveLR();
    void MoveUD();
    void RotateLR();
    void LookUD();

    // overloaded function for setting plain
    void SetPlains(const int &moveX, const int &moveZ);

    // resets camera
    void ResetXYZ();
    // display new view
    void callGLLookAt();

    bool m_CollisionDetectionOn = true;

    // objects
    Collision m_colDetect{};
    CameraMap m_map{};
    PlainLinkedList m_Plain{};

    // These functions were set up to climb stairs, but are not used.
    // The Plain object is used instead
    void ClimbSteps(GLfloat stepStart, GLfloat stepFinish, GLfloat stepHeight,
                    GLfloat stepWidth, int noSteps);
    void CheckSteps();

    //----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Camera(const Camera &cam) = delete;
    Camera &operator=(const Camera &cam) = delete;
};

#endif
