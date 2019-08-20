#include "Stonk/Engine.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>

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
    auto &engine     = Engine::get();
    auto &shaysWorld = ShaysWorld::get();

    auto time      = static_cast<double>(SDL_GetPerformanceCounter());
    auto oldTime   = 0.0;
    auto deltaTime = 0.0;

    while (engine.getIsRunning()) {
        oldTime = time;
        time    = static_cast<double>(SDL_GetPerformanceCounter());
        deltaTime =
            (time - oldTime) / static_cast<double>(SDL_GetPerformanceFrequency());

        engine.processInput();
        shaysWorld.Update(deltaTime);
        shaysWorld.Display();
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
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
#ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
#else
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif

    // Get display size.
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);

    // Create window.
    this->window = Engine::Window{
        SDL_CreateWindow("Shay's World", 0, 0, display.w, display.h,
                         SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL),
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

    // Enable Vsync.
    constexpr auto ENABLE_VSYNC = 1;
    SDL_GL_SetSwapInterval(ENABLE_VSYNC);

    // Capture the mouse.
    SDL_CaptureMouse(SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
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
    auto &shaysWorld = ShaysWorld::get();

    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE: {
            this->isRunning = false;
        } break;
        case SDL_SCANCODE_SPACE: {
            // Toggle for welcome screen
            shaysWorld.DisplayWelcome = (shaysWorld.DisplayWelcome) ? false : true;
        } break;
        default: break;
    }
}

auto Engine::handleKeyRelease(SDL_Event &event) -> void {
    switch (event.key.keysym.scancode) {
        default: break;
    }
}

auto Engine::handleMouseMovement(SDL_Event &event) -> void {
    this->mouse.x = event.motion.xrel;
    this->mouse.y = event.motion.yrel;
}

auto Engine::handleMouseButtonPress(SDL_Event &event) -> void {
    // int numClicks =
    //     event.button.clicks; // Number of clicks received as event   e.g. 1 =
    //                          // single click, 2 = double click
    // int releaseXPos = event.button.x; // X-position of mouse when pressed
    // int releaseYPos = event.button.y; // Y-position of mouse when pressed

    switch (event.button.button) {
        case SDL_BUTTON_LEFT: break;
        case SDL_BUTTON_RIGHT: break;
        case SDL_BUTTON_MIDDLE: break;
        default: break;
    }
}

auto Engine::handleMouseButtonRelease(SDL_Event &event) -> void {
    // int numClicks =
    //     event.button.clicks; // Number of clicks received as event   e.g. 1 =
    //                          // single click, 2 = double click
    // int releaseXPos = event.button.x; // X-position of mouse when pressed
    // int releaseYPos = event.button.y; // Y-position of mouse when pressed

    switch (event.button.button) {
        case SDL_BUTTON_LEFT: break;
        case SDL_BUTTON_RIGHT: break;
        case SDL_BUTTON_MIDDLE: break;
        default: break;
    }
}

auto Engine::handleMouseWheelMotion([[maybe_unused]] SDL_Event &event) -> void {
    // int amountScrolledX = event.wheel.x; // Amount scrolled left or right
    // int amountScrolledY = event.wheel.y; // Amount scrolled up or down
}

auto Engine::processInput() -> void {
    auto event        = SDL_Event{};
    auto handledMouse = false;

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
                handledMouse = true;
            } break;
            case SDL_MOUSEWHEEL: { // Mouse wheel scroll events
                this->handleMouseWheelMotion(event);
            } break;
            case SDL_QUIT: this->isRunning = false; break;
            default: break;
        }
    }

    if (!handledMouse) {
        this->mouse = {0.0f, 0.0f};
    }
}

auto Engine::update(State &newState, double dt) -> void {
    this->physics.update(newState, dt);
}

auto Engine::render([[maybe_unused]] const State &newState) const -> void {}
