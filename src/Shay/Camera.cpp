#include "Camera.h"

#include <algorithm>
#include <cmath>
#include <cstddef>

#include <SDL2/SDL.h>
#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Shay/PlainNode.h"
#include "Shay/Shay.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"

using glm::vec2;
using glm::vec3;
using Shay::Camera;
using std::size_t;

using Shay::PlainNode;
using Slope = PlainNode::Slope;

constexpr auto PI = glm::pi<float>();

Camera::Camera() {
    MOVEMENT_SPEED = 2000.0f;
}
/**
 * @brief Adjust the Y axis of the camera correctly for the plane it is current on.
 */
void Camera::AdjustForPlane() {
    // store number of plains (stops from looping through linked list each time)
    if (m_No_Plains == 0)
        m_No_Plains = m_Plain.GetListSize();

    for (size_t i = 0; i < m_No_Plains; i++) {
        // if camera is positioned on a plain
        if ((position.z <= m_Plain.GetZend(i)) &&
            (position.z >= m_Plain.GetZstart(i)) &&
            (position.x <= m_Plain.GetXend(i)) &&
            (position.x >= m_Plain.GetXstart(i))) {
            if (m_Plain.GetType(i) == Slope::FLAT) {
                position.y = m_Plain.GetYstart(i);

                m_plainNo     = i;
                m_plainHeight = m_Plain.GetYstart(i);
            }
            if (m_Plain.GetType(i) == Slope::ZY) {
                auto height = std::abs(m_Plain.GetYstart(i) - m_Plain.GetYend(i));
                auto length = std::abs(m_Plain.GetZstart(i) - m_Plain.GetZend(i));
                auto ratio =
                    std::abs(this->position.z - m_Plain.GetZend(i)) / length;

                if (m_Plain.GetYstart(i) > m_Plain.GetYend(i)) {
                    position.y = m_Plain.GetYend(i) + (ratio * height);
                } else {
                    position.y = m_Plain.GetYend(i) - (ratio * height);
                }
            }
            if (m_Plain.GetType(i) == Slope::XY) {
                auto height = std::abs(m_Plain.GetYstart(i) - m_Plain.GetYend(i));
                auto length = std::abs(m_Plain.GetXstart(i) - m_Plain.GetXend(i));
                auto ratio =
                    std::abs(this->position.x - m_Plain.GetXend(i)) / length;

                if (m_Plain.GetYstart(i) > m_Plain.GetYend(i)) {
                    position.y = m_Plain.GetYend(i) + (ratio * height);
                } else {
                    position.y = m_Plain.GetYend(i) - (ratio * height);
                }
            }
        }
    }
}

/**
 * @brief Updates the camera look point.
 *
 * @param dt The elapsed delta time since last frame.
 */
void Camera::UpdateLook([[maybe_unused]] double dt) {
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

/**
 * @brief Updates the camera position.
 *
 * @param dt The elapsed delta time since last frame.
 */
void Camera::UpdatePosition(double dt) {
    auto *keys       = SDL_GetKeyboardState(nullptr);

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

/**
 * @brief Updates the camera.
 *
 * @param dt The elapsed delta time since last frame.
 */
void Camera::Update(double dt) {
    this->UpdatePosition(dt);
    this->AdjustForPlane();
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

void Camera::DisplayMap(int screenWidth, int screenHeight, GLuint tempImage) {
    m_map.DisplayMap(screenWidth, screenHeight, GetLR(), GetFB(), tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayWelcomeScreen(int screenWidth, int screenHeight,
                                  int tempExit, GLuint tempImage) {
    m_map.DisplayWelcomeScreen(screenWidth, screenHeight, tempExit, tempImage);
}

//--------------------------------------------------------------------------------------
// Display welcome or exit page
//----------------------------------------------------------------------------------------

void Camera::DisplayNoExit(int screenWidth, int screenHeight, GLuint tempImage) {
    m_map.DisplayNoExit(screenWidth, screenHeight, tempImage);
}

//----------------------------------------------------------------------------------------

void Camera::SetWorldCoordinates(GLfloat tempX, GLfloat tempZ) {
    m_colDetect.SetWorldX(tempX);
    m_colDetect.SetWorldZ(tempZ);
}

//----------------------------------------------------------------------------------------

void Camera::SetPlains(Slope tempType, GLfloat tempXs, GLfloat tempXe,
                       GLfloat tempYs, GLfloat tempYe, GLfloat tempZs,
                       GLfloat tempZe) {
    m_Plain.AddToStart(tempType, tempXs, tempXe, tempYs, tempYe, tempZs, tempZe);
}

auto Camera::FinishAABB() -> void {
    m_colDetect.FinishAABB();
}
