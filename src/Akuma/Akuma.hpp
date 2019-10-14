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
    ~Akuma() = default;
    auto display() -> void;
    auto softInit() -> void;
    auto hardInit() -> void;
    auto displayGrid() -> void;
    auto drawRectangle(float width, float height, bool wireframe) -> void;
    auto drawSquare(float size, bool wireframe) -> void;
    auto displayDebugMenu() -> void;
    auto unInit() -> void;
    auto handleInput(SDL_Event &event) -> void;
    void update(double dt);
    static auto get() -> Akuma &;

    glm::vec3 gridTranslation = {0, 0, -50.f};

    struct Camera {
        glm::dvec3 position = {0.f, 0.f, 0.f};
        glm::dvec3 look     = {0.f, 0.f, -1.f};
        glm::dvec3 up       = {0.f, 1.f, 0.f};
    } camera;

  private:
    Floor floor;
    /// Toggle for drawing 3d axis
    bool shouldDrawAxis = false;
    auto drawAxis(float x, float y, float z, float length) -> void;
};
