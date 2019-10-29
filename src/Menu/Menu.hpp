#pragma once

#include "Akuma/Akuma.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"
/**
 * @class Menu
 * @brief The Menu game state object
 */
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
    void drawCube(float size, bool wireframe);
    void handleWindowEvent(SDL_Event &event);
    void displayDisclaimer();

  private:
	  ///The floor object being rendered behind the gui
    Floor floor;
	///The current rotation of the grid begin rendered
    float gridRotation = 0;
	/// The current path being rendered on the grid
    std::vector<Pathing::Node *> currentPath;
    auto updatePath() -> void;
};
