#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/Physics.hpp"
#include "Stonk/Player.hpp"
#include "Akuma/Akuma.hpp"
/**
 * @namespace Stonk
 * @brief The global Stonk namespace
 */
namespace Stonk {
    enum class GameMode { SHAY, STONK, MENU };
    /**
     * @brief Stonk game engine.
     *
     * At least it's not Shay's World.
     */
    class Engine {
      public:
        using Window  = std::shared_ptr<SDL_Window>;
        using Context = std::shared_ptr<void>;
        glm::vec2 size     = {40, 40};


        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* SDL handles. */
        Window window   = nullptr;
        Context context = nullptr;

        /* Game state. */
        State state = {};

        /**
         * @brief The current gamemode, will eventually be used to determine where to send SDL2 events
         */
        GameMode gameMode = GameMode::SHAY;

        /* Subsystems. */
        // Camera camera       = {};
        // Collision collision = {};
        Physics physics = {};

        /**
         * @brief The current FPS
         */
        double fps = 0.0;

        /**
         * @brief Boolean to tell whether to display the debug menu
         */
        bool showDebugMenu = false;

      private:
        /**
         * @brief A boolean signifying whether the game engine is running or not
         */
        bool isRunning = true;

        auto getTime() const -> double;

        Engine();

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        static auto get() -> Engine &;
        static auto run() -> void;

        /**
         * @brief Overloaded assignment operator, set to default overload
         */
        auto operator=(Engine &&) -> Engine & = default;

        /**
         * @brief Overloaded const assignment operator, set to delete overload
         */
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
}
