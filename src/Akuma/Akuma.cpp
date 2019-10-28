#include "Akuma.hpp"

#include <iostream>
#include <sstream>

#include <glm/vec3.hpp>

#include "Akuma/CombatLog.hpp"
#include "Camera.hpp"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"

using std::stringstream;

/**
 * @brief Default constructor for the Akuma game state
 */
Akuma::Akuma() {

    light_position[0] = 1;
    light_position[1] = 4;
    light_position[2] = 1;
    light_position[3] = 1;
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
    glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, 1);
}

Akuma::~Akuma() {
    audiomgr->StopMusic();
}

/**
 * @brief Akuma display function
 */
auto Akuma::display() -> void {
    auto &stonk = Stonk::Engine::get();
    if (showEscapeMenu || showCharacterMenu || playerMouse || showInventory ||
        playerIsDead || showLevelUp) {
        relativeMouse = 0;
    } else {
        relativeMouse = 1;
    }

    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    Player::Camera &camera = player->getComponent<CameraComponent>().camera;

    gluLookAt(
        static_cast<double>(camera.position.x),
        static_cast<double>(camera.position.y),
        static_cast<double>(camera.position.z),
        static_cast<double>(camera.look.x), static_cast<double>(camera.look.y),
        static_cast<double>(camera.look.z), static_cast<double>(camera.tilt.x),
        static_cast<double>(camera.tilt.y), static_cast<double>(camera.tilt.z));

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(stonk.window.get());
    ImGui::NewFrame();

    glPushMatrix();
    displayGrid();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    manager.draw();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    displayDebugMenu();
    displayGameStats();

    if (showInventory) {
        drawInventoryWindow();
    }

    if (showCharacterMenu) {
        drawCharacterMenu();
    }
    if ((showIntro)) {
        displayIntro();
    }
    displayCombatLog();
    if (showEscapeMenu) {
        displayEscapeMenu();
    }
    if (stonk.showSettingsMenu) {
        stonk.settingsMenu();
    }
    if (showInfo) {
        displayHelpMenu();
    }
    if (showLevelUp) {
        displayLevelUp();
    }
    if (playerIsDead) {
        displayDeathMenu();
    }

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(stonk.window.get());

    if (hardExit) {
        stonk.isRunning = false;
    }
    if (menuExit) {
        stonk.popStack();
    }
}

/**
 * @brief Soft initialiser for the Akuma gamestate
 */

auto Akuma::softInit() -> void {
    glLoadIdentity();
    glLineWidth(1);
    auto &engine = Stonk::Engine::get();

    SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
    ratio = static_cast<double>(width) / static_cast<double>(height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, ratio, 1, 70);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
}

/**
 * @brief Hard initialiser for the Akuma gamestate
 */
auto Akuma::Akuma::hardInit() -> void {
    CombatLog::log().clear();
    ItemLoader item;
    item.init();
    // Load models textures etc here
    modelList.push_back(OBJ::Load("flattile.obj"));
    modelList.push_back(OBJ::Load("flatwall.obj"));

    this->audiomgr = &(Stonk::Engine::get().audio);
    audioPlaylist.push_back(audiomgr->LoadMusic("ambient.ogg"));
    audioPlaylist.push_back(audiomgr->LoadMusic("ambient2.ogg"));
    akumaSound = audiomgr->LoadSound("akuma.ogg");
    createPlayer();
    enemyFactory.factorySetup(&floor, player);
    generateLevel();
    makeStairs();
    turnManager.addEntity(player);
    softInit();

    turnManager.turnOnManager();
}

/**
 * @brief Handles window events for the Akuma class
 * @param event The SDL event object containing the window event
 */
void Akuma::handleWindowEvent(SDL_Event &event) {
    switch (event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESIZED: {
            auto &engine = Stonk::Engine::get();

            SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
            ratio = static_cast<double>(width) / static_cast<double>(height);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glViewport(0, 0, width, height);
            gluPerspective(60, ratio, 1, 70);
            glMatrixMode(GL_MODELVIEW);
        } break;
        default: break;
    }
}

/**
 * @brief Displays the IMGUI debug menu
 */
void Akuma::displayDebugMenu() {
    auto &stonk = Stonk::Engine::get();
    auto buffer = stringstream{};

    if (stonk.showDebugMenu) {
        auto &pos    = player->getComponent<CameraComponent>().camera.position;
        auto &look   = player->getComponent<CameraComponent>().camera.look;
        auto &angles = player->getComponent<CameraComponent>().camera.tilt;

        auto playerpos = player->getComponent<PositionComponent>().getPos();

        ImGui::Begin("Debug Menu");
        ImGui::Text("Camera: %.2f, %.2f, %.2f", static_cast<double>(pos.x),
                    static_cast<double>(pos.y), static_cast<double>(pos.z));
        ImGui::Text("Look: %.2f, %.2f, %.2f", static_cast<double>(look.x),
                    static_cast<double>(look.y), static_cast<double>(look.z));
        ImGui::Text("Angles: %.2f, %.2f", static_cast<double>(angles.x),
                    static_cast<double>(angles.y));
        ImGui::Separator();
        ImGui::Text(
            "Player Position: %.2f, %.2f %.2f", static_cast<double>(playerpos.x),
            static_cast<double>(playerpos.y), static_cast<double>(playerpos.z));
        ImGui::Separator();
        if (ImGui::Button("Quit")) {
            stonk.isRunning = false;
        }
        ImGui::End();

        ImGui::Begin("FPS", nullptr,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::Text("%.0f", std::ceil(stonk.fps));

        ImGui::End();
    }
}

/**
 * @brief Displays the IMGUI debug menu
 */
void Akuma::displayGameStats() {
    auto &playerStats = player->getComponent<StatComponent>().stat;
    auto &playerEquip = player->getComponent<EquipmentComponent>();
    auto playerTurn   = player->getComponent<TurnComponent>().checkTurn();
    auto turnOutput   = string();
    if (playerTurn) {
        turnOutput = "Your Turn";
    } else {
        turnOutput = "Enemy Turn";
    }

    ImGui::SetNextWindowSize(ImVec2(250, 500), 1);
    ImGui::SetNextWindowPos(ImVec2(width - 250, 0), 1);

    ImGui::Begin("Game Info", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::Text("Game Stats");
    ImGui::Separator();
    ImGui::Text("%s", turnOutput.c_str());
    ImGui::Text("Floor Level  :  %.0d", floorLevel);
    ImGui::Text("Round        :  %.0d", turnManager.getTurnRound());

    ImGui::Separator();
    ImGui::Text("Player Stats");
    ImGui::Separator();
    std::string name       = "Name        : ";
    std::string playerName = playerStats.name;
    name                   = name + playerName;
    ImGui::Text("%s", name.c_str());
    ImGui::Text("Unspent Points: %d", playerStats.pointsLeft);
    ImGui::Text("Level       :  %.0d", playerStats.level);
    ImGui::Text("HP          :  %.0d/%.0d", playerStats.HP, playerStats.maxHP);
    ImGui::Text("Strength    :  %.0d", playerStats.strength);
    ImGui::Text("Dexterity   :  %.0d", playerStats.dexterity);
    ImGui::Text("Luck        :  %.0d", playerStats.luck);
    ImGui::Text("Vitality    :  %.0d", playerStats.vitality);
    ImGui::Text("Intelligence:  %.0d", playerStats.intelligence);
    ImGui::Separator();
    ImGui::Text("Equipped Items");
    ImGui::Separator();
    ImGui::Text("Main Hand:  %s", playerEquip.getEquippedMainHand().name.c_str());
    ImGui::Text("Armor:  %s", playerEquip.getEquippedArmor().name.c_str());

    if (!playerIsDead) {

        auto *e = player->getComponent<PlayerComponent>().getLookingAtNode();
        ImGui::Separator();
        ImGui::Text("Selected Enemy Stats");
        ImGui::Separator();
        if (e->occupant != nullptr && e->occupant->hasComponent<EnemyComponent>()) {
            auto &enemyStats = e->occupant->getComponent<StatComponent>().stat;
            std::string enemyNamename = "Name        : ";
            std::string enemy         = enemyStats.name;
            enemyNamename             = name + enemy;
            ImGui::Text("%s", name.c_str());
            ImGui::Text("Level       :  %.0d", enemyStats.level);
            ImGui::Text("HP          :  %.0d", enemyStats.HP);
            ImGui::Text("Strength    :  %.0d", enemyStats.strength);
            ImGui::Text("Dexterity   :  %.0d", enemyStats.dexterity);
            ImGui::Text("Luck        :  %.0d", enemyStats.luck);
            ImGui::Text("Vitality    :  %.0d", enemyStats.vitality);
            ImGui::Text("Intelligence:  %.0d", enemyStats.intelligence);
        }
    }
    ImGui::End();
}

/**
 * @brief Uninitialiser for the Akuma gamestate
 */
auto Akuma::unInit() -> void {}

/**
 * @brief Handles input for the Akuma gamestate
 * @param event The SDL event to read input from
 */
auto Akuma::handleInput(SDL_Event &event) -> void {

    switch (event.type) {
        case SDL_WINDOWEVENT: {
            this->handleWindowEvent(event);
        } break;
        case SDL_KEYDOWN: {
            this->handleKeyPress(event);
        } break;
        case SDL_KEYUP: {
            this->handleKeyRelease(event);
        } break;
        case SDL_MOUSEBUTTONDOWN: break;
        case SDL_MOUSEBUTTONUP: break;
        case SDL_MOUSEWHEEL: {
            if (!menuOpen()) {
                this->handleMouseWheel(event);
            }
        } break;
        default: break;
    }
}

/**
 * @brief Physics update function for the Akuma gamestate
 * @param dt Delta time since last frame
 */
void Akuma::update([[maybe_unused]] double dt) {
    if (!playerIsDead) {
        audioPlayList();
        turnManager.update();
        manager.update();
        light_position[0] = player->getComponent<PositionComponent>().getXPos();
        light_position[2] = player->getComponent<PositionComponent>().getZPos();
    }
    if (stairs != nullptr) {
        if (stairs->hasComponent<StairComponent>()) {
            if (stairs->getComponent<StairComponent>().checkStairActive()) {
                stairs->getComponent<StairComponent>().resetStairCase();
                descendLevel();
            }
        }
    }
    if (boss != nullptr) {
        if (boss->hasComponent<DeadComponent>()) {
            turnManager.turnOffManager();
            audiomgr->StopMusic();
            showEnd = 1;
        }
    }
    if (player != nullptr) {
        if (player->hasComponent<DeadComponent>()) {
            // THE DEATH MECHANIC
            clearEnemies();
            turnManager.clearActors();
            turnManager.turnOffManager();
            audiomgr->StopMusic();
            playerIsDead = 1;
        }
    }
}

/**
 * @brief Handles key presses for the Akuma game state
 * @param event The SDL event containing the key press event
 */
void Akuma::handleKeyPress(SDL_Event &event) {
    auto &cameraComp = player->getComponent<CameraComponent>();
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q: {
            cameraComp.rotateCamera(2);
        } break;
        case SDL_SCANCODE_E: {
            cameraComp.rotateCamera(-2);
        } break;
        case SDL_SCANCODE_I: {
            if (!showCharacterMenu) {
                this->showInventory = showInventory ? 0 : 1;
            }
        } break;
        case SDL_SCANCODE_ESCAPE: {
            this->showEscapeMenu = showEscapeMenu ? false : true;
        } break;
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_SPACE: {
            player->getComponent<PlayerComponent>().issueAction();
        } break;
        case SDL_SCANCODE_R: {
            this->playerMouse = playerMouse ? 0 : 1;
        } break;
        case SDL_SCANCODE_F1: {
            this->showInfo = showInfo ? 0 : 1;
        } break;
        case SDL_SCANCODE_K: {
            if (!showCharacterMenu) {
                this->showLevelUp = showLevelUp ? 0 : 1;
            }
        } break;
        default: break;
    }
}

/**
 * @brief Handles key release events for the Akuma game state
 * @param event The SDL event with the release event
 */
void Akuma::handleKeyRelease(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A: {
            player->getComponent<PlayerComponent>().turnEntity(1);
            break;
        }
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D: {
            player->getComponent<PlayerComponent>().turnEntity(-1);
            break;
        }
        case SDL_SCANCODE_X: {
            player->getComponent<PlayerComponent>().skipTurn();
            break;
        }
        default: break;
    }
}

/**
 * @brief Handles mouse wheel events for the akuma gamestate
 * @param event The SDL event containing the mouse wheel event
 */
void Akuma::handleMouseWheel(SDL_Event &event) {
    auto &cameraComp = player->getComponent<CameraComponent>();

    int amountScrolledY = event.wheel.y; // Amount scrolled up or down
    cameraComp.zoomCamera(amountScrolledY);
}

/**
 * @brief ImGui stat selector label and changer
 * @param attribName The name of the attribute
 * @param statMin The minimum the stat can be
 * @param pointsLeft The number of total points left
 * @param attributePoints The number of attribute points
 * @param desc The description of the attribute
 * @param buttonCount The Imgui button ID, needs to be different for every stat
 */
void Akuma::statSelection(const char *attribName, int statMin, int &pointsLeft,
                          int &attributePoints, std::string desc, int buttonCount) {
    ImGui::PushID(buttonCount);
    if (ImGui::Button("--")) {
        if (attributePoints > statMin) {
            attributePoints--;
            pointsLeft++;
        }
    }
    ImGui::SameLine(80);

    ImGui::Text("%s: ", attribName);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", desc.c_str());
    ImGui::SameLine(ImGui::GetWindowWidth() - 80);
    ImGui::Text("%d", attributePoints);
    ImGui::SameLine(ImGui::GetWindowWidth() - 30);

    if (ImGui::Button("++")) {
        if (pointsLeft >= 1 && attributePoints >= statMin) {
            attributePoints++;
            pointsLeft--;
        }
    }
    ImGui::PopID();
}

void Akuma::levelStatSelection(const char *attribName, int &pointsLeft,
                               int &attributePoints, std::string desc,
                               int buttonCount) {
    ImGui::PushID(buttonCount);
    ImGui::Text("%s: ", attribName);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", desc.c_str());
    ImGui::SameLine(ImGui::GetWindowWidth() - 80);
    ImGui::Text("%d", attributePoints);
    ImGui::SameLine(ImGui::GetWindowWidth() - 30);

    if (ImGui::Button("++")) {
        if (pointsLeft >= 1) {
            attributePoints++;
            pointsLeft--;
        }
    }
    ImGui::PopID();
}

/**
 * @brief Draws the character selection menu using ImGui
 */
void Akuma::drawCharacterMenu() {
    const int statMin = 8;
    auto &playerStats = player->getComponent<StatComponent>().stat;
    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);

    ImGui::Begin("Character Menu", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();

    ImGui::Text("Player Name");
    static char playerName[32] = "Name";
    ImGui::InputText("Player Name", playerName, 32);
    ImGui::Separator();
    ImGui::Text("Player Model");

    static int item_current_model = 0;
    ImGui::Combo("Player Model", &item_current_model, "Male\0Female\0");
    ImGui::Separator();

    static StatDescription desc;

    ImGui::Text("Player Stats");
    ImGui::Text("Points Left: %d", playerStats.pointsLeft);
    statSelection("Strength", statMin, playerStats.pointsLeft,
                  playerStats.strength, desc.strength, 1);
    statSelection("Vitality", statMin, playerStats.pointsLeft,
                  playerStats.vitality, desc.vitality, 2);
    statSelection("Dexterity", statMin, playerStats.pointsLeft,
                  playerStats.dexterity, desc.dexterity, 3);
    statSelection("Intelligence", statMin, playerStats.pointsLeft,
                  playerStats.intelligence, desc.intelligence, 4);
    statSelection("Luck", statMin, playerStats.pointsLeft, playerStats.luck,
                  desc.luck, 5);

    ImGui::Separator();
    if (ImGui::Button("Start")) {
        playerStats.name = std::string(playerName);

        if (item_current_model == 0) {
            player->getComponent<ModelComponent>().setModel("player_male.obj");
        } else {
            player->getComponent<ModelComponent>().setModel(
                "player_female.obj");
        }
        playerStats.pointsLeft = 0;
        player->getComponent<StatComponent>().setupEntity();
        this->showCharacterMenu = false;
    }

    ImGui::End();
}

/**
 * @brief Displays the current grid within the room object
 */
auto Akuma::displayGrid() -> void {
    auto gridSize = floor.getGridSize();

    glPushMatrix();
    glTranslatef(gridSize.x / 2, 0, (gridSize.y / 2));
    for (unsigned x = 0; x < gridSize.x; x++) {
        for (unsigned y = 0; y < gridSize.y; y++) {
            glPushMatrix();
            glTranslatef(x - 0.5f * gridSize.x, 0, (y - 0.5f * gridSize.y));
            glPushMatrix();
            glTranslatef(0.f, 0.03f, 0.f);
            drawSquare(1, 1);
            glPopMatrix();
            if (!floor.getGridNode(x, y)->walkable) {
                glPushMatrix();
                glColor3f(0.7f, 0.7f, 0.7f);
                glTranslatef(0.f, 0.f, -0.01f);
                glPushMatrix();
                glTranslatef(-0.5, 0, 0.5);

                drawCube(0.2f, 0.f);

                glPopMatrix();
                drawSquare(1.f, 0.f);
                glColor3f(1.f, 1.f, 1.f);
                glPopMatrix();
            }
            if (floor.getGridNode(x, y)->walkable) {
                glPushMatrix();
                // glColor3f(0.2, .2f, .2f);
                glEnable(GL_TEXTURE_2D);
                glTranslatef(-0.5f, 0.0f, -0.5);
                // drawSquare(1.f, 0.f);
                glNormal3f(0, 1, 0);
                OBJ::displayModel(modelList[0], 0.2f);
                glDisable(GL_TEXTURE_2D);
                glColor3f(1.f, 1.f, 1.f);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }

    glPopMatrix();
}

/**
 * @brief Draws a square on screen matching the given parameters
 * @param size The size of the square to create
 * @param wireframe Whether to draw a wireframe square or a polygon
 */
auto Akuma::drawSquare(float size, bool wireframe) -> void {
    Akuma::drawRectangle(size, size, wireframe);
}

/**
 * @brief Draws a rectangle on screen matching the given parameters
 * @param _height The height of the rectangle to create
 * @param _width The width of the rectangle to create
 * @param wireframe Whether to draw a wireframe or polygon
 */
auto Akuma::drawRectangle(float _width, float _height, bool wireframe) -> void {
    if (wireframe) {
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }
    glVertex3f(-0.5f * _width, 0, 0.5f * _height);
    glVertex3f(0.5f * _width, 0, 0.5f * _height);
    glVertex3f(0.5f * _width, 0, -0.5f * _height);
    glVertex3f(-0.5f * _width, 0, -0.5f * _height);
    glEnd();
}

/**
 * @brief Draws a cube model
 * @param size Size of the cube
 * @param wireframe Unused wireframe parameter
 */
auto Akuma::drawCube(float size, [[maybe_unused]] bool wireframe) -> void {
    glEnable(GL_TEXTURE_2D);
    OBJ::displayModel(modelList[1], size);
    glDisable(GL_TEXTURE_2D);
}

/**
 * @brief Descends a level for the akuma gamestate
 */
void Akuma::descendLevel() {
    turnManager.turnOffManager();
    turnManager.resetTurnRound();
    auto &p   = player->getComponent<StatComponent>();
    p.stat.HP = p.stat.maxHP;
    p.levelUp();
    if (floorLevel < bossFloor) {
        floor.regen();
        floorLevel++;
        clearEnemies();
        turnManager.clearActors();
        turnManager.addEntity(player);
        makeStairs();
        generateLevel();
        placePlayer(); // move player to new node.
        turnManager.sortActors();
        turnManager.turnOnManager();
    } else if (floorLevel == bossFloor) {
        floor.regen(glm::uvec2(30, 30), 1);
        clearEnemies();
        turnManager.clearActors();
        bossBattleEngage();
        turnManager.addEntity(player);
        unMakeStairs();
        turnManager.sortActors();
        turnManager.turnOnManager();
        this->audiomgr->PlaySound(this->akumaSound);
    }
}

/**
 * @brief Clears all enemies in the enemy array and removes them from the manager
 */
void Akuma::clearEnemies() {
    for (auto &i : enemies) {
        i->destroy();
    }
    manager.refresh();
    enemies.clear();
}

/**
 * @brief Displays the escape menu
 */
void Akuma::displayEscapeMenu() {
    auto &stonk = Stonk::Engine::get();
    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);

    ImGui::Begin("Game Menu", &showEscapeMenu,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (ImGui::Button("Settings")) {
        stonk.showSettingsMenu = stonk.showSettingsMenu ? false : true;
    }
    if (ImGui::Button("Quit to Main Menu")) {
        menuExit = 1;
    }
    ImGui::SameLine();
    if (ImGui::Button("Quit to Desktop")) {
        hardExit = 1;
    }
    ImGui::End();
}

/**
 * @brief Displays the combat log
 */
void Akuma::displayCombatLog() {
    ImGui::SetNextWindowSize(ImVec2(500, 120), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("Combat Log");
    for (auto n : CombatLog::log()) {
        ImGui::Text("%s", n.c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::End();
}

/**
 * @brief Generates a level by creating all enemies, and placing the enemies,
 * player and stairs and the correct positions
 */
void Akuma::generateLevel() {
    enemyFactory.generateEnemy(floorLevel, enemies, manager);
    for (auto &e : enemies) {
        turnManager.addEntity(e);
    }
}

/**
 * @brief Creates the stair entity within the level
 */
void Akuma::makeStairs() {
    if (stairs == nullptr) {
        stairs = &manager.addEntity();
    }
    auto roomList = floor.getRoomList();
    for (auto i = roomList.size() - 1; i > 0; i--) {
        auto roomSize =
            roomList.at(i)->gridTopRight - roomList.at(i)->gridBottomLeft;
        if (roomSize.x >= 3 && roomSize.y >= 3) {
            glm::uvec2 pos = roomList[i]->getCentrePoint();
            auto roomNode1 = floor.getGridNode(pos);
            pos.x -= 1;
            auto roomNode2 = floor.getGridNode(pos);
            pos.y += 1;
            auto roomNode3 = floor.getGridNode(pos);
            pos.x += 1;
            auto roomNode4 = floor.getGridNode(pos);
            if (!stairs->hasComponent<StairComponent>()) {
                stairs->addComponentID<StairComponent>();
            }
            stairs->getComponent<StairComponent>().setNodes(roomNode1, roomNode2,
                                                            roomNode3, roomNode4);
            if (!stairs->hasComponent<ScaleComponent>()) {
                stairs->addComponentID<ScaleComponent>(glm::vec3{0.3, 0.3, 0.3});
            }
            if (!stairs->hasComponent<PositionComponent>()) {
                stairs->addComponentID<PositionComponent>();
            }
            glm::vec3 e = {0, 0, 0};
            e.x += pos.x + 0.2f;
            e.z += pos.y + 0.2f;
            stairs->getComponent<PositionComponent>().setPos(e);
            if (!stairs->hasComponent<ModelComponent>()) {
                stairs->addComponentID<ModelComponent>();
                stairs->getComponent<ModelComponent>().setModel("stairs.obj");
            }
            break;
            // valid room
        }
    }
}

void Akuma::unMakeStairs() {
    stairs->getComponent<ModelComponent>().unSetModel();
    stairs->destroy();
    stairs = nullptr;
}

void Akuma::createPlayer() {
    player = &manager.addEntity();
    player->addComponentID<FloorComponent>();
    player->getComponent<FloorComponent>().setFloor(floor);
    player->addComponentID<ScaleComponent>();
    player->getComponent<ScaleComponent>().setScale(glm::vec3{0.5, 0.5, 0.5});
    player->addComponentID<PositionComponent>();
    placePlayer();
    player->addComponentID<ModelComponent>();
    player->addComponentID<PlayerComponent>();
    player->addComponentID<MoveComponent>();
    player->addComponentID<StatComponent>();
    player->addComponentID<CameraComponent>();
    player->addComponentID<TurnComponent>();
    player->addComponentID<CombatComponent>();
    player->addComponentID<InventoryComponent>();
    player->addComponentID<EquipmentComponent>();
}

/**
 * @brief Places a player entity within the level
 */
void Akuma::placePlayer() {
    auto roomList  = floor.getRoomList();
    glm::uvec2 pos = roomList[0]->getCentrePoint();
    auto roomNode  = floor.getGridNode(pos);
    player->getComponent<PositionComponent>().setPos(roomNode);
}

void Akuma::drawInventoryWindow() {
    ImGui::SetNextWindowSize(ImVec2(400, 120), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 400), ImGuiCond_Once);
    ImGui::Begin("Inventory", &showInventory);
    if (player->hasComponent<InventoryComponent>()) {
        auto &inventory = player->getComponent<InventoryComponent>().inventoryList;
        if (inventory.size() == 0) {
            ImGui::Text("Only cobwebs in here");
        } else {

            for (size_t i = 0; i < inventory.size(); i++) {
                ImGui::PushID(static_cast<int>(i));
                ImGui::Text("%s", inventory[i].mItem.name.c_str());
                ImGui::SameLine(ImGui::GetWindowWidth() - 130);
                ImGui::Text(" (%zu)", inventory[i].quantitiy);
                ImGui::SameLine(ImGui::GetWindowWidth() - 100);

                if (ImGui::Button("Equip")) {
                    player->getComponent<InventoryComponent>().equipItemtoSlot(
                        inventory[i].mItem);
                }
                ImGui::PopID();
            }
        }
    }
    ImGui::End();
}

void Akuma::displayDeathMenu() {
    ImGui::SetNextWindowSize(ImVec2(300, 240), 1);
    ImGui::SetNextWindowPosCenter(1);

    ImGui::Begin("Dead", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove);

    ImGui::Text("You died");

    ImGui::Separator();
    if (ImGui::Button(("Quit to menu"), ImVec2(ImGui::GetWindowSize().x - 15, 80))) {
        menuExit = 1;
    }
    if (ImGui::Button(("Quit to desktop"),
                      ImVec2(ImGui::GetWindowSize().x - 15, 80))) {
        hardExit = 1;
    }
    ImGui::End();
}

void Akuma::displayHelpMenu() {

    ImGui::SetNextWindowSize(ImVec2(550, 300), 1);
    ImGui::SetNextWindowPosCenter(ImGuiCond_FirstUseEver);

    ImGui::Begin("Game Information", &showInfo,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::Text("Controls");
    ImGui::Separator();
    ImGui::Separator();

    ImGui::Text("A");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Rotates player counter-clockwise");
    ImGui::Separator();
    ImGui::Text("D");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Rotates player clockwise");
    ImGui::Separator();
    ImGui::Text("Spacebar");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Moves to or attacks selected square");
    ImGui::Separator();
    ImGui::Text("X");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Skips current player turn");
    ImGui::Separator();
    ImGui::Text("I");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Shows player inventory");
    ImGui::Separator();
    ImGui::Text("K");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Open Level up menu");
    ImGui::Separator();
    ImGui::Text("Q");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Rotates camera counter-clockwise around player");
    ImGui::Separator();
    ImGui::Text("E");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Rotates camera clockwise aorund player");
    ImGui::Separator();
    ImGui::Text("Mouse Wheel");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Zooms in and out");
    ImGui::Separator();
    ImGui::Text("Escape");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Shows escape menu");
    ImGui::Separator();
    ImGui::Text("F1");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Displays help menu");
    ImGui::Separator();
    ImGui::Text("R");
    ImGui::SameLine(ImGui::GetWindowWidth() - 350);
    ImGui::BulletText("Shows mouse");
    ImGui::Separator();
    ImGui::End();
}

void Akuma::displayLevelUp() {
    auto &playerStats = player->getComponent<StatComponent>().stat;

    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);

    ImGui::Begin("Level Up!", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    static StatDescription desc;
    ImGui::Separator();
    ImGui::Text("Player Stats");
    ImGui::Separator();
    ImGui::TextColored(ImVec4(255, 0, 0, 255), "Points are non refundable");
    ImGui::Separator();
    ImGui::Text("Points Left: %d", playerStats.pointsLeft);
    ImGui::Separator();
    levelStatSelection("Strength", playerStats.pointsLeft, playerStats.strength,
                       desc.strength, 1);

    ImGui::PushID(2);
    ImGui::Text("Vitality");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", desc.vitality.c_str());
    ImGui::SameLine(ImGui::GetWindowWidth() - 80);
    ImGui::Text("%d", playerStats.vitality);
    ImGui::SameLine(ImGui::GetWindowWidth() - 30);

    if (ImGui::Button("++")) {
        if (playerStats.pointsLeft >= 1) {
            player->getComponent<StatComponent>().pointVitality();
            playerStats.pointsLeft--;
        }
    }
    ImGui::PopID();

    levelStatSelection("Dexterity", playerStats.pointsLeft,
                       playerStats.dexterity, desc.dexterity, 3);
    levelStatSelection("Intelligence", playerStats.pointsLeft,
                       playerStats.intelligence, desc.intelligence, 4);
    levelStatSelection("Luck", playerStats.pointsLeft, playerStats.luck,
                       desc.luck, 5);

    ImGui::Separator();
    if (playerStats.pointsLeft < 1) {

        if (ImGui::Button("Accept")) {

            this->showLevelUp = false;
            player->getComponent<StatComponent>().newMaxHP();
        }
    }

    ImGui::End();
}

void Akuma::displayIntro() {
    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);
    ImGui::Begin("INTRO", &showIntro, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::TextWrapped(
        "You wake up, it smells of pungent mould and you appeared to be "
        "stripped of all your personal belongings, through the door you can "
        "see light but the coldness of this room validates your thought, You "
        "are deep underground. You have heard stories of the devil shei who "
        "captures young adventurers and feeds them to his minions. You have "
        "got to get out of here before you become their next meal!");
    ImGui::PushItemWidth(-100);
    if (ImGui::Button("START")) {
        showIntro = showIntro ? 0 : 1;
    }
    ImGui::End();
}

void Akuma::displayEnd() {
    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);
    ImGui::Begin("Congratulations", &showIntro, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::TextWrapped(
        "Devil Sheis corpse lays on the ground, demonic blood of a thick dark "
        "tarry substance oozes out, the smell causes you to convulse, however "
        "nows not the time to admire your accomplishments but instead get out "
        "of this god awful dungeon and back to society.You wonder how long you "
        "have been down here, a day maybe a week.Who knows, but you can see "
        "the staircase out ofhere.Hopefully there is still a society to come "
        "home too");
    ImGui::PushItemWidth(-100);
    if (ImGui::Button("START")) {
        showEnd = showEnd ? 0 : 1;
    }
    ImGui::End();
}

void Akuma::bossBattleEngage() {
    auto floorSize = floor.getGridSize();
    bool loop      = true;
    for (auto x = 1u; x < (floorSize.x - 1u) && loop; x++) {
        for (auto y = 1u; x < (floorSize.y - 1u) && loop; y++) {
            if (floor.getGridNode(x, y)->walkable) {
                player->getComponent<PositionComponent>().setNode(
                    floor.getGridNode(x, y));
                loop = false;
            }
        }
    }
    boss = &manager.addEntity();
    boss->addComponentID<ScaleComponent>(glm::vec3{0.5, 0.5, 0.5});
    boss->addComponentID<PositionComponent>();
    loop = true;
    for (auto x = (floorSize.x - 1u); x > 1u && loop; x--) {
        for (auto y = (floorSize.y - 1u); y > 1u && loop; y--) {
            if (floor.getGridNode(x, y)->walkable) {
                boss->getComponent<PositionComponent>().setNode(
                    floor.getGridNode(x, y));
                loop = false;
            }
        }
    }
    boss->addComponentID<ModelComponent>();
    boss->getComponent<ModelComponent>().setModel("akuma.obj");
    boss->addComponentID<MoveComponent>();
    boss->addComponentID<FloorComponent>();
    boss->getComponent<FloorComponent>().setFloor(floor);
    boss->addComponentID<EnemyComponent>();
    boss->getComponent<EnemyComponent>().SetPlayerTarget(player);
    boss->getComponent<EnemyComponent>().lockedToPlayer = true;
    boss->addComponentID<EquipmentComponent>();
    boss->addComponentID<CombatComponent>();
    boss->addComponentID<StatComponent>();
    CharacterSheet akumaShet;
    akumaShet.strength                       = 16;
    akumaShet.dexterity                      = 14;
    akumaShet.vitality                       = 14;
    akumaShet.name                           = "Akuma Shei";
    boss->getComponent<StatComponent>().stat = akumaShet;
    boss->getComponent<StatComponent>().setupEntity();
    boss->addComponentID<TurnComponent>();
    turnManager.addEntity(boss);
}

void Akuma::audioPlayList() {
    if (audiomgr->checkPlayer() == 0) {
        if (trackNumber < audioPlaylist.size()) {
            audiomgr->PlayMusic(audioPlaylist.at(trackNumber), 1);
            trackNumber++;
        } else {
            trackNumber = 0;
            audiomgr->PlayMusic(audioPlaylist.at(trackNumber));
        }
    }
}

bool Akuma::menuOpen() {
    if (playerIsDead || showLevelUp || showIntro || showEnd || showInfo ||
        showInventory || showCharacterMenu) {
        return true;
    }
    return false;
}
