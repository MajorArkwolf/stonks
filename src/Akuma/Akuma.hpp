#pragma once

#include <cmath>

#include "Akuma/Floor.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"
#include "glm/vec3.hpp"

/**
 * @class Akuma
 * @brief The Akuma game state object
 */
class Akuma : public BaseState {
  public:
    Akuma();
    //~Akuma();
    auto display() -> void;
    auto softInit() -> void;
    auto hardInit() -> void;
    auto displayGrid() -> void;
    auto drawRectangle(float width, float height, bool wireframe) -> void;
    auto drawSquare(float size, bool wireframe) -> void;
    auto displayDebugMenu() -> void;
    auto unInit() -> void;
    auto handleInput(SDL_Event &event) -> void;
    static auto Akuma::get() -> Akuma &;

    int width                 = 0;
    int height                = 0;
    double ratio              = 0.0;
    glm::vec3 gridTranslation = {0, 0, -50.f};

    struct Camera {
        glm::dvec3 position = {0.f, 0.f, 0.f};
        glm::dvec3 look     = {0.f, 0.f, -1.f};
        glm::dvec3 up       = {0.f, 1.f, 0.f};
        auto Camera::getForwardDir() const -> glm::vec3 {
            return glm::vec3{std::sin(this->up.x), std::sin(this->up.y),
                             std::cos(this->up.x)};
        }
    } camera;

  private:
    Floor floor;
    /// Toggle for drawing 3d axis
    bool shouldDrawAxis = false;
    auto drawAxis(float x, float y, float z, float length) -> void;
};
