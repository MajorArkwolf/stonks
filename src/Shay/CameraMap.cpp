
#include "CameraMap.hpp"

#include "Stonk/OpenGl.hpp"

using Shay::CameraMap;

/**
 * @brief Displays a map of murdoch with a pointer showing the player position
 * @param screenWidth The current width of the screen
 * @param screenHeight The current height of the screen
 * @param xPos The x position of the player
 * @param zPos The z position of the player
 * @param tempImage The enum number of the texture to display
 */
void CameraMap::DisplayMap(int screenWidth, int screenHeight, GLfloat xPos,
                           GLfloat zPos, GLuint tempImage) {
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
    glTranslatef(0, static_cast<GLfloat>(-screenHeight), 0);

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

/**
 * @brief Displays the welcome or exit screen
 * @param screenWidth The current width of the screen
 * @param screenHeight The current height of the screen
 * @param textureNum The enum value for the texture
 */
void CameraMap::DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                     GLuint textureNum) {
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

    glBindTexture(GL_TEXTURE_2D, textureNum);

    // display image
    glCallList(449);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

/**
 * @brief Displays the no exit dialog
 * @param screenWidth The current width of the screen
 * @param screenHeight The current height of the screen
 * @param textureNum The enum value for the texture
 */

void CameraMap::DisplayNoExit(int screenWidth, int screenHeight, GLuint textureNum) {
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
    glBindTexture(GL_TEXTURE_2D, textureNum);
    // display image
    glCallList(454);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
