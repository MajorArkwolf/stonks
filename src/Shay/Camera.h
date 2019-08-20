#pragma once

#include <cstddef>

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "CameraMap.h"
#include "Collision.h"
#include "PlainLinkedList.h"
#include "PlainNode.h"

//  camera.h
//  Header file for the camera class
//	Allows the camera to be navigated around the world.
//	Also sets Plains, Bounding Boxes and view Maps
//
//  Shay Leary, March 2005

namespace Shay {
    class Camera {
      public:
        static constexpr GLfloat MOVEMENT_SPEED = 2000.0f;
        static constexpr GLfloat LOOK_SPEED     = 0.005f;

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
        GLfloat GetLR() {
            return this->position.x;
        }
        GLfloat GetUD() {
            return this->position.y;
        }
        GLfloat GetFB() {
            return this->position.z;
        }
        GLfloat GetAABBMaxX() {
            return m_colDetect.GetAABBMaxX();
        }
        GLfloat GetAABBMinX() {
            return m_colDetect.GetAABBMinX();
        }
        GLfloat GetAABBMaxY() {
            return m_colDetect.GetAABBMaxY();
        }
        GLfloat GetAABBMinY() {
            return m_colDetect.GetAABBMinY();
        }
        GLfloat GetAABBMaxZ() {
            return m_colDetect.GetAABBMaxZ();
        }
        GLfloat GetAABBMinZ() {
            return m_colDetect.GetAABBMinZ();
        }
        auto FinishAABB() -> void;

        void Update(double dt);

        void DisplayMap(int screenWidth, int screenHeight, GLuint tempImage);
        void DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                  int tempExit, GLuint tempImage);
        void DisplayNoExit(int screenWidth, int screenHeight, GLuint tempImage);

      private:
        // steep incline increments
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

        // movement variables
        glm::vec3 position     = {32720.0f, 9536.0f, 4800.0f};
        glm::vec3 lastPosition = position;
        glm::vec3 look         = {};
        glm::vec3 tilt         = {0.0f, 1.0f, 0.0f};
        glm::vec2 angles       = {glm::pi<float>() * 2, 0.0f};
        glm::vec2 mouse        = {};

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
        Collision m_colDetect{};
        CameraMap m_map{};
        PlainLinkedList m_Plain{};

        // These functions were set up to climb stairs, but are not used.
        // The Plain object is used instead
        void ClimbSteps(GLfloat stepStart, GLfloat stepFinish,
                        GLfloat stepHeight, GLfloat stepWidth, int noSteps);
        void CheckSteps();

        // Privatised copy constructor and assignment operator
        Camera(const Camera &cam) = delete;
        Camera &operator=(const Camera &cam) = delete;
    };
};
