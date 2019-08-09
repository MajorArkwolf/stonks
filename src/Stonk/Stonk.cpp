#include "Stonk/Stonk.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_Opengl.h>
#include <iostream>
#include <stdexcept>
#include <string>

// TODO: REMOVE
#include "Gl.hpp"
#include "Main.hpp"
#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"

using std::runtime_error;
using std::string;

auto shayHack() -> void {
    auto width  = 1280;
    auto height = 720;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glViewport(0, 0, width, height);
    gluPerspective(45, static_cast<double>(width) / static_cast<double>(height),
                   1, 250000);
    glMatrixMode(GL_MODELVIEW);
}

auto Stonk::run() -> void {
    auto &stonk = Stonk::get();

    // Setup Shay's world.
    shayHack();
    myinit();

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

    // Set OpenGL attributes.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable Vsync.
    SDL_GL_SetSwapInterval(1);

    // Create window.
    this->window =
        Stonk::Window{SDL_CreateWindow("Shay's World", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 1280, 720,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
                      &SDL_DestroyWindow};

    if (this->window.get() == nullptr) {
        throw runtime_error{string{"Unable to create window: "} + SDL_GetError()};
    }

    // Create OpenGL context.
    this->gl = Stonk::Gl{SDL_GL_CreateContext(this->window.get()),
                         &SDL_GL_DeleteContext};

    if (this->gl.get() == nullptr) {
        throw runtime_error{string{"Unable to create OpenGL context: "} +
                            SDL_GetError()};
    }

    // Set the current OpenGL context.
    SDL_GL_MakeCurrent(this->window.get(), this->gl.get());
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
    switch (event.key.keysym.scancode) {
            // Use SDL Scancodes that correspond to keyboard keys
        case SDL_SCANCODE_RETURN: {
            printf("'Enter' key pressed\n");
        } break;
    }
}

auto Stonk::handleKeyRelease(SDL_Event &event) -> void {
    switch (event.key.keysym.scancode) {
            // Use SDL Scancodes that correspond to keyboard keys
        case SDL_SCANCODE_RETURN: {
            printf("'Enter' key released\n");
        } break;
    }
}

auto Stonk::processInput() -> void {
    auto event = SDL_Event{};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: { // Key press events
                handleKeyPress(event);
            } break;
            case SDL_KEYUP: { // Key Release Events
                handleKeyRelease(event);
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
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    SDL_GL_SwapWindow(this->window.get());
}
