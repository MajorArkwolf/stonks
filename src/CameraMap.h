//  cameraMap.h
//  Header file for the cameraMap class
//  Displays a map and welcome screen in 2D on the screen
//
//  Shay Leary, April 2005
//--------------------------------------------------------------------------------------

#ifndef CAMERA_MAP_H
#    define CAMERA_MAP_H

#    include "Glut.hpp"

//--------------------------------------------------------------------------------------

class CameraMap {
  public:
    CameraMap() {}
    ~CameraMap() {}

    //----------------------------------------------------------------------------------

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

#endif

//--------------------------------------------------------------------------------------
