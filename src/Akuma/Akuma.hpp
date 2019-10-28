#pragma once

#include <cmath>

#include "Akuma/EnemyFactory.hpp"
#include "Akuma/Floor.hpp"
#include "Akuma/Items/ItemManager.hpp"
#include "ECS/Components.hpp"
#include "ObjLoader/ObjDisplay.hpp"
#include "RNG/Dice.hpp"
#include "Stonk/BaseState.hpp"
#include "Stonk/Engine.hpp"
#include "Stonk/OpenGl.hpp"
#include "TurnManager/TurnManager.hpp"
#include "glm/vec3.hpp"

/**
 * @class Akuma
 * @brief The Akuma game state object
 */
class Akuma : public BaseState {
  public:
    Akuma();
    ~Akuma();
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
    void displayDeathMenu();
    void displayHelpMenu();
    void displayStartMenu();
    void displayLevelUp();
    void displayIntro();
    void displayEnd();
    /// The current floor level
    unsigned floorLevel = 1;
    unsigned bossFloor  = 10;
    void descendLevel();
    /// Light position array
    GLfloat light_position[4];

  private:
    /// Whether to draw the mouse on screen
    bool playerIsDead = 0;
    bool showLevelUp   = 0;
    bool showIntro     = 1;
    bool showEnd       = 0;
    bool showInfo      = 0;
    bool playerMouse   = 0;
    bool showInventory = 0;
    void statSelection(const char *attribName, int statMin, int &pointsLeft,
                       int &attributePoints, std::string desc, int buttonCount);

    void levelStatSelection(const char *attribName, int &pointsLeft, int &attributePoints,
                       std::string desc, int buttonCount);
    /// Whether to draw the character menu
    bool showCharacterMenu = 1;
    /// Whether to draw the escape menu
    bool showEscapeMenu = 0;
    bool menuExit       = 0;
    bool hardExit       = 0;
    // Audio Manager
    Stonk::Audio *audiomgr = nullptr;
    /// Audio playlist
    std::vector<Stonk::Audio::Music> audioPlaylist;
    /// Shay Sound
    Stonk::Audio::Sound akumaSound;
    /// Track Number
    size_t trackNumber = 0;
    /// ECS Manager
    Manager manager;
    /// Player entity
    Entity *player = nullptr;
    /// Stair entity used to ascend levels
    Entity *stairs = nullptr;
    Entity *boss   = nullptr;
    /// Factory used to generate enemies
    EnemyFactory enemyFactory;
    /// Vector of enemy entities
    std::vector<Entity *> enemies;
    /// Manages turns between enemies and players
    TurnManager turnManager;
    /// The floor
    Floor floor;
    
    /// Vector of models
    std::vector<Model> modelList;
    void bossBattleEngage();
    void makeStairs();
    void createPlayer();
    void unMakeStairs();
    void audioPlayList();
};
