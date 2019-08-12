#pragma once

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class CameraMap {
      public:
        CameraMap() {}
        ~CameraMap() {}

        // display the map
        void DisplayMap(const int &screenWidth, const int &screenHeight,
                        const GLfloat &xPos, const GLfloat &zPos,
                        const GLuint &tempImage);

        // display the welcome screen
        void DisplayWelcomeScreen(const int &screenWidth, const int &screenHeight,
                                  const int &tempExit, const GLuint &tempImage);

        void DisplayNoExit(const int &screenWidth, const int &screenHeight,
                           const GLuint &tempImage);

      private:
        // Privatised copy constructor and assignment operator
        CameraMap(const CameraMap &cam) = delete;
        CameraMap &operator=(const CameraMap &cam) = delete;
    };
};
