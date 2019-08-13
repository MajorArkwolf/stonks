#include "Stonk/Engine.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Shay/Shay.hpp"
#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"
#include "Stonk/OpenGl.hpp"

using Shay::ShaysWorld;
using std::runtime_error;
using std::string;
using Stonk::Engine;
using Stonk::State;

auto Engine::run() -> void {
    auto &engine = Engine::get();

    // Setup Shay's world.
    ShaysWorld::Init();

    auto t  = 0.0;
    auto dt = 0.01;

    auto currentTime = static_cast<double>(SDL_GetPerformanceFrequency());
    auto accumulator = 0.0;

    auto previousState = State{};
    auto currentState  = State{};

    while (engine.getIsRunning()) {
        auto newTime   = static_cast<double>(SDL_GetPerformanceFrequency());
        auto frameTime = newTime - currentTime;

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        currentTime = newTime;
        accumulator += frameTime;

        engine.processInput();

        while (accumulator >= dt) {
            previousState = currentState;
            engine.update(currentState, dt);
            t += dt;
            accumulator -= dt;
        }

        const auto alpha = accumulator / dt;

        auto interpolatedState =
            currentState * alpha + previousState * (1.0 - alpha);

        engine.render(interpolatedState);
    }
}

Engine::Engine() {
    // Start SDL.
    auto status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (status != 0) {
        throw runtime_error{string{"Unable to initialize SDL: "} + SDL_GetError()};
    }

    // Set OpenGL settings.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Enable Vsync.
    constexpr auto ENABLE_VSYNC = 1;
    SDL_GL_SetSwapInterval(ENABLE_VSYNC);

    // Create window.
    this->window =
        Engine::Window{SDL_CreateWindow("Shay's World", SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, 1280, 720,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
                       &SDL_DestroyWindow};

    if (this->window.get() == nullptr) {
        throw runtime_error{string{"Unable to create window: "} + SDL_GetError()};
    }

    // Create OpenGL context.
    this->context = Engine::Context{SDL_GL_CreateContext(this->window.get()),
                                    &SDL_GL_DeleteContext};

    if (this->context.get() == nullptr) {
        throw runtime_error{string{"Unable to create OpenGL context: "} +
                            SDL_GetError()};
    }
}

Engine::~Engine() {
    SDL_Quit();
}

auto Engine::get() -> Engine & {
    static auto instance = Engine{};

    return instance;
}

auto Engine::getIsRunning() const -> bool {
    return this->isRunning;
}

auto Engine::handleKeyPress(SDL_Event &event) -> void {
    switch (event.key.keysym.scancode) { // Use SDL Scancodes that correspond to keyboard keys
        case SDL_SCANCODE_ESCAPE: {
            this->isRunning = false;
        } break;
        case SDL_SCANCODE_SPACE: {
            ShaysWorld::DisplayWelcome = (ShaysWorld::DisplayWelcome == 1) ? 0 : 1;
            // Toggle for welcome screen
        } break;
        case SDL_SCANCODE_W: {

        } break;
        case SDL_SCANCODE_A: {

        } break;
        case SDL_SCANCODE_S: {

        } break;
        case SDL_SCANCODE_D: {

        } break;
    }
}

auto Engine::handleKeyRelease(SDL_Event &event) -> void {
    switch (event.key.keysym.scancode) { // Use SDL Scancodes that correspond to keyboard keys
        case SDL_SCANCODE_W: {

        } break;
        case SDL_SCANCODE_A: {

        } break;
        case SDL_SCANCODE_S: {

        } break;
        case SDL_SCANCODE_D: {

        } break;
    }
}

auto Engine::handleMouseMovement(SDL_Event &event) -> void {
    int mouseXPos     = event.motion.x;
    int mouseYPos     = event.motion.y;
    int relativeXMove = event.motion.xrel;
    int relativeYMove = event.motion.yrel;
}

auto Engine::handleMouseButtonPress(SDL_Event &event) -> void {
    int numClicks =
        event.button.clicks; // Number of clicks received as event   e.g. 1 =
                             // single click, 2 = double click
    int releaseXPos = event.button.x; // X-position of mouse when pressed
    int releaseYPos = event.button.y; // Y-position of mouse when pressed

    switch (event.button.button) {
        case SDL_BUTTON_LEFT: { // Left mouse button

        } break;
        case SDL_BUTTON_RIGHT: { // Right mouse button

        } break;
        case SDL_BUTTON_MIDDLE: { // Middle mouse button

        } break;
    }
}

auto Engine::handleMouseButtonRelease(SDL_Event &event) -> void {
    int numClicks =
        event.button.clicks; // Number of clicks received as event   e.g. 1 =
                             // single click, 2 = double click
    int releaseXPos = event.button.x; // X-position of mouse when pressed
    int releaseYPos = event.button.y; // Y-position of mouse when pressed

    switch (event.button.button) {
        case SDL_BUTTON_LEFT: { // Left mouse button

        } break;
        case SDL_BUTTON_RIGHT: { // Right mouse button

        } break;
        case SDL_BUTTON_MIDDLE: { // Middle mouse button

        } break;
    }
}

auto Engine::handleMouseWheelMotion(SDL_Event &event) -> void {
    int amountScrolledX = event.wheel.x; // Amount scrolled left or right
    int amountScrolledY = event.wheel.y; // Amount scrolled up or down
}

auto Engine::processInput() -> void {
    auto event = SDL_Event{};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: { // Key press events
                this->handleKeyPress(event);
            } break;
            case SDL_KEYUP: { // Key Release Events
                this->handleKeyRelease(event);
            } break;
            case SDL_MOUSEBUTTONDOWN: { // Mouse button press events
                this->handleMouseButtonPress(event);
            } break;
            case SDL_MOUSEBUTTONUP: { // Mouse button release events
                this->handleMouseButtonRelease(event);
            } break;
            case SDL_MOUSEMOTION: { // Mouse movement events
                this->handleMouseMovement(event);
            } break;
            case SDL_MOUSEWHEEL: { // Mouse wheel scroll events
                this->handleMouseWheelMotion(event);
            } break;
            case SDL_QUIT: this->isRunning = false; break;
            default: break;
        }
    }
}

auto Engine::update(State &state, double dt) -> void {
    this->physics.update(state, dt);
}

auto Engine::render(const State &state) const -> void {
    ShaysWorld::Display();
    SDL_GL_SwapWindow(this->window.get());
}
