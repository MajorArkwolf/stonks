#include <cstddef>

#include "Shay/Shay.hpp"
#include "Stonk/Engine.hpp"

int main(int argc, char **argv) {
    Stonk::Engine::run();

    return EXIT_SUCCESS;
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
