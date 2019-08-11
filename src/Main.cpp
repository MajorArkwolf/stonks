#include <math.h>
#include <string>
#include <time.h>

//#include <windows.h> // only used if mouse is required (not portable)
#include "Stonk/Stonk.hpp"
#include "Shay.hpp"

//--------------------------------------------------------------------------------------

// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
// Set speed (steps)
static GLfloat movementSpeed = 10.0f;
static GLfloat rotationSpeed = 0.005f;

//Eww Shay
Shay shay;

//--------------------------------------------------------------------------------------
//  Main function
//--------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    Stonk::run();

    return (0);
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void myinit() {
    auto &stonk = Stonk::get();

	shay.myinit();
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display() {
    shay.Display();
}

void drawAxis() {
    // Positive Z-direction = Red
    glColor3f(255, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100000);
    glEnd();

    // Positive Y-Direction = Green
    glColor3f(0, 255, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100000, 0);
    glEnd();

    // Positive X-Direction = Blue
    glColor3f(0, 0, 255);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(100000, 0, 0);
    glEnd();
}

