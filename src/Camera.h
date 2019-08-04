//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world.
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------
#ifndef CAMERA_H
#define CAMERA_H

#define PI 3.1415962654

#include "CameraMap.h"
#include "Collision.h"
#include "PlainLinkedList.h"

//--------------------------------------------------------------------------------------

class Camera {
  public:
    Camera();
    virtual ~Camera() {}

    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------
    //  Set Methods
    //----------------------------------------------------------------------------------
    // sets initial value for bounding boxes (in the array AABB)
    void SetAABBMaxX(const int &tempIndex, const GLdouble &tempX) {
        m_colDetect.SetAABBMaxX(tempIndex, tempX);
    }
    void SetAABBMinX(const int &tempIndex, const GLdouble &tempX) {
        m_colDetect.SetAABBMinX(tempIndex, tempX);
    }
    void SetAABBMaxY(const int &tempIndex, const GLdouble &tempY) {
        m_colDetect.SetAABBMaxY(tempIndex, tempY);
    }
    void SetAABBMinY(const int &tempIndex, const GLdouble &tempY) {
        m_colDetect.SetAABBMinY(tempIndex, tempY);
    }
    void SetAABBMaxZ(const int &tempIndex, const GLdouble &tempZ) {
        m_colDetect.SetAABBMaxZ(tempIndex, tempZ);
    }
    void SetAABBMinZ(const int &tempIndex, const GLdouble &tempZ) {
        m_colDetect.SetAABBMinZ(tempIndex, tempZ);
    }

    // set step and rotation size
    void SetRotateSpeed(const GLdouble &tempSpeed) {
        m_rotateSpeed = tempSpeed;
    }
    void SetMoveSpeed(const GLdouble &tempSpeed) {
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
    void SetWorldCoordinates(const GLdouble &tempX, const GLdouble &tempZ);
    // creates a linked list for each quadrant of the world and places the
    // bounding box data in each.  Then clears and deletes AABB array.
    void InitiateBoundingBoxes() {
        m_colDetect.CreateLinkedList();
    }

    // sets the co-ordinate of each plain
    void SetPlains(const int tempType, const GLdouble tempXs, const GLdouble tempXe,
                   const GLdouble tempYs, const GLdouble tempYe,
                   const GLdouble tempZs, const GLdouble tempZe);

    //----------------------------------------------------------------------------------
    //  Get Methods
    //----------------------------------------------------------------------------------
    GLdouble GetLR() {
        return m_x;
    }
    GLdouble GetUD() {
        return m_y;
    }
    GLdouble GetFB() {
        return m_z;
    }
    GLdouble GetAABBMaxX(const int &tempIndex) {
        return m_colDetect.GetAABBMaxX(tempIndex);
    }
    GLdouble GetAABBMinX(const int &tempIndex) {
        return m_colDetect.GetAABBMinX(tempIndex);
    }
    GLdouble GetAABBMaxY(const int &tempIndex) {
        return m_colDetect.GetAABBMaxY(tempIndex);
    }
    GLdouble GetAABBMinY(const int &tempIndex) {
        return m_colDetect.GetAABBMinY(tempIndex);
    }
    GLdouble GetAABBMaxZ(const int &tempIndex) {
        return m_colDetect.GetAABBMaxZ(tempIndex);
    }
    GLdouble GetAABBMinZ(const int &tempIndex) {
        return m_colDetect.GetAABBMinZ(tempIndex);
    }

    // position the camera
    void Position(GLdouble const &tempX, GLdouble const &tempY,
                  GLdouble const &tempZ, GLdouble const &tempAngle);

    // check whether ok to move
    void CheckCamera();

    // Used to pass direction to move or rotate  (i.e. 1, -1 or 0)
    void DirectionFB(int const &tempMove);
    void DirectionLR(int const &tempMove);
    void DirectionUD(int const &tempMove);
    void DirectionRotateLR(GLdouble const &tempMove);
    void DirectionLookUD(int const &tempMove);

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
    GLdouble m_incrementX  = 0.0;
    GLdouble m_incrementZ  = 0.0;
    int m_No_Plains        = 0;
    int m_plainNo          = 0;
    GLdouble m_plainHeight = 0.0;

    // rotation variables
    GLdouble m_rotateAngleLR = 0.0;
    GLdouble m_deltaAngleLR  = 0.0;
    GLdouble m_rotateAngleUD = 0.0;
    GLdouble m_deltaAngleUD  = 0.0;

    // movement variables
    GLdouble m_x = 0.0, m_y = 0.0, m_z = 0.0, m_zLast = 0.0, m_xLast = 0.0;
    GLdouble m_lookX = 0.0, m_lookY = 0.0, m_lookZ = 0.0;
    GLdouble m_lookXX = 0.0, m_lookYY = 0.0, m_lookZZ = 0.0;
    GLdouble m_deltaMoveLR = 0.0;
    GLdouble m_deltaMoveFB = 0.0;
    GLdouble m_deltaMoveUD = 0.0;
    GLdouble m_direction   = 0.0;

    // movement speed (step size)
    GLdouble m_rotateSpeed = 0.0;
    GLdouble m_moveSpeed   = 0.0;

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
    void ClimbSteps(GLdouble stepStart, GLdouble stepFinish,
                    GLdouble stepHeight, GLdouble stepWidth, int noSteps);
    void CheckSteps();

    //----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    Camera(const Camera &cam) = delete;
    Camera &operator=(const Camera &cam) = delete;
};

#endif
