#pragma once

#include <cmath>

#include "Akuma/Floor.hpp"

#include "ObjLoader/ObjDisplay.hpp"
#include "RNG/Dice.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"
#include "TurnManager/TurnManager.hpp"
#include "glm/vec3.hpp"
#include "ECS/Components.hpp"
/**
 * @class Akuma
 * @brief The Akuma game state object
 */
class Akuma : public BaseState {
  public:
    Akuma();
    ~Akuma() = default;
    auto display() -> void;
    auto softInit() -> void;
    auto hardInit() -> void;
    void handleWindowEvent(SDL_Event &event);
    auto displayGrid() -> void;
    static auto drawRectangle(float width, float height, bool wireframe) -> void;
    static auto drawSquare(float size, bool wireframe) -> void;
    auto displayDebugMenu() -> void;
    auto unInit() -> void;
    auto handleInput(SDL_Event &event) -> void;
    void update(double dt);
    void handleKeyPress(SDL_Event &event);
    void handleKeyRelease(SDL_Event &event);
    void handleMouseWheel(SDL_Event &event);
    void drawCharacterMenu();
    void drawCube(float size, bool wireframe);
    void generateLevel();
    void ClearEnemies();
    auto displayGameStats() -> void;
    void displayEscapeMenu();

    unsigned floorLevel = 1;
    void descendLevel();

    glm::vec3 gridTranslation = {0, 0, -50.f};

    GLfloat light_position[4];

  private:
    void statSelection(const char *attribName, int statMin, int &pointsLeft,
                       int &attributePoints, std::string desc, int buttonCount);
    bool showCharacterMenu = 1;
    bool showEscapeMenu    = 0;
    Manager manager;
    Entity *player = nullptr;
    std::vector<Entity *> enemies;
    Dice diceRoller;
    TurnManager turnManager;
    /// The floor
    Floor floor;
    // Toggle for drawing 3d axis
    // bool shouldDrawAxis = false;
    auto drawAxis(float x, float y, float z, float length) -> void;
    std::vector<Model> modelList;
};
