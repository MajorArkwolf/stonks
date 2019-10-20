#pragma once

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
};
