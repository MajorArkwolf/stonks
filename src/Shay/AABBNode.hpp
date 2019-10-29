#pragma once

#include "Stonk/OpenGl.hpp"

namespace Shay {
    /**
     * @class AABBNode
     * @brief  Stores data relating to collision information
     *
     * Used inside of the AABBList file
     *
     * @author Peter Crabbe
     * @version 02
     * @date 04/08/2019
     *
     */

    class AABBNode {
      public:
        /**
         * @brief Default constructor, not required
         */
        AABBNode() = default;

        /**
         * @brief Default Copy Constructor
         */
        AABBNode(const AABBNode &newNode) = default;

        /**
         * @brief Default Copy assignment
         */
        AABBNode &operator=(const AABBNode &newNode) = default;

        GLfloat GetMaxX();

        GLfloat GetMinX();

        GLfloat GetMaxY();

        GLfloat GetMinY();

        GLfloat GetMaxZ();

        GLfloat GetMinZ();

        void SetData(const GLfloat maxX, const GLfloat minX, const GLfloat maxY,
                     const GLfloat minY, const GLfloat maxZ, const GLfloat minZ);

      private:
        /// stores x,y,z co-ordinates
        struct XYZ {
            GLfloat x = 0.0, y = 0.0, z = 0.0;
        };
        /// stores max and min values of co-ordinates
        struct BoundingBox {
            XYZ max{};
            XYZ min{};
        };
        /// stores above info
        BoundingBox m_BBox{};
    };
}
