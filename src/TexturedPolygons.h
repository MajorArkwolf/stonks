//  texturedPolygon.h
//  Header file for the texturedPolygon class
//
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef TEXTURE_POLYGON_H
#    define TEXTURE_POLYGON_H

//--------------------------------------------------------------------------------------

#    include <stdio.h> // should really be using c++, but didn't get time to change
#    include <stdlib.h>

#    include "OpenGl.hpp"

//--------------------------------------------------------------------------------------

class TexturedPolygons {
  public:
    TexturedPolygons() = default;
    ~TexturedPolygons() {
        Clear();
    }

    //----------------------------------------------------------------------------------

    // returns texture
    GLuint GetTexture(const GLuint &tempIndex) {
        return m_texture[tempIndex];
    }

    // loads a raw image file into memory
    GLubyte *LoadTexture(const char *filename, size_t imgWidth, size_t imgHeight);

    // set the number of textures to be used
    void SetTextureCount(const GLuint &textureNo);

    // creates texture and set required values for texture mapping
    void CreateTexture(GLuint textureNo, unsigned char *image, size_t imgWidth,
                       size_t imgHeight);

    // calls function to creates display list to contain image
    void CreateDisplayList(const int &XYZ, const GLuint &listNo,
                           const GLfloat &xImgSize, const GLfloat &zImgSize,
                           const GLfloat &xStart, const GLfloat &yStart,
                           const GLfloat &zStart, const GLfloat &xTimes,
                           const GLfloat &zTimes);

    // used to create display lists where image is larger than world scale on YZ axis
    void CreateYtoZWindowList(const GLuint &listNo, const GLfloat &xStart,
                              const GLfloat &yStart, const GLfloat &ySize,
                              const GLfloat &zStart, const GLfloat &zSize,
                              const GLfloat &yImgSize, const GLfloat &zImgSize);

    // used to create display lists where image is larger than world scale on XY axis
    void CreateXtoYWindowList(const GLuint &listNo, const GLfloat &zStart,
                              const GLfloat &xStart, const GLfloat &xSize,
                              const GLfloat &yStart, const GLfloat &ySize,
                              const GLfloat &xImgSize, const GLfloat &yImgSize);

    // used to create display lists where image is on an angle
    void CreateAngledPolygon(const GLuint &listNo, const GLfloat &imageWidth,
                             const GLfloat &imageHeight, const GLfloat &x1,
                             const GLfloat &x2, const GLfloat &x3,
                             const GLfloat &x4, const GLfloat &y1,
                             const GLfloat &y2, const GLfloat &y3,
                             const GLfloat &y4, const GLfloat &z1,
                             const GLfloat &z2, const GLfloat &z3,
                             const GLfloat &z4, const int &smallestX,
                             const int &smallestZ);

  private:
    // pointer to display list
    GLuint *m_texture{};

    // returns image file
    GLubyte *LoadRawImageFile(const char *filename, size_t width, size_t height);

    void Clear();

    // creates display list to contain image on X Z axis
    void CreateXtoZTextureList(const GLfloat &xImgSize, const GLfloat &zImgSize,
                               const GLfloat &xStart, const GLfloat &yStart,
                               const GLfloat &zStart, const GLfloat &xTimes,
                               const GLfloat &zTimes);

    // creates display list to contain image on X Y axis
    void CreateXtoYTextureList(const GLfloat &xImgSize, const GLfloat &yImgSize,
                               const GLfloat &xStart, const GLfloat &yStart,
                               const GLfloat &zStart, const GLfloat &xTimes,
                               const GLfloat &yTimes, const bool &flip);

    // creates display list to contain image on Y Z axis
    void CreateYtoZTextureList(const GLfloat &yImgSize, const GLfloat &zImgSize,
                               const GLfloat &xStart, const GLfloat &yStart,
                               const GLfloat &zStart, const GLfloat &yTimes,
                               const GLfloat &zTimes, const bool &flip);

    // called from	CreateAngledPolygon determine how images are displayed
    void CreateTextureScale(GLfloat &xzImage1, GLfloat &xzImage2, GLfloat &xzImage3,
                            GLfloat &xzImage4, const GLfloat &imageSize);

    //----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    TexturedPolygons(const TexturedPolygons &tp) = delete;
    TexturedPolygons &operator=(const TexturedPolygons &tp) = delete;
};

#endif

//----------------------------------------------------------------------------------
