#pragma once

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class CameraMap {
      public:
        /// Default constructor
        CameraMap() {}

        /// Destructor
        ~CameraMap() {}

        /// Copy constructor, set to delete
        CameraMap(const CameraMap &cam) = delete;

        /// Overloaded assignment operator, set to delete
        CameraMap &operator=(const CameraMap &cam) = delete;

        // display the map
        void DisplayMap(int screenWidth, int screenHeight, GLfloat xPos,
                        GLfloat zPos, GLuint tempImage);

        // display the welcome screen
        void DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                  GLuint tempImage);

        void DisplayNoExit(int screenWidth, int screenHeight, GLuint tempImage);
    };
}
