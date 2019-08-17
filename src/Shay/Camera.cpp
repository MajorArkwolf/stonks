#include "Camera.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shay/Shay.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"

using glm::vec2;
using glm::vec3;
using Shay::Camera;
constexpr auto PI = glm::pi<float>();

//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Camera::Camera() {
    m_rotateSpeed = 0.0f;
    m_moveSpeed   = 0.0f;

    ResetXYZ();

    m_deltaMoveFB = 0.0f;
    m_deltaMoveLR = 0.0f;
    m_deltaMoveUD = 0.0f;

    m_rotateAngleLR = 0.0f;
    m_rotateAngleUD = 0.0f;
    m_deltaAngleLR  = 0.0f;
    m_deltaAngleUD  = 0.0f;

    m_CollisionDetectionOn = true;
}

//--------------------------------------------------------------------------------------
// Reset camera values
//--------------------------------------------------------------------------------------
void Camera::ResetXYZ() {}

//----------------------------------------------------------------------------------------
//  Places camera at the correct level on the current plain
//----------------------------------------------------------------------------------------
void Camera::SetPlains(int moveX, int moveZ) {
    // store number of plains (stops from looping through linked list each time)
    if (m_No_Plains == 0)
        m_No_Plains = m_Plain.GetListSize();

    for (int i = 0; i < m_No_Plains; i++) {
        // if camera is positioned on a plain
        if ((position.z <= m_Plain.GetZend(i)) &&
            (position.z >= m_Plain.GetZstart(i)) &&
            (position.x <= m_Plain.GetXend(i)) &&
            (position.x >= m_Plain.GetXstart(i))) {
            // if flat plain
            if (m_Plain.GetType(i) == 0) {
                position.y = m_Plain.GetYstart(i);

                m_plainNo     = i;
                m_plainHeight = m_Plain.GetYstart(i);
            }
            // if plain slopes in z direction
            if (m_Plain.GetType(i) == 2) {
                // if plain slopes up or down
                if (lastPosition.z > position.z) {
                    m_incrementZ = ((position.y - m_Plain.GetYstart(i)) /
                                    (position.z - m_Plain.GetZstart(i)));
                } else {
                    m_incrementZ = ((m_Plain.GetYend(i) - position.y) /
                                    (m_Plain.GetZend(i) - position.z));
                }
                position.y += (m_incrementZ * moveZ);
            }
            // if plain slopes in x direction
            if (m_Plain.GetType(i) == 1) {
                // if plain slopes up or down
                if (lastPosition.x > position.x) {
                    m_incrementX = ((position.y - m_Plain.GetYstart(i)) /
                                    (position.x - m_Plain.GetXstart(i)));
                } else {
                    m_incrementX = ((m_Plain.GetYend(i) - position.y) /
                                    (m_Plain.GetXend(i) - position.x));
                }

                position.y += (m_incrementX * moveX);
            }
        }
    }
}

void Camera::Position(GLfloat const &tempX, GLfloat const &tempY,
                      GLfloat const &tempZ, GLfloat const &tempAngle) {
    ResetXYZ();

    position.x = tempX;
    position.y = tempY;
    position.z = tempZ;

    // rotate to correct angle
    m_rotateAngleLR = tempAngle * (PI / 180.0f);
    m_lookX         = sin(m_rotateAngleLR);
    m_lookZ         = -cos(m_rotateAngleLR);
    m_lookXX        = sin(m_rotateAngleLR + PI / 2.0f);
    m_lookZZ        = -cos(m_rotateAngleLR + PI / 2.0f);
    m_rotateAngleUD = 0.0;
    m_deltaAngleUD  = 0.0;
}

void Camera::UpdateLook(double dt) {
    // The vertical look limit, to prevent looking completely up or down.
    constexpr auto VERTICAL_LIMIT = (PI / 2.0f) - 0.03f;

    auto &engine = Stonk::Engine::get();

    this->mouse = engine.mouse;

    this->angles.x += -this->mouse.x * LOOK_SPEED;
    this->angles.y += -this->mouse.y * LOOK_SPEED;

    // Wrap the view angles on the x axis.
    if (this->angles.x < -PI) {
        this->angles.x += PI * 2.0f;
    } else if (this->angles.x > PI) {
        this->angles.x -= PI * 2.0f;
    }

    // Wrap the view angles on the y axis.
    if (this->angles.y < -PI / 2.0f) {
        this->angles.y = -PI / 2.0f;
    } else if (this->angles.y > PI / 2.0f) {
        this->angles.y = PI / 2.0f;
    }

    // Prevent the y angles from exceeding the vertical limit.
    this->angles.y = std::clamp(this->angles.y, -VERTICAL_LIMIT, VERTICAL_LIMIT);

    // Calculate the new look position from the view angles.
    this->look.x = std::sin(this->angles.x) * std::cos(this->angles.y);
    this->look.y = std::sin(this->angles.y);
    this->look.z = std::cos(this->angles.x) * std::cos(this->angles.y);
    this->look += this->position;
}

void Camera::UpdatePosition(double dt) {
    auto *keys = SDL_GetKeyboardState(nullptr);

    this->lastPosition = position;

    auto fdt = static_cast<float>(dt);
    auto forwardDir =
        vec3{std::sin(this->angles.x), 0.0, std::cos(this->angles.x)};
    auto rightDir = vec3{-forwardDir.z, 0.0, forwardDir.x};

    if (keys[SDL_SCANCODE_W]) {
        auto newPos = this->position + (forwardDir * MOVEMENT_SPEED * fdt);
        MoveIfOk(newPos);
    }

    if (keys[SDL_SCANCODE_A]) {
        auto newPos = this->position - (rightDir * MOVEMENT_SPEED * fdt);
        MoveIfOk(newPos);
    }

    if (keys[SDL_SCANCODE_S]) {
        auto newPos = this->position - (forwardDir * MOVEMENT_SPEED * fdt);
        MoveIfOk(newPos);
    }

    if (keys[SDL_SCANCODE_D]) {
        auto newPos = this->position + (rightDir * MOVEMENT_SPEED * fdt);
        MoveIfOk(newPos);
    }

    this->look.x = std::sin(this->angles.x) * std::cos(this->angles.y);
    this->look.y = std::sin(this->angles.y);
    this->look.z = std::cos(this->angles.x) * std::cos(this->angles.y);
    this->look += this->position;
}

void Camera::Update(double dt) {
    this->UpdatePosition(dt);
    SetPlains(static_cast<int>(MOVEMENT_SPEED * static_cast<float>(dt)),
              static_cast<int>(MOVEMENT_SPEED * static_cast<float>(dt)));
    this->UpdateLook(dt);

    glLoadIdentity();
    gluLookAt(static_cast<double>(this->position.x), //
              static_cast<double>(this->position.y), //
              static_cast<double>(this->position.z), //
              static_cast<double>(this->look.x),     //
              static_cast<double>(this->look.y),     //
              static_cast<double>(this->look.z),     //
              static_cast<double>(this->tilt.x),     //
              static_cast<double>(this->tilt.y),     //
              static_cast<double>(this->tilt.z));    //
}

void Camera::MoveIfOk(glm::vec3 newPos) {
    if (!(m_colDetect.Collide(newPos.x, newPos.y, newPos.z))) {
        this->position = newPos;
    }
}

//--------------------------------------------------------------------------------------
// Display map of world
//----------------------------------------------------------------------------------------

void Camera::DisplayMap(const int &screenWidth, const int &screenHeight,
                        const GLuint &tempImage) {
    m_map.DisplayMap(screenWidth, screenHeight, GetLR(), GetFB(), tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayWelcomeScreen(const int &screenWidth, const int &screenHeight,
                                  const int &tempExit, const GLuint &tempImage) {
    m_map.DisplayWelcomeScreen(screenWidth, screenHeight, tempExit, tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayNoExit(const int &screenWidth, const int &screenHeight,
                           const GLuint &tempImage) {
    m_map.DisplayNoExit(screenWidth, screenHeight, tempImage);
}

//----------------------------------------------------------------------------------------

void Camera::SetWorldCoordinates(const GLfloat &tempX, const GLfloat &tempZ) {
    m_colDetect.SetWorldX(tempX);
    m_colDetect.SetWorldZ(tempZ);
}

//----------------------------------------------------------------------------------------

void Camera::SetPlains(const int tempType, const GLfloat tempXs,
                       const GLfloat tempXe, const GLfloat tempYs,
                       const GLfloat tempYe, const GLfloat tempZs,
                       const GLfloat tempZe) {
    m_Plain.AddToStart(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
}
