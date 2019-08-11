#include "Stonk/Stonk.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <string>

#include "OpenGl.hpp"
#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"

// TODO: REMOVE
#include "Main.hpp"

using std::runtime_error;
using std::string;

auto shayHack() -> void {
    auto width  = 800;
    auto height = 500;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, static_cast<double>(width) / static_cast<double>(height),
                   1, 250000);
    glMatrixMode(GL_MODELVIEW);
}

auto Stonk::run() -> void {
    auto &stonk = Stonk::get();

    // Setup Shay's world.
    myinit();
    shayHack();

    auto t  = 0.0;
    auto dt = 0.01;

    auto currentTime = static_cast<double>(SDL_GetPerformanceFrequency());
    auto accumulator = 0.0;

    auto previousState = State{};
    auto currentState  = State{};

    while (stonk.getIsRunning()) {
        auto newTime   = static_cast<double>(SDL_GetPerformanceFrequency());
        auto frameTime = newTime - currentTime;

        if (frameTime > 0.25) {
            frameTime = 0.25;
        }

        currentTime = newTime;
        accumulator += frameTime;

        stonk.processInput();

        while (accumulator >= dt) {
            previousState = currentState;
            stonk.update(currentState, dt);
            t += dt;
            accumulator -= dt;
        }

        const auto alpha = accumulator / dt;

        auto interpolatedState =
            currentState * alpha + previousState * (1.0 - alpha);

        stonk.render(interpolatedState);
    }
}

Stonk::Stonk() {
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
    // SDL_GL_SetSwapInterval(1);

    // Create window.
    this->window =
        Stonk::Window{SDL_CreateWindow("Shay's World", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 800, 500,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
                      &SDL_DestroyWindow};

    if (this->window.get() == nullptr) {
        throw runtime_error{string{"Unable to create window: "} + SDL_GetError()};
    }

    // Create OpenGL context.
    this->context = Stonk::Context{SDL_GL_CreateContext(this->window.get()),
                                   &SDL_GL_DeleteContext};

    if (this->context.get() == nullptr) {
        throw runtime_error{string{"Unable to create OpenGL context: "} +
                            SDL_GetError()};
    }
}

Stonk::~Stonk() {
    SDL_Quit();
}

auto Stonk::get() -> Stonk & {
    static auto instance = Stonk{};

    return instance;
}

auto Stonk::getIsRunning() const -> bool {
    return this->isRunning;
}
auto Stonk::handleKeyPress(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_KeyboardEvent
    switch (event.key.keysym.scancode) { // Use SDL Scancodes that correspond to keyboard keys
        case SDL_SCANCODE_ESCAPE: {
            this->isRunning = false;
        } break;
        case SDL_SCANCODE_SPACE: {
            // DisplayWelcome = (DisplayWelcome == 1) ? 0 : 1; // Ternary operator toggle for welcome screen
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

auto Stonk::handleKeyRelease(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_KeyboardEvent
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

auto Stonk::handleMouseMovement(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_MouseMotionEvent
    int mouseXPos     = event.motion.x;
    int mouseYPos     = event.motion.y;
    int relativeXMove = event.motion.xrel;
    int relativeYMove = event.motion.yrel;
}
auto Stonk::handleMouseButtonPress(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_MouseButtonEvent
    int numClicks =
        event.button.clicks; // Number of clicks received as event   e.g. 1 = single click, 2 = double click
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
auto Stonk::handleMouseButtonRelease(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_MouseButtonEvent
    int numClicks =
        event.button.clicks; // Number of clicks received as event   e.g. 1 = single click, 2 = double click
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
auto Stonk::handleMouseWheelMotion(SDL_Event &event) -> void {
    // https://wiki.libsdl.org/SDL_MouseWheelEvent
    int amountScrolledX = event.wheel.x; // Amount scrolled left or right
    int amountScrolledY = event.wheel.y; // Amount scrolled up or down
}

auto Stonk::processInput() -> void {
    // https://wiki.libsdl.org/SDL_Event
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

auto Stonk::update(State &state, double dt) -> void {
    this->physics.update(state, dt);
}

auto Stonk::render(const State &state) const -> void {
    Display();
    SDL_GL_SwapWindow(this->window.get());
}
