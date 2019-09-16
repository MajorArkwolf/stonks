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
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"

using Shay::ShaysWorld;
using std::runtime_error;
using std::string;
using Stonk::Engine;
using Stonk::State;

auto Engine::run() -> void {
    auto &engine     = Engine::get();
    auto &shaysWorld = ShaysWorld::get();

    auto frameCount    = 0l;
    auto lastFpsUpdate = 0.0;

    auto time      = engine.getTime();
    auto oldTime   = 0.0;
    auto deltaTime = 0.0;

    while (engine.getIsRunning()) {
        ++frameCount;
        oldTime   = time;
        time      = engine.getTime();
        deltaTime = time - oldTime;

        if (time - lastFpsUpdate >= FPS_UPDATE_INTERVAL) {
            engine.fps    = frameCount / (time - lastFpsUpdate);
            lastFpsUpdate = time;
            frameCount    = 0;
        }

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
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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
                         SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL |
                             SDL_WINDOW_ALLOW_HIGHDPI),
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

    SDL_GL_MakeCurrent(this->window.get(), this->context.get());

    // Enable Vsync.
    constexpr auto ENABLE_VSYNC = 1;
    SDL_GL_SetSwapInterval(ENABLE_VSYNC);

    // Capture the mouse.
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // Setup ImGui.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(this->window.get(), this->context.get());
    ImGui_ImplOpenGL2_Init();
}

Engine::~Engine() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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

    switch (gameMode) {
        case GameMode::SHAY: {
            shaysWorld.handleKeyEvents(event);
        } break;
        case GameMode::STONK: {
            // Send event to stonk input handler
        } break;
        case GameMode::MENU: {
            // Send event to menu handler
        } break;
    }

    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_P: {
            this->showDebugMenu = !this->showDebugMenu;
        } break;
        default: break;
    }
}

auto Engine::handleKeyRelease(SDL_Event &event) -> void {
    auto &shaysWorld = ShaysWorld::get();
    switch (gameMode) {
        case GameMode::SHAY: {
            shaysWorld.handleKeyEvents(event);
        } break;
        case GameMode::STONK: {
            // Send event to stonk input handler
        } break;
        case GameMode::MENU: {
            // Send event to menu handler
        } break;
    }
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_P: {

        } break;
        default: break;
    }
}

auto Engine::handleMouseMovement(SDL_Event &event) -> void {
    this->mouse.x = static_cast<float>(event.motion.xrel);
    this->mouse.y = static_cast<float>(event.motion.yrel);
}

auto Engine::handleMouseButtonPress(SDL_Event &event) -> void {
    // int numClicks =
    //     event.button.clicks; // Number of clicks received as event   e.g. 1 =
    //                          // single click, 2 = double click
    // int releaseXPos = event.button.x; // X-position of mouse when pressed
    // int releaseYPos = event.button.y; // Y-position of mouse when pressed
    auto &shaysWorld = ShaysWorld::get();
    switch (gameMode) {
        case GameMode::SHAY: {
            shaysWorld.handleMouseEvents(event);
        } break;
        case GameMode::STONK: {
            // Send event to stonk input handler
        } break;
        case GameMode::MENU: {
            // Send event to menu handler
        } break;
    }
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
        ImGui_ImplSDL2_ProcessEvent(&event);
        SDL_SetRelativeMouseMode(this->showDebugMenu ? SDL_FALSE : SDL_TRUE);

        switch (event.type) {
            case SDL_KEYDOWN: {
                this->handleKeyPress(event);
            } break;
            case SDL_KEYUP: {
                this->handleKeyRelease(event);
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                this->handleMouseButtonPress(event);
            } break;
            case SDL_MOUSEBUTTONUP: {
                this->handleMouseButtonRelease(event);
            } break;
            case SDL_MOUSEMOTION: {
                this->handleMouseMovement(event);
                handledMouse = true;
            } break;
            case SDL_MOUSEWHEEL: {
                this->handleMouseWheelMotion(event);
            } break;
            case SDL_QUIT: {
                this->isRunning = false;
            } break;
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

auto Engine::getTime() const -> double {
    return static_cast<double>(SDL_GetPerformanceCounter()) /
           static_cast<double>(SDL_GetPerformanceFrequency());
}
