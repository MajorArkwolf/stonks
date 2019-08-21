#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Stonk/OpenGl.hpp"

namespace Shay {
    class TexturedPolygons {
      public:
        static constexpr auto CHANNELS = 3;

        using Image = std::vector<unsigned char>;

        TexturedPolygons() = default;

        TexturedPolygons(const TexturedPolygons &) = delete;
        TexturedPolygons &operator=(const TexturedPolygons &) = delete;

        GLuint GetTexture(GLuint tempIndex);
        Image LoadTexture(const std::string &filename, size_t width, size_t height);

        void SetTextureCount(GLuint textureNo);
        void CreateTexture(GLuint textureNo, const Image &image,
                           size_t imgWidth, size_t imgHeight);
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
