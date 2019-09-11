#pragma once

#include <cstddef>

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "CameraMap.hpp"
#include "Collision.hpp"
#include "PlainLinkedList.hpp"
#include "PlainNode.hpp"

//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world.
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005

namespace Shay {
    class Camera {
      public:
        /// Movement speed multiplier for the camera
        GLfloat MOVEMENT_SPEED = 2000.0f;

        /// Mouse movement camera look multiplier
        static constexpr GLfloat LOOK_SPEED = 0.005f;

        /**
         * @brief Default constructor, set to default
         */

        Camera() = default;

        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        //  Set Methods
        //----------------------------------------------------------------------------------
        // sets initial value for bounding boxes (in the array AABB)
        void SetAABBMaxX(GLfloat tempX) {
            m_colDetect.SetAABBMaxX(tempX);
        }
        void SetAABBMinX(GLfloat tempX) {
            m_colDetect.SetAABBMinX(tempX);
        }
        void SetAABBMaxY(GLfloat tempY) {
            m_colDetect.SetAABBMaxY(tempY);
        }
        void SetAABBMinY(GLfloat tempY) {
            m_colDetect.SetAABBMinY(tempY);
        }
        void SetAABBMaxZ(GLfloat tempZ) {
            m_colDetect.SetAABBMaxZ(tempZ);
        }
        void SetAABBMinZ(GLfloat tempZ) {
            m_colDetect.SetAABBMinZ(tempZ);
        }

        // set step and rotation size
        void SetRotateSpeed(GLfloat tempSpeed) {
            m_rotateSpeed = tempSpeed;
        }

        void SetMoveSpeed(GLfloat tempSpeed) {
            m_moveSpeed = tempSpeed;
        }

        // set the co-ordinates of the world
        void SetWorldCoordinates(GLfloat tempX, GLfloat tempZ);
        // creates a linked list for each quadrant of the world and places the
        // bounding box data in each.  Then clears and deletes AABB array.
        void InitiateBoundingBoxes() {
            m_colDetect.CreateLinkedList();
        }

        // sets the co-ordinate of each plain
        void SetPlains(PlainNode::Slope tempType, GLfloat tempXs,
                       GLfloat tempXe, GLfloat tempYs, GLfloat tempYe,
                       GLfloat tempZs, GLfloat tempZe);

        //----------------------------------------------------------------------------------
        //  Get Methods
        //----------------------------------------------------------------------------------
        auto getForwardDir() const -> glm::vec3;

        /**
         * @brief Returns the X coordinate of the camera
         * @return The x coordinate of the camera
         */
        GLfloat GetLR() {
            return this->position.x;
        }

        /**
         * @brief Returns the Y coordinate of the camera
         * @return The Y coordinate of the camera
         */
        GLfloat GetUD() {
            return this->position.y;
        }

        /**
         * @brief Returns the Z coordinate of the camera
         * @return The Z coordinate of the camera
         */
        GLfloat GetFB() {
            return this->position.z;
        }

        /**
         * @brief Returns the Max X coordinate of the bounding box
         * @return The max X coordinate
         */
        GLfloat GetAABBMaxX() {
            return m_colDetect.GetAABBMaxX();
        }

        /**
         * @brief Returns the min X value for the bounding box
         * @return The min X coordinate
         */
        GLfloat GetAABBMinX() {
            return m_colDetect.GetAABBMinX();
        }

        /**
         * @brief Returns the max Y value for the bounding box
         * @return The max Y coordinate
         */
        GLfloat GetAABBMaxY() {
            return m_colDetect.GetAABBMaxY();
        }

        /**
         * @brief Returns the min Y value for the bounding box
         * @return The min Y coordinate
         */
        GLfloat GetAABBMinY() {
            return m_colDetect.GetAABBMinY();
        }

        /**
         * @brief Returns the max Z value for the bounding box
         * @return The max Z coordinate
         */
        GLfloat GetAABBMaxZ() {
            return m_colDetect.GetAABBMaxZ();
        }

        /**
         * @brief Returns the min Z value for the bounding box
         * @return The min Z coordinate
         */
        GLfloat GetAABBMinZ() {
            return m_colDetect.GetAABBMinZ();
        }

        auto FinishAABB() -> void;

        void Update(double dt);

        void DisplayMap(int screenWidth, int screenHeight, GLuint tempImage);
        void DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                  GLuint tempImage);
        void DisplayNoExit(int screenWidth, int screenHeight, GLuint tempImage);

        /// Camera starting position
        glm::vec3 position = {32720.0f, 9536.0f, 4800.0f};

        /// Previous camera position
        glm::vec3 lastPosition = position;

        /// Look coordinates of the camera
        glm::vec3 look = {};

        /// Camera tilt values
        glm::vec3 tilt = {0.0f, 1.0f, 0.0f};

        /// Camera angle values
        glm::vec2 angles = {glm::pi<float>() * 2, 0.0f};

        /// Mouse coordinates
        glm::vec2 mouse = {};

      private:
        GLfloat m_incrementX    = 0.0;
        GLfloat m_incrementZ    = 0.0;
        std::size_t m_No_Plains = 0;
        std::size_t m_plainNo   = 0;
        GLfloat m_plainHeight   = 0.0;

        // rotation variables
        GLfloat m_rotateAngleLR = 0.0;
        GLfloat m_deltaAngleLR  = 0.0;
        GLfloat m_rotateAngleUD = 0.0;
        GLfloat m_deltaAngleUD  = 0.0;

        GLfloat m_x = 0.0, m_y = 0.0, m_z = 0.0, m_zLast = 0.0, m_xLast = 0.0;
        GLfloat m_lookX = 0.0, m_lookY = 0.0, m_lookZ = 0.0;
        GLfloat m_lookXX = 0.0, m_lookYY = 0.0, m_lookZZ = 0.0;
        GLfloat m_deltaMoveLR = 0.0;
        GLfloat m_deltaMoveFB = 0.0;
        GLfloat m_deltaMoveUD = 0.0;
        GLfloat m_direction   = 0.0;

        // movement speed (step size)
        GLfloat m_rotateSpeed = 0.0;
        GLfloat m_moveSpeed   = 0.0;


        void UpdatePosition(double dt);
        void UpdateLook(double dt);
        void MoveIfOk(glm::vec3 newPos);

        void AdjustForPlane();

        // objects
        /// Camera collision object
        Collision m_colDetect{};

        /// Camera map object
        CameraMap m_map{};

        /// Camera plain values
        PlainLinkedList m_Plain{};

        // Privatised copy constructor and assignment operator
        Camera(const Camera &cam) = delete;
        Camera &operator=(const Camera &cam) = delete;
    };
}
