#include "TexturedPolygons.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using Shay::TexturedPolygons;

using std::ifstream;
using std::ofstream;
using std::runtime_error;
using std::string;
using Image = TexturedPolygons::Image;

/**
 * @brief Returns the enum number of the texture that the polygon at the specified index location is using
 * @param tempIndex The index number in the polygon vector to read from
 * @return Enum number of texture
 */
GLuint TexturedPolygons::GetTexture(GLuint tempIndex) {
    return m_texture[tempIndex];
}

/**
 * @brief Returns an SDL2 image generated from the file at the given path
 * @param fileName The filename of the image file to read from
 * @return The SDL2 image that was generated
 */
Image TexturedPolygons::LoadTexture(const string &filename) {
    auto path  = string{SDL_GetBasePath()} + "res/" + filename;
    auto image = Image{IMG_Load(path.c_str()), &SDL_FreeSurface};

    if (image == nullptr) {
        throw runtime_error{string{"Unable to load texture: "} + path};
    }

    return image;
}

/**
 * @brief Sets the number of textures to be used in the program
 * @param textureNo The number of elements to set the vector to be able to contain
 */

void TexturedPolygons::SetTextureCount(GLuint textureNo) {
    m_texture.resize(textureNo);

    glGenTextures(static_cast<GLsizei>(textureNo), &m_texture[0]);
}

/**
 * @brief Creates textures and sets the required values for mapping
 * @param textureNo The index location of the texture
 * @param image The SDL2 image to bind
 */
void TexturedPolygons::CreateTexture(GLuint textureNo, const Image &image) {
    glBindTexture(GL_TEXTURE_2D, m_texture[textureNo]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->w, image->h, GL_BGR,
                      GL_UNSIGNED_BYTE, image->pixels);
}

/**
 * @brief  Calls functions to create display lists, depending on parameters.
 *  I created these functions very early on in the program before I had a full understanding,
 *  therefore I would probably create a better function for the purpose, but this works well.
 *
 * @param xyz
 * @param listNo The list number
 * @param xImgSize Image size in X direction
 * @param zImgSize Image size in Z direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param xTimes Multiplier in X firection
 * @param zTimes Multiplier in Z direction
 */
void TexturedPolygons::CreateDisplayList(int XYZ, GLuint listNo, GLfloat xImgSize,
                                         GLfloat zImgSize, GLfloat xStart,
                                         GLfloat yStart, GLfloat zStart,
                                         GLfloat xTimes, GLfloat zTimes) {
    glNewList(listNo, GL_COMPILE);
    glBegin(GL_QUADS);
    switch (XYZ) {
        case 0:
            // create list where image is on X and Y axis
            CreateXtoYTextureList(xImgSize, zImgSize, xStart, yStart, zStart,
                                  xTimes, zTimes, false);
            break;
        case 1:
            // create list where image is on X and Z axis
            CreateXtoZTextureList(xImgSize, zImgSize, xStart, yStart, zStart,
                                  xTimes, zTimes);
            break;
        case 2:
            // create list where image is on Y and Z axis
            CreateYtoZTextureList(xImgSize, zImgSize, xStart, yStart, zStart,
                                  xTimes, zTimes, false);
            break;
        case 3:
            // create list where (flipped) image is on X and Z axis
            CreateYtoZTextureList(xImgSize, zImgSize, xStart, yStart, zStart,
                                  xTimes, zTimes, true);
            break;
        case 4:
            // create list where (flipped) image is on X and Y axis
            CreateXtoYTextureList(xImgSize, zImgSize, xStart, yStart, zStart,
                                  xTimes, zTimes, true);
            break;
    }
    glEnd();
    glEndList();
}

/**
 * @brief  Create display list with image plotted on X to Z axis
 *
 * @param xImgSize Image size in X direction
 * @param zImgSize Image size in Z direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param xTimes Mulltiplier in X direction
 * @param zTimes Multiplier in Z direction
 */
void TexturedPolygons::CreateXtoZTextureList(GLfloat xImgSize, GLfloat zImgSize,
                                             GLfloat xStart, GLfloat yStart,
                                             GLfloat zStart, GLfloat xTimes,
                                             GLfloat zTimes) {
    glTexCoord2f(0.0, 0.0);
    glVertex3f(xStart, yStart, zStart);
    glTexCoord2f(0.0, zTimes);
    glVertex3f(xStart, yStart, zStart + (zImgSize * zTimes));
    glTexCoord2f(xTimes, zTimes);
    glVertex3f(xStart + (xImgSize * xTimes), yStart, zStart + (zImgSize * zTimes));
    glTexCoord2f(xTimes, 0.0);
    glVertex3f(xStart + (xImgSize * xTimes), yStart, zStart);
}

/**
 * @brief  Create display list with image plotted on X to Y axis
 *
 * @param xImgSize Image size in X direction
 * @param yImgSize Image size in y direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param xTimes Multiplier in X direction
 * @param yTimes Multiplier in Y direction
 * @param flip If image needs to be flipped
 */
void TexturedPolygons::CreateXtoYTextureList(GLfloat xImgSize, GLfloat yImgSize,
                                             GLfloat xStart, GLfloat yStart,
                                             GLfloat zStart, GLfloat xTimes,
                                             GLfloat yTimes, bool flip) {
    GLfloat flipX = 0.0;
    GLfloat tempX = xTimes;
    // if image is required to be flipped (this will be improved)
    if (flip) {
        flipX = xTimes;
        tempX = 0.0;
    }
    glTexCoord2f(flipX, 0.0);
    glVertex3f(xStart, yStart, zStart);
    glTexCoord2f(flipX, yTimes);
    glVertex3f(xStart, yStart + (yImgSize * yTimes), zStart);
    glTexCoord2f(tempX, yTimes);
    glVertex3f(xStart + (xImgSize * xTimes), yStart + (yImgSize * yTimes), zStart);
    glTexCoord2f(tempX, 0.0);
    glVertex3f(xStart + (xImgSize * xTimes), yStart, zStart);
}

/**
 * @brief  Create display list with image plotted on Y to A axis
 *
 * @param yImgSize Image size in y direction
 * @param zImgSize Image size in z direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param yTimes Multiplier in Y direction
 * @param zTimes Multiplier in Z direction
 *@param flip If image needs to be flipped
 */
void TexturedPolygons::CreateYtoZTextureList(GLfloat yImgSize, GLfloat zImgSize,
                                             GLfloat xStart, GLfloat yStart,
                                             GLfloat zStart, GLfloat yTimes,
                                             GLfloat zTimes, bool flip) {
    GLfloat flipZ = 0.0;
    GLfloat tempZ = zTimes;
    // if image is required to be flipped
    if (flip) {
        flipZ = zTimes;
        tempZ = 0.0;
    }
    glTexCoord2f(0.0, flipZ);
    glVertex3f(xStart, yStart, zStart);
    glTexCoord2f(0.0, tempZ);
    glVertex3f(xStart, yStart, zStart + (zImgSize * zTimes));
    glTexCoord2f(yTimes, tempZ);
    glVertex3f(xStart, yStart + (yImgSize * yTimes), zStart + (zImgSize * zTimes));
    glTexCoord2f(yTimes, flipZ);
    glVertex3f(xStart, yStart + (yImgSize * yTimes), zStart);
}

/**
 * @brief  Used to create display lists where the image size is not to scale with the
 *  world co-ordinates. This is mainly used to create lists for the larger
 *  images (i.e. windows and doors), where they are to large to keep to scale.
 *
 * @param yImgSize Image size in y direction
 * @param zImgSize Image size in z direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param ySize Multiplier in Y direction
 * @param zSize Multiplier in Z direction
 * @param listNo The list Number
 */
void TexturedPolygons::CreateYtoZWindowList(GLuint listNo, GLfloat xStart,
                                            GLfloat yStart, GLfloat ySize,
                                            GLfloat zStart, GLfloat zSize,
                                            GLfloat yImgSize, GLfloat zImgSize) {
    glNewList(listNo, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, zImgSize);
    glVertex3f(xStart, yStart, zStart);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(xStart, yStart, zStart + zSize);
    glTexCoord2f(yImgSize, 0.0);
    glVertex3f(xStart, yStart + ySize, zStart + zSize);
    glTexCoord2f(yImgSize, zImgSize);
    glVertex3f(xStart, yStart + ySize, zStart);
    glEnd();
    glEndList();
}

//--------------------------------------------------------------------------------------

/**
 * @brief  Used to create display lists where the image size is not to scale with the
 *  world co-ordinates. This is mainly used to create lists for the larger
 *  images (i.e. windows and doors), where they are to large to keep to scale.
 *
 * @param yImgSize Image size in y direction
 * @param xImgSize Image size in x direction
 * @param xStart Start x-coordinate
 * @param yStart Start y-coordinate
 * @param zStart Start z-coordinate
 * @param ySize Multiplier in Y direction
 * @param xSize Multiplier in X direction
 * @param listNo The list Number
 */
void TexturedPolygons::CreateXtoYWindowList(GLuint listNo, GLfloat zStart,
                                            GLfloat xStart, GLfloat xSize,
                                            GLfloat yStart, GLfloat ySize,
                                            GLfloat xImgSize, GLfloat yImgSize) {
    glNewList(listNo, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(xStart, yStart, zStart);
    glTexCoord2f(xImgSize, 0.0);
    glVertex3f(xStart + xSize, yStart, zStart);
    glTexCoord2f(xImgSize, yImgSize);
    glVertex3f(xStart + xSize, yStart + ySize, zStart);
    glTexCoord2f(0.0, yImgSize);
    glVertex3f(xStart, yStart + ySize, zStart);
    glEnd();
    glEndList();
}

/**
 * @brief  Used to create display lists where the image is on an angle.
 *  The final two parameters are used to rotate the image so that it appears correctly.
 *  This works by passing the number of the smallest co-ordinate.
 *  Eg, smallestX = 1 to 4 for smallest x values (image angles on the XZ or XY axis)
 *      smallestX = 5 to 8 for smallest y values (image angles on the YZ)
 *      smallestZ = 1 to 4 for smallest z values (image angles on the XZ or YZ)
 *      smallestZ = 5 to 8 for smallest y values (image angles on the XY)
 *
 * @param listNo The list number
 * @param imageWidth The width of the image
 * @param imageHeight The height of the image
 * @param x1 X-coordinate 1
 * @param x2 X-coordinate 2
 * @param x3 X-coordinate 3
 * @param x4 X-coordinate 4
 * @param y1 Y-coordinate 1
 * @param y2 Y-coordinate 2
 * @param y3 Y-coordinate 3
 * @param y4 Y-coordinate 4
 * @param z1 Z-coordinate 1
 * @param z2 Z-coordinate 2
 * @param z3 Z-coordinate 3
 * @param z4 Z-coordinate 4
 * @param smallestX The smallest X value
 * @param smallestZ The smallest Y value
 */
void TexturedPolygons::CreateAngledPolygon(GLuint listNo, GLfloat imageWidth,
                                           GLfloat imageHeight, GLfloat x1,
                                           GLfloat x2, GLfloat x3, GLfloat x4,
                                           GLfloat y1, GLfloat y2, GLfloat y3,
                                           GLfloat y4, GLfloat z1, GLfloat z2,
                                           GLfloat z3, GLfloat z4,
                                           int smallestX, int smallestZ) {
    GLfloat xImage1 = x1;
    GLfloat xImage2 = x2;
    GLfloat xImage3 = x3;
    GLfloat xImage4 = x4;
    GLfloat zImage1 = z1;
    GLfloat zImage2 = z2;
    GLfloat zImage3 = z3;
    GLfloat zImage4 = z4;

    if (smallestX == 1) {
        CreateTextureScale(xImage1, xImage2, xImage3, xImage4, imageWidth);
    } else if (smallestX == 2) {
        CreateTextureScale(xImage2, xImage1, xImage3, xImage4, imageWidth);
    } else if (smallestX == 3) {
        CreateTextureScale(xImage3, xImage1, xImage2, xImage4, imageWidth);
    } else if (smallestX == 4) {
        CreateTextureScale(xImage4, xImage1, xImage2, xImage3, imageWidth);
    } else {
        xImage1 = y1;
        xImage2 = y2;
        xImage3 = y3;
        xImage4 = y4;
        if (smallestX == 5) {
            CreateTextureScale(xImage1, xImage2, xImage3, xImage4, imageWidth);
        } else if (smallestX == 6) {
            CreateTextureScale(xImage2, xImage1, xImage3, xImage4, imageWidth);
        } else if (smallestX == 7) {
            CreateTextureScale(xImage3, xImage1, xImage2, xImage4, imageWidth);
        } else if (smallestX == 8) {
            CreateTextureScale(xImage4, xImage1, xImage2, xImage3, imageWidth);
        }
    }
    if (smallestZ == 1) {
        CreateTextureScale(zImage1, zImage2, zImage3, zImage4, imageHeight);
    } else if (smallestZ == 2) {
        CreateTextureScale(zImage2, zImage1, zImage3, zImage4, imageHeight);
    } else if (smallestZ == 3) {
        CreateTextureScale(zImage3, zImage1, zImage2, zImage4, imageHeight);
    } else if (smallestZ == 4) {
        CreateTextureScale(zImage4, zImage1, zImage2, zImage3, imageHeight);
    } else {
        zImage1 = y1;
        zImage2 = y2;
        zImage3 = y3;
        zImage4 = y4;
        if (smallestZ == 5) {
            CreateTextureScale(zImage1, zImage2, zImage3, zImage4, imageHeight);
        } else if (smallestZ == 6) {
            CreateTextureScale(zImage2, zImage1, zImage3, zImage4, imageHeight);
        } else if (smallestZ == 7) {
            CreateTextureScale(zImage3, zImage1, zImage2, zImage4, imageHeight);
        } else if (smallestZ == 8) {
            CreateTextureScale(zImage4, zImage1, zImage2, zImage3, imageHeight);
        }
    }
    // create display list
    glNewList(static_cast<GLuint>(listNo), GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(xImage1, zImage1);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(xImage2, zImage2);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(xImage3, zImage3);
    glVertex3f(x3, y3, z3);
    glTexCoord2f(xImage4, zImage4);
    glVertex3f(x4, y4, z4);
    glEnd();
    glEndList();
}

/**
 * @brief Called from	CreateAngledPolygon determine how images are displayed
 *
 * @param xzImage1 The first xz coordinate
 * @param xzImage2 The second xz coordinate
 * @param xzImage3 The third xz coordinate
 * @param xzImage4 The frouth xz coordinate
 * @param imageSize The size of the image
 */
void TexturedPolygons::CreateTextureScale(GLfloat &xzImage1, GLfloat &xzImage2,
                                          GLfloat &xzImage3, GLfloat &xzImage4,
                                          GLfloat imageSize) {
    xzImage2 = ((xzImage2 - xzImage1) / imageSize);
    xzImage3 = ((xzImage3 - xzImage1) / imageSize);
    xzImage4 = ((xzImage4 - xzImage1) / imageSize);
    xzImage1 = 0.0;
}

//--------------------------------------------------------------------------------------
