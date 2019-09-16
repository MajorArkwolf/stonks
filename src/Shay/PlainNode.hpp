#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>

#include "Stonk/OpenGl.hpp"

namespace Shay {
    /**
     * @class  PlainNode
     * @brief A class used to represent a slope node within the plain vector
     */
    class PlainNode {
      public:
        enum class Slope { FLAT, ZY, XY };

        /**
         * @brief Default constructor, not required
         */
        PlainNode() {
            Clear();
        }

        /**
         * @brief Default Destructor, not required
         */
        ~PlainNode() {
            Clear();
        }

        /**
         * @brief Copy Constructor, defaulted
         */
        PlainNode(const PlainNode &newNode) = default;

        /**
         * @brief Copy assignment, defaulted
         */
        PlainNode &operator=(const PlainNode &newNode) = default;

        // Deprecated, to be deleted when safe to do so.
        void Clear();

        Slope GetType();
        GLfloat GetXstart();
        GLfloat GetXend();
        GLfloat GetYstart();
        GLfloat GetYend();
        GLfloat GetZstart();
        GLfloat GetZend();
        void SetData(Slope tempType, GLfloat tempXs, GLfloat tempXe, GLfloat tempYs,
                     GLfloat tempYe, GLfloat tempZs, GLfloat tempZe);

      private:
        /// Stores type of plain:
        /// (0: flat plane)
        /// (1: incline from z to y)
        /// (2: incline from x to y)
        Slope m_type{};

        /// stores start and end co-ordinates of plane on x, y and z axis
        GLfloat m_xPlainStart = 0, m_xPlainEnd = 0;
        GLfloat m_yPlainStart = 0, m_yPlainEnd = 0;
        GLfloat m_zPlainStart = 0, m_zPlainEnd = 0;
    };
}
