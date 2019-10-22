#pragma once

#include <memory>
#include <stack>
#include <string>

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "Akuma/Akuma.hpp"
#include "Stonk/Audio.hpp"
#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/Physics.hpp"
#include "Stonk/Player.hpp"

/**
 * @namespace Stonk
 * @brief The global Stonk namespace
 */
namespace Stonk {
    enum class GameMode { SHAY, AKUMA, MENU };
    /**
     * @class Engine
     * @brief Stonk game engine.
     *
     * At least it's not Shay's World.
     */
    class Engine {
      public:
        using Window  = std::shared_ptr<SDL_Window>;
        using Context = std::shared_ptr<void>;

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
        Audio audio     = {};

        /**
         * @brief The current FPS
         */
        double fps = 0.0;

        /**
         * @brief Boolean to tell whether to display the debug menu
         */
        bool showDebugMenu = false;

        /**
         * @brief A boolean signifying whether the game engine is running or not
         */
        bool isRunning = true;

        std::string basepath = "";

      private:
        auto getTime() const -> double;
        auto getBasePath() -> void;

        Engine();

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        static auto get() -> Engine &;
        auto Audio() -> Stonk::Audio &;
        static auto run() -> void;

        auto loadState(GameMode) -> void;

        std::stack<BaseState *> daGameStateStack;

        auto purgeStack() -> void;
        auto checkStack() -> void;
        auto popStack() -> void;
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
