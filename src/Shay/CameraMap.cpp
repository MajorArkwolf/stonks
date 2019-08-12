//  cameraMap.cpp
//
//  Implementation file for CameraMap Class
//  Defines all the methods declared, but not defined, in cameraMap.h
//
//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#include "CameraMap.h"
#include "Stonk/OpenGl.hpp"

//--------------------------------------------------------------------------------------
//  Display a map with a cursor on it, which moves with the camera
//--------------------------------------------------------------------------------------

void CameraMap::DisplayMap(const int &screenWidth, const int &screenHeight,
                           const GLfloat &xPos, const GLfloat &zPos,
                           const GLuint &tempImage) {
    GLfloat tempX = xPos / 163.0f - 2096.0f / 163.0f;
    GLfloat tempZ = zPos / 164.0f - 4688.0f / 164.0f;
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // mover the origin from the bottom left corner
    // to the upper left corner
    glTranslatef(0, -screenHeight, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // display the cursor of the camera position
    glBegin(GL_QUADS);
    glVertex3f(219.0f - tempX - 2.0f, 256.0f - tempZ - 2.0f, 0.0f);
    glVertex3f(219.0f - tempX + 2.0f, 256.0f - tempZ - 2.0f, 0.0f);
    glVertex3f(219.0f - tempX + 2.0f, 256.0f - tempZ + 2.0f, 0.0f);
    glVertex3f(219.0f - tempX - 2.0f, 256.0f - tempZ + 2.0f, 0.0f);
    glEnd();

    // display map
    glBindTexture(GL_TEXTURE_2D, tempImage);
    glCallList(448);

    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

//--------------------------------------------------------------------------------------
//  Displays a welcome or exit screen
//--------------------------------------------------------------------------------------
void CameraMap::DisplayWelcomeScreen(const int &screenWidth,
                                     const int &screenHeight, const int &tempExit,
                                     const GLuint &tempImage) {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(screenWidth / 2.0f - 256.0f, -screenHeight / 2.0f - 256.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display exit screen or welcome screen
    if (tempExit == 1) {
        glBindTexture(GL_TEXTURE_2D, tempImage);
    } else {
        glBindTexture(GL_TEXTURE_2D, tempImage);
    }
    // display image
    glCallList(449);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void CameraMap::DisplayNoExit(const int &screenWidth, const int &screenHeight,
                              const GLuint &tempImage) {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(screenWidth / 2.0f - 128.0f, -screenHeight / 2.0f - 32.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(454);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
