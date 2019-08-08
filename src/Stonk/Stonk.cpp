#include "Stonk/Stonk.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>
#include <string>

// TODO: REMOVE
#include "Main.hpp"
#include "Stonk/Camera.hpp"
#include "Stonk/Collision.hpp"

using std::runtime_error;
using std::string;

Stonk::Stonk() {
    // Start SDL.
    auto status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (status != 0) {
        throw runtime_error{string{"Unable to initialize SDL: "} + SDL_GetError()};
    }

    // Create window.
    this->window =
        Stonk::Window{SDL_CreateWindow("Shay's World", SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, 1280, 720,
                                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
                      &SDL_DestroyWindow};

    if (this->window.get() == nullptr) {
        throw runtime_error{string{"Unable to create window: "} + SDL_GetError()};
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create OpenGL context.
    this->gl = Stonk::Gl{SDL_GL_CreateContext(this->window.get()),
                         &SDL_GL_DeleteContext};

    if (this->gl.get() == nullptr) {
        throw runtime_error{string{"Unable to create OpenGL context: "} +
                            SDL_GetError()};
    }

    SDL_GL_SetSwapInterval(1);
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

auto Stonk::processInput() -> void {
    auto event = SDL_Event{};

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: this->isRunning = false; break;
            default: break;
        }
    }
}

auto Stonk::integrateState(State &state, double dt) -> void {
    this->physics.integrateState(state, dt);
}

auto Stonk::render(const State &state) const -> void {}
