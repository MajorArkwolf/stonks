#pragma once

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class CameraMap {
      public:
        CameraMap() {}
        ~CameraMap() {}

        // display the map
        void DisplayMap(int screenWidth, int screenHeight, GLfloat xPos,
                        GLfloat zPos, GLuint tempImage);

        // display the welcome screen
        void DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                  int tempExit, GLuint tempImage);

        void DisplayNoExit(int screenWidth, int screenHeight, GLuint tempImage);

        CameraMap(const CameraMap &cam) = delete;
        CameraMap &operator=(const CameraMap &cam) = delete;
    };
};
