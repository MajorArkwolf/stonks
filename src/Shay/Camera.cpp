//  camera.cpp
//
//  Implementation file for Camera Class
//  Defines all the methods declared, but not defined, in camera.h
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#include "Camera.h"

#include <math.h>

#include "Stonk/OpenGl.hpp"
#include "Math.hpp"

//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Camera::Camera() {
    m_rotateSpeed = 0.0f;
    m_moveSpeed   = 0.0f;

    ResetXYZ();

    m_deltaMoveFB = 0.0f;
    m_deltaMoveLR = 0.0f;
    m_deltaMoveUD = 0.0f;

    m_rotateAngleLR = 0.0f;
    m_rotateAngleUD = 0.0f;
    m_deltaAngleLR  = 0.0f;
    m_deltaAngleUD  = 0.0f;

    m_CollisionDetectionOn = true;
}

//--------------------------------------------------------------------------------------
// Reset camera values
//--------------------------------------------------------------------------------------
void Camera::ResetXYZ() {
    m_x = 0.0f;
    m_y = 1.75f;
    m_z = 0.0f;

    m_lookX = 0.0f;
    m_lookY = 0.0f;
    m_lookZ = -1.0f;

    m_lookXX = 1.0f;
    m_lookYY = 1.0f;
    m_lookZZ = 0.0f;
}

//--------------------------------------------------------------------------------------
//  Determine direction
//--------------------------------------------------------------------------------------
void Camera::DirectionFB(GLfloat tempMove) {
    m_deltaMoveFB = tempMove;
}
//--------------------------------------------------------------------------------------
void Camera::DirectionLR(GLfloat tempMove) {
    m_deltaMoveLR = tempMove;
}
//--------------------------------------------------------------------------------------
// Not used but allows up and don movement
void Camera::DirectionUD(GLfloat tempMove) {
    m_deltaMoveUD = tempMove;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionRotateLR(GLfloat tempMove) {
    m_deltaAngleLR = tempMove * m_rotateSpeed;
}

//--------------------------------------------------------------------------------------
void Camera::DirectionLookUD(GLfloat tempMove) {
    m_deltaAngleUD = tempMove * m_rotateSpeed;
}

//--------------------------------------------------------------------------------------
// Is ok to move camera backwards and forwards
//--------------------------------------------------------------------------------------
bool Camera::MoveFBOK() {
    bool tempReturn;
    if (m_deltaMoveFB < 0 || m_deltaMoveFB > 0) {
        tempReturn = true;
    } else {
        tempReturn = false;
    }
    return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to move camera sideways
//--------------------------------------------------------------------------------------
bool Camera::MoveLROK() {
    bool tempReturn;
    if (m_deltaMoveLR < 0 || m_deltaMoveLR > 0) {
        tempReturn = true;
    } else {
        tempReturn = false;
    }
    return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to move camera up and down (not used)
//--------------------------------------------------------------------------------------
bool Camera::MoveUDOK() {
    bool tempReturn;
    if (m_deltaMoveUD < 0 || m_deltaMoveUD > 0) {
        tempReturn = true;
    } else {
        tempReturn = false;
    }
    return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to rotate sideways
//--------------------------------------------------------------------------------------
bool Camera::RotateLROK() {
    bool tempReturn = false;

    if (m_rotateSpeed != 0.0f) {
        if ((m_deltaAngleLR / m_rotateSpeed) < 0 ||
            (m_deltaAngleLR / m_rotateSpeed) > 0) {
            tempReturn = true;
        } else {
            tempReturn = false;
        }
    }

    return tempReturn;
}

//--------------------------------------------------------------------------------------
// Is ok to rotate up and down
//--------------------------------------------------------------------------------------
bool Camera::LookUDOK() {
    bool tempReturn = false;

    if (m_rotateSpeed != 0.0f) {
        if ((m_deltaAngleUD / m_rotateSpeed) < 0 ||
            (m_deltaAngleUD / m_rotateSpeed) > 0) {
            tempReturn = true;
        } else {
            tempReturn = false;
        }
    }

    return tempReturn;
}

//--------------------------------------------------------------------------------------
// Move camera backwards and forwards
//--------------------------------------------------------------------------------------
void Camera::MoveFB() {
    // record previous co-ordinates
    m_xLast = m_x;
    m_zLast = m_z;

    // set movement step
    GLfloat moveZ = (m_deltaMoveFB * (m_lookZ)*m_moveSpeed);
    GLfloat moveX = (m_deltaMoveFB * (m_lookX)*m_moveSpeed);

    if (m_CollisionDetectionOn) {
        GLfloat startX = m_x + moveX * 5.0f;
        GLfloat startZ = m_z + moveZ * 5.0f;

        // check if collsion
        if (!(m_colDetect.Collide(startX + m_lookX, m_y + m_lookY,
                                  startZ + m_lookZ))) {
            // increment position
            m_x += moveX;
            m_z += moveZ;
            // check plain
            SetPlains(static_cast<int>(moveX), static_cast<int>(moveZ));
            // redisplay
            callGLLookAt();
        }
    } else {
        // increment position
        m_x += moveX;
        m_z += moveZ;
        // check plain
        SetPlains(static_cast<int>(moveX), static_cast<int>(moveZ));
        // redisplay
        callGLLookAt();
    }
}

//--------------------------------------------------------------------------------------
// Move camera left and right (sideways)
//--------------------------------------------------------------------------------------
void Camera::MoveLR() {
    // record previous co-ordinates
    m_zLast = m_z;
    m_xLast = m_x;

    // set movement step
    GLfloat moveZ = (m_deltaMoveLR * (m_lookZZ)*m_moveSpeed);
    GLfloat moveX = (m_deltaMoveLR * (m_lookXX)*m_moveSpeed);

    if (m_CollisionDetectionOn) {
        GLfloat startX = m_x + moveX * 1.0f;
        GLfloat startZ = m_z + moveZ * m_moveSpeed * 1.0f;

        // check if collsion
        if (!(m_colDetect.Collide(startX + m_lookXX, m_y + m_lookYY,
                                  startZ + m_lookZZ))) {
            // increment position
            m_x += moveX;
            m_z += moveZ;
            // check plain
            SetPlains(static_cast<int>(moveX), static_cast<int>(moveZ));
            // redisplay
            callGLLookAt();
        }
    } else {
        // increment position
        m_x += moveX;
        m_z += moveZ;
        SetPlains(static_cast<int>(moveX), static_cast<int>(moveZ));
        // redisplay
        callGLLookAt();
    }
}

//----------------------------------------------------------------------------------------
//  Places camera at the correct level on the current plain
//----------------------------------------------------------------------------------------
void Camera::SetPlains(const int &moveX, const int &moveZ) {
    // store number of plains (stops from looping through linked list each time)
    if (m_No_Plains == 0)
        m_No_Plains = m_Plain.GetListSize();

    for (int i = 0; i < m_No_Plains; i++) {
        // if camera is positioned on a plain
        if ((m_z <= m_Plain.GetZend(i)) && (m_z >= m_Plain.GetZstart(i)) &&
            (m_x <= m_Plain.GetXend(i)) && (m_x >= m_Plain.GetXstart(i))) {
            // if flat plain
            if (m_Plain.GetType(i) == 0) {
                m_y = m_Plain.GetYstart(i);

                m_plainNo     = i;
                m_plainHeight = m_Plain.GetYstart(i);
            }
            // if plain slopes in z direction
            if (m_Plain.GetType(i) == 2) {
                // if plain slopes up or down
                if (m_zLast > m_z) {
                    m_incrementZ = ((m_y - m_Plain.GetYstart(i)) /
                                    (m_z - m_Plain.GetZstart(i)));
                } else {
                    m_incrementZ =
                        ((m_Plain.GetYend(i) - m_y) / (m_Plain.GetZend(i) - m_z));
                }
                m_y += (m_incrementZ * moveZ);
            }
            // if plain slopes in x direction
            if (m_Plain.GetType(i) == 1) {
                // if plain slopes up or down
                if (m_xLast > m_x) {
                    m_incrementX = ((m_y - m_Plain.GetYstart(i)) /
                                    (m_x - m_Plain.GetXstart(i)));
                } else {
                    m_incrementX =
                        ((m_Plain.GetYend(i) - m_y) / (m_Plain.GetXend(i) - m_x));
                }
                m_y += (m_incrementX * moveX);
            }
        }
    }
}

//----------------------------------------------------------------------------------------
// Moves camera up and down (NOT USED)
//----------------------------------------------------------------------------------------
void Camera::MoveUD() {
    if (m_CollisionDetectionOn) {
        GLfloat startY = m_y + m_deltaMoveUD * (m_lookYY)*m_moveSpeed * 5.0f;

        if (!(m_colDetect.Collide(m_x + m_lookXX, startY + m_lookYY,
                                  m_z + m_lookZZ))) {
            m_y += m_deltaMoveUD * (m_lookYY)*m_moveSpeed;
            callGLLookAt();
        }
    } else {
        m_y += m_deltaMoveUD * (m_lookYY)*m_moveSpeed;
        callGLLookAt();
    }
}

//----------------------------------------------------------------------------------------
// Rotates camera left and right
//----------------------------------------------------------------------------------------
void Camera::RotateLR() {
    m_rotateAngleLR += m_deltaAngleLR;
    m_lookX  = sin(m_rotateAngleLR);
    m_lookZ  = -cos(m_rotateAngleLR);
    m_lookXX = sin(m_rotateAngleLR + PI_F / 2.0f);
    m_lookZZ = -cos(m_rotateAngleLR + PI_F / 2.0f);
    callGLLookAt();
}

//----------------------------------------------------------------------------------------
//  Rotates camera up and down
//----------------------------------------------------------------------------------------
void Camera::LookUD() {
    m_rotateAngleUD += m_deltaAngleUD;
    m_lookY = sin(m_rotateAngleUD);
    callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Positions camera at co-ordinates of parameters
//----------------------------------------------------------------------------------------
void Camera::Position(GLfloat const &tempX, GLfloat const &tempY,
                      GLfloat const &tempZ, GLfloat const &tempAngle) {
    ResetXYZ();

    m_x = tempX;
    m_y = tempY;
    m_z = tempZ;

    // rotate to correct angle
    m_rotateAngleLR = tempAngle * (PI_F / 180.0f);
    m_lookX         = sin(m_rotateAngleLR);
    m_lookZ         = -cos(m_rotateAngleLR);
    m_lookXX        = sin(m_rotateAngleLR + PI_F / 2.0f);
    m_lookZZ        = -cos(m_rotateAngleLR + PI_F / 2.0f);
    m_rotateAngleUD = 0.0;
    m_deltaAngleUD  = 0.0;

    // redislay
    callGLLookAt();
}

//----------------------------------------------------------------------------------------
// Check ok to move
//----------------------------------------------------------------------------------------
void Camera::CheckCamera() {
    if (MoveFBOK())
        MoveFB();
    if (MoveLROK())
        MoveLR();
    if (MoveUDOK())
        MoveUD();
    if (RotateLROK())
        RotateLR();
    if (LookUDOK())
        LookUD();
}

//----------------------------------------------------------------------------------------
//  Redisplay new camera view
//----------------------------------------------------------------------------------------
void Camera::callGLLookAt() {
    glLoadIdentity();
    gluLookAt(static_cast<double>(m_x), static_cast<double>(m_y),
              static_cast<double>(m_z), static_cast<double>(m_x + m_lookX),
              static_cast<double>(m_y + m_lookY),
              static_cast<double>(m_z + m_lookZ), static_cast<double>(0.0f),
              static_cast<double>(1.0f), static_cast<double>(0.0f));
}

//--------------------------------------------------------------------------------------
// Display map of world
//----------------------------------------------------------------------------------------

void Camera::DisplayMap(const int &screenWidth, const int &screenHeight,
                        const GLuint &tempImage) {
    m_map.DisplayMap(screenWidth, screenHeight, GetLR(), GetFB(), tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayWelcomeScreen(const int &screenWidth, const int &screenHeight,
                                  const int &tempExit, const GLuint &tempImage) {
    m_map.DisplayWelcomeScreen(screenWidth, screenHeight, tempExit, tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayNoExit(const int &screenWidth, const int &screenHeight,
                           const GLuint &tempImage) {
    m_map.DisplayNoExit(screenWidth, screenHeight, tempImage);
}

//----------------------------------------------------------------------------------------

void Camera::SetWorldCoordinates(const GLfloat &tempX, const GLfloat &tempZ) {
    m_colDetect.SetWorldX(tempX);
    m_colDetect.SetWorldZ(tempZ);
}

//----------------------------------------------------------------------------------------

void Camera::SetPlains(const int tempType, const GLfloat tempXs,
                       const GLfloat tempXe, const GLfloat tempYs,
                       const GLfloat tempYe, const GLfloat tempZs,
                       const GLfloat tempZe) {
    m_Plain.AddToStart(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
}

//--------------------------------------------------------------------------------------
// THE BELOW FUNCTIONS ARE NOT IMPLEMENTED
// Originally created to climb stairs
// The Plain object is used instead
//----------------------------------------------------------------------------------------
void Camera::CheckSteps() {

    // ClimbSteps(10000.0, 9430.0, 48.0, 142.0, 4);
    // ClimbSteps(8920.0, 8210.0, 48.0, 142.0, 5);
    // ClimbSteps(7698.0, 6988.0, 48.0, 142.0, 5);
    // ClimbSteps(6476.0, 5766.0, 48.0, 142.0, 5);
}

//----------------------------------------------------------------------------------------

void Camera::ClimbSteps(GLfloat stepStart, GLfloat stepFinish,
                        GLfloat stepHeight, GLfloat stepWidth, int noSteps) {
    GLfloat tempUpSteps;
    if ((m_z < stepStart) && (m_z > stepFinish)) {
        bool stepped = false;
        if (m_z > m_zLast) {
            m_direction = 1.0;
            tempUpSteps = stepWidth;
        } else {
            m_direction = -1.0;
            tempUpSteps = 0.0;
        }

        for (int i = 0; i < noSteps + 1; i++) {
            if ((m_z < (stepStart - (i * stepWidth) + stepWidth / 2) - tempUpSteps) &&
                (m_z > (stepStart - (i * stepWidth) - stepWidth / 2) - tempUpSteps)) {
                if (stepped == false) {
                    m_z = stepStart - (stepWidth * i) +
                          (m_direction * stepWidth) - tempUpSteps;
                    m_y += stepHeight * m_direction;

                    stepped = true;
                    DirectionFB(0);
                    DirectionLR(0);
                }
            }
        }
    }
}
//----------------------------------------------------------------------------------------

