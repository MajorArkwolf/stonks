#pragma once

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "Stonk/OpenGl.hpp"

namespace Shay {
    /**
     * @class  TexturedPolygons
     * @brief A class used to represent a singular polygon with texture
     */
    class TexturedPolygons {
      public:
        using Image = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

        /// The number of colour channels in the texture
        static constexpr auto CHANNELS = 3;

        /// Default constructor, set to default
        TexturedPolygons() = default;

        /// Overloaded copy constructor
        TexturedPolygons(const TexturedPolygons &) = delete;

        /// Overloaded assignment operator
        TexturedPolygons &operator=(const TexturedPolygons &) = delete;

        GLuint GetTexture(GLuint tempIndex);
        Image LoadTexture(const std::string &filename);

        void SetTextureCount(GLuint textureNo);
        void CreateTexture(GLuint textureNo, const Image &image);
        void CreateDisplayList(int XYZ, GLuint listNo, GLfloat xImgSize,
                               GLfloat zImgSize, GLfloat xStart, GLfloat yStart,
                               GLfloat zStart, GLfloat xTimes, GLfloat zTimes);
        void CreateYtoZWindowList(GLuint listNo, GLfloat xStart, GLfloat yStart,
                                  GLfloat ySize, GLfloat zStart, GLfloat zSize,
                                  GLfloat yImgSize, GLfloat zImgSize);
        void CreateXtoYWindowList(GLuint listNo, GLfloat zStart, GLfloat xStart,
                                  GLfloat xSize, GLfloat yStart, GLfloat ySize,
                                  GLfloat xImgSize, GLfloat yImgSize);
        void CreateAngledPolygon(GLuint listNo, GLfloat imageWidth,
                                 GLfloat imageHeight, GLfloat x1, GLfloat x2,
                                 GLfloat x3, GLfloat x4, GLfloat y1, GLfloat y2,
                                 GLfloat y3, GLfloat y4, GLfloat z1, GLfloat z2,
                                 GLfloat z3, GLfloat z4, int smallestX,
                                 int smallestZ);

      private:
        /// Vector containing texture enum numbers
        std::vector<GLuint> m_texture = {};

        void CreateXtoZTextureList(GLfloat xImgSize, GLfloat zImgSize,
                                   GLfloat xStart, GLfloat yStart, GLfloat zStart,
                                   GLfloat xTimes, GLfloat zTimes);
        void CreateXtoYTextureList(GLfloat xImgSize, GLfloat yImgSize,
                                   GLfloat xStart, GLfloat yStart, GLfloat zStart,
                                   GLfloat xTimes, GLfloat yTimes, bool flip);
        void CreateYtoZTextureList(GLfloat yImgSize, GLfloat zImgSize,
                                   GLfloat xStart, GLfloat yStart, GLfloat zStart,
                                   GLfloat yTimes, GLfloat zTimes, bool flip);

        // called from	CreateAngledPolygon determine how images are displayed
        void CreateTextureScale(GLfloat &xzImage1, GLfloat &xzImage2,
                                GLfloat &xzImage3, GLfloat &xzImage4,
                                GLfloat imageSize);
    };
}
