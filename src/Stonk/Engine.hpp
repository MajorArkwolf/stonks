#pragma once

#include <memory>

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/Physics.hpp"
#include "Stonk/Player.hpp"

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

        static constexpr auto FPS_UPDATE_INTERVAL = 0.5;

        /* Mouse movement. */
        glm::vec2 mouse = {};

        /* SDL handles. */
        Window window   = nullptr;
        Context context = nullptr;

        /* Game state. */
        State state = {};

        /********************************************
         * \brief The current gamemode, will eventually be used to determine where to send SDL2 events
         ***********************************************/
        GameMode gameMode = GameMode::SHAY;

        /* Subsystems. */
        // Camera camera       = {};
        // Collision collision = {};
        Physics physics = {};

        /********************************************
         * \brief The current FPS
         ***********************************************/
        double fps = 0.0;

        /********************************************
         * \brief Boolean to tell whether to display the debug menu
         ***********************************************/
        bool showDebugMenu = false;

      private:
        /********************************************
         * \brief A boolean signifying whether the game engine is running or not
         ***********************************************/
        bool isRunning = true;

        auto getTime() const -> double;

        Engine();

      public:
        Engine(Engine &&)      = default;
        Engine(const Engine &) = delete;
        ~Engine();

        static auto get() -> Engine &;
        static auto run() -> void;

        /********************************************
         * \brief Overloaded assignment operator
         ***********************************************/
        auto operator=(Engine &&) -> Engine & = default;

        /********************************************
         * \brief Overloaded const assignment operator
         ***********************************************/
        auto operator=(const Engine &) -> Engine & = delete;

        /********************************************
         * \brief Handles SDL2 events regarding mouse movement, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleMouseMovement(SDL_Event &event) -> void;

        /********************************************
         * \brief Handles SDL2 events regarding mouse button presses, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleMouseButtonPress(SDL_Event &event) -> void;

        /********************************************
         * \brief Handles SDL2 events regarding mouse button releases, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleMouseButtonRelease(SDL_Event &event) -> void;

        /********************************************
         * \brief Handles SDL2 events regarding mouse wheel motion, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleMouseWheelMotion(SDL_Event &event) -> void;

        /********************************************
         * \brief Handles SDL2 events regarding keyboard key presses, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleKeyPress(SDL_Event &event) -> void;

        /********************************************
         * \brief Handles SDL2 events regarding keyboard key releases, works by sending
         * the events to the currently set game state
         * \param event The SDL2 event being read from
         ***********************************************/
        auto handleKeyRelease(SDL_Event &event) -> void;

        /********************************************
         * \brief Checks to see if the engine is currently running
         * \return A boolean, returns true if the engine is running
         ***********************************************/
        auto getIsRunning() const -> bool;

        /********************************************
         * \brief Parses all SDL2 events and sends them to the correct function
         * to process them based on their event type
         ***********************************************/
        auto processInput() -> void;

        /********************************************
         * \brief I DONT KNOW WHAT THIS DOES
         * \param newState
         * \param dt
         ***********************************************/
        auto update(State &newState, double dt) -> void;

        /********************************************
         * \brief I DONT KNOW WHAT THIS DOES
         * \param newState
         ***********************************************/
        auto render(const State &newState) const -> void;
    };
}
