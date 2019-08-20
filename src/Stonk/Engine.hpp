#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/Physics.hpp"
#include "Stonk/Player.hpp"

namespace Stonk {
    /**
     * @brief Stonk game engine.
     *
     * At least it's not Shay's World.
     */
    class Engine {
      public:
        using Window  = std::shared_ptr<SDL_Window>;
        using Context = std::shared_ptr<void>;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* SDL handles. */
        Window window   = nullptr;
        Context context = nullptr;

        /* Game state. */
        State state = {};

        /* Subsystems. */
        // Camera camera       = {};
        // Collision collision = {};
        Physics physics = {};

      private:
        bool isRunning = true;

        Engine();

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        static auto get() -> Engine &;
        static auto run() -> void;

        auto operator=(Engine &&) -> Engine & = default;
        auto operator=(const Engine &) -> Engine & = delete;

        auto handleMouseMovement(SDL_Event &event) -> void;
        auto handleMouseButtonPress(SDL_Event &event) -> void;
        auto handleMouseButtonRelease(SDL_Event &event) -> void;
        auto handleMouseWheelMotion(SDL_Event &event) -> void;
        auto handleKeyPress(SDL_Event &event) -> void;
        auto handleKeyRelease(SDL_Event &event) -> void;
        auto getIsRunning() const -> bool;
        auto processInput() -> void;
        auto update(State &newState, double dt) -> void;
        auto render(const State &newState) const -> void;
    };
};
