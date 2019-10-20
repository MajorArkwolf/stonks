#include "Menu.hpp"

#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"

void Menu::displayMenuWindow() {
    auto &stonk  = Stonk::Engine::get();
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);

    ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Once);
    ImGui::SetNextWindowPosCenter();

    ImGui::Begin("Menu", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();

    ImGui::Text("Choose game to load");
    if (ImGui::Button("Shays World")) {
        stonk.loadState(Stonk::GameMode::SHAY);
    }
    ImGui::SameLine();
    if (ImGui::Button("Akuma Shei")) {
        stonk.loadState(Stonk::GameMode::AKUMA);
    }

    ImGui::Separator();

    if (ImGui::Button("Quit")) {
        stonk.isRunning = false;
    }

    ImGui::End();
}

void Menu::display() {
    auto &stonk = Stonk::Engine::get();

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(stonk.window.get());
    ImGui::NewFrame();

    displayMenuWindow();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(stonk.window.get());
}

void Menu::softInit() {}

void Menu::hardInit() {}

void Menu::unInit() {}

void Menu::handleInput([[maybe_unused]] SDL_Event &event) {}

void Menu::update([[maybe_unused]] double dt) {}
