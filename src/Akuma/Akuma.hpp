#pragma once

#include <cmath>

#include "Akuma/Floor.hpp"
#include "ECS/Components.hpp"
#include "ObjLoader/ObjDisplay.hpp"
#include "RNG/Dice.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"
#include "glm/vec3.hpp"
#include "ECS/Components.hpp"
#include "RNG/Dice.hpp"
#include "TurnManager/TurnManager.hpp"
#include "Akuma/Items/ItemManager.hpp"
#include "glm/vec3.hpp"
#include "Akuma/EnemyFactory.hpp"

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
    void clearEnemies();
    auto displayGameStats() -> void;
    void displayEscapeMenu();
    void displayCombatLog();
    void placePlayer();
    void drawInventoryWindow();

	///The current floor level
    unsigned floorLevel = 1;
    unsigned bossFloor  = 9;
    void descendLevel();
	///Light position array
    GLfloat light_position[4];

  private:
	  ///Whether to draw the mouse on screen
    bool playerMouse = 0;
    bool showInventory = 0;
    void statSelection(const char *attribName, int statMin, int &pointsLeft,
                       int &attributePoints, std::string desc, int buttonCount);
	///Whether to draw the character menu
    bool showCharacterMenu = 1;
	///Whether to draw the escape menu
    bool showEscapeMenu    = 0;

	///ECS Manager
    Manager manager;
	///Player entity
    Entity *player = nullptr;
	///Stair entity used to ascend levels
    Entity *stairs = nullptr;
    Entity *boss   = nullptr;
    ///Factory used to generate enemies
    EnemyFactory enemyFactory;
	///Vector of enemy entities
    std::vector<Entity *> enemies;
	///RNG generator
    Dice diceRoller;
	///Manages turns between enemies and players
    TurnManager turnManager;
    /// The floor
    Floor floor;
    // Toggle for drawing 3d axis
    // bool shouldDrawAxis = false;
    auto drawAxis(float x, float y, float z, float length) -> void;
	///Vector of models
    std::vector<Model> modelList;
    void bossBattleEngage();
	void makeStairs();
    void createPlayer();
    void unMakeStairs();
};
