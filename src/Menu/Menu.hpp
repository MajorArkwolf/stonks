#pragma once

#include "Akuma/Akuma.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"

class Menu : public BaseState {
  public:
    void display();
    void softInit();
    void hardInit();
    void unInit();
    void handleInput(SDL_Event &event);
    void update(double dt);
    void displayMenuWindow();
    void displayGrid();

  private:
    Floor floor;
    float gridRotation = 0;
    std::vector<Pathing::Node *> currentPath;
    auto updatePath() -> void;
};
