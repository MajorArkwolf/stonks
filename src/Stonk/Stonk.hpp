#pragma once

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>
#include <memory>

#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/Physics.hpp"
#include "Stonk/Player.hpp"

/**
 * @brief Stonk game engine.
 *
 * At least it's not Shay's World.
 */
class Stonk {
  public:
    using Window = std::shared_ptr<SDL_Window>;
    using Gl     = std::shared_ptr<void>;

    /* SDL handles. */
    Window window = nullptr;
    Gl gl         = nullptr;

    /* Game state. */
    State state = {};

    /* Subsystems. */
    // Camera camera       = {};
    // Collision collision = {};
    Physics physics = {};

  private:
    bool isRunning = true;

    Stonk();

  public:
    Stonk(Stonk &&)      = default;
    Stonk(const Stonk &) = delete;
    ~Stonk();

    static auto get() -> Stonk &;
    static auto run() -> void;

    auto operator=(Stonk &&) -> Stonk & = default;
    auto operator=(const Stonk &) -> Stonk & = delete;

	static auto handleKeyboardEvent() -> void;
    auto getIsRunning() const -> bool;
    auto processInput() -> void;
    auto update(State &state, double dt) -> void;
    auto render(const State &state) const -> void;
};
