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
Akuma::Akuma::Akuma() {

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

/**
 * @brief Akuma display function
 */
auto Akuma::Akuma::display() -> void {
    auto &stonk = Stonk::Engine::get();
    if (showEscapeMenu || showCharacterMenu || playerMouse || showInventory) {
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
    // glTranslatef(gridTranslation.x, gridTranslation.y, gridTranslation.z);
    displayGrid();
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    manager.draw();
    glPushMatrix();
    glTranslatef(0, 0, -20);
    // OBJ::displayModel(modelList[0], 5, 1);
    glPopMatrix();

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
    displayCombatLog();
    if (showEscapeMenu) {
        displayEscapeMenu();
    }
    if (stonk.showSettingsMenu) {
        stonk.settingsMenu();
    }

    /*if (this->shouldDrawAxis) {
        auto origin = this->camera.look + (this->camera.getForwardDir()
    * 1.01f); drawAxis(origin.x, origin.y, origin.z, 0.5f);
    }*/

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(stonk.window.get());
}

/**
 * @brief Soft initialiser for the Akuma gamestate
 */

auto Akuma::Akuma::softInit() -> void {
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
    ItemLoader item;
    item.init();

    // Load models textures etc here
    modelList.push_back(OBJ::Load("flattile.obj"));
    modelList.push_back(OBJ::Load("flatwall.obj"));

    createPlayer();
    generateLevel();
    makeStairs();
    turnManager.addEntity(player);
    softInit();

    turnManager.turnOnManager();
}

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
void Akuma::Akuma::displayDebugMenu() {
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
void Akuma::Akuma::displayGameStats() {
    auto &playerStats = player->getComponent<StatComponent>().stat;

    ImGui::SetNextWindowSize(ImVec2(250, 500), 1);
    ImGui::SetNextWindowPos(ImVec2(width - 250, 0), 1);

    ImGui::Begin("Game Info", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::Text("Player Stats");
    ImGui::Separator();
    std::string name       = "Name        : ";
    std::string playerName = playerStats.name;
    name                   = name + playerName;
    ImGui::Text("%s", name.c_str());
    ImGui::Text("Level       :  %.0d", playerStats.level);
    ImGui::Text("HP          :  %.0d", playerStats.HP);
    ImGui::Text("Strength    :  %.0d", playerStats.strength);
    ImGui::Text("Dexterity   :  %.0d", playerStats.dexterity);
    ImGui::Text("Luck        :  %.0d", playerStats.luck);
    ImGui::Text("Vitality    :  %.0d", playerStats.vitality);
    ImGui::Text("Intelligence:  %.0d", playerStats.intelligence);

	auto *e = player->getComponent<PlayerComponent>().getLookingAtNode();
    ImGui::Separator();
    ImGui::Text("Selected Enemy Stats");
    ImGui::Separator();
    if (e->occupant != nullptr && e->occupant->hasComponent<EnemyComponent>()) {
        auto &enemyStats      = e->occupant->getComponent<StatComponent>().stat;
		std::string name       = "Name        : ";
        std::string enemy = enemyStats.name;
        name                   = name + enemy;
		ImGui::Text("%s", name.c_str());
        ImGui::Text("Level       :  %.0d", enemyStats.level);
        ImGui::Text("HP          :  %.0d", enemyStats.HP);
        ImGui::Text("Strength    :  %.0d", enemyStats.strength);
        ImGui::Text("Dexterity   :  %.0d", enemyStats.dexterity);
        ImGui::Text("Luck        :  %.0d", enemyStats.luck);
        ImGui::Text("Vitality    :  %.0d", enemyStats.vitality);
        ImGui::Text("Intelligence:  %.0d", enemyStats.intelligence);
     }
    ImGui::End();
}

/**
 * @brief Uninitialiser for the Akuma gamestate
 */
auto Akuma::Akuma::unInit() -> void {}

/**
 * @brief Handles input for the Akuma gamestate
 * @param event The SDL event to read input from
 */
auto Akuma::Akuma::handleInput(SDL_Event &event) -> void {

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
            this->handleMouseWheel(event);
        } break;
        default: break;
    }
}

/**
 * @brief Physics update function for the Akuma gamestate
 * @param dt Delta time since last frame
 */
void Akuma::update([[maybe_unused]] double dt) {
    turnManager.update();
    manager.update();
    // player->getComponent<PositionComponent>().setXPos(
    //    player->getComponent<PositionComponent>().getXPos() + 0.01f);
    // player->getComponent<PositionComponent>().setZPos(
    //    player->getComponent<PositionComponent>().getZPos() + 0.01f);
    light_position[0] = player->getComponent<PositionComponent>().getXPos();
    // light_position[1] = 2;
    light_position[2] = player->getComponent<PositionComponent>().getZPos();
    // light_position[3] = 1;
    if (stairs != nullptr) {
        if (stairs->hasComponent<StairComponent>()) {
            if (stairs->getComponent<StairComponent>().checkStairActive()) {
                stairs->getComponent<StairComponent>().resetStairCase();
                descendLevel();
            }
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
            this->showInventory = showInventory ? 0 : 1;
        } break;
        case SDL_SCANCODE_ESCAPE: {
            this->showEscapeMenu = showEscapeMenu ? false : true;
        } break;
        case SDL_SCANCODE_SPACE: {
            player->getComponent<PlayerComponent>().issueAction();
        } break;
        case SDL_SCANCODE_R: {
            this->playerMouse = playerMouse ? 0 : 1;
        } break;
        default: break;
    }
}

void Akuma::handleKeyRelease(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_A: {
            player->getComponent<PlayerComponent>().turnEntity(1);
            break;
        }
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

void Akuma::handleMouseWheel(SDL_Event &event) {
    auto &cameraComp = player->getComponent<CameraComponent>();

    int amountScrolledY = event.wheel.y; // Amount scrolled up or down
    cameraComp.zoomCamera(amountScrolledY);
}

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
        player->getComponent<StatComponent>().setupEntity();
        this->showCharacterMenu = false;
    }

    ImGui::End();
}

/**
 * @brief Draws a 3-dimensional spatial axis at the given coordinates at the given length
 * @param x The x-coordinate to start the axis
 * @param y The y-coordinate to start the axis
 * @param z The z-coordinate to start the axis
 * @param length The amount to extend the axis lines in each respective direction
 */
auto Akuma::Akuma::drawAxis(float x, float y, float z, float length) -> void {
    glPushMatrix();
    glDepthMask(false);
    glLineWidth(5.0);

    // Draw the x-axis.
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex3f(x, y, z);
    glVertex3f(x + length, y, z);
    glEnd();

    // Draw the y-axis.
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex3f(x, y, z);
    glVertex3f(x, y + length, z);
    glEnd();

    // Draw the z-axis.
    glColor3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + length);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glDepthMask(true);
    glPopMatrix();
}

/**
 * @brief Displays the current grid within the room object
 */
auto Akuma::Akuma::displayGrid() -> void {
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

auto Akuma::Akuma::drawCube(float size, [[maybe_unused]] bool wireframe) -> void {
    glEnable(GL_TEXTURE_2D);
    OBJ::displayModel(modelList[1], size);
    glDisable(GL_TEXTURE_2D);
}

void Akuma::descendLevel() {
    turnManager.turnOffManager();
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
    } else if (floorLevel == bossFloor){
        clearEnemies();
        turnManager.clearActors();
        turnManager.addEntity(player);
        stairs->destroy();
        stairs = nullptr;
	}
}

void Akuma::clearEnemies() {
    for (auto &i : enemies) {
        i->destroy();
    }
    manager.refresh();
    enemies.clear();
}

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
        stonk.daGameStateStack.pop();
    }
    ImGui::SameLine();
    if (ImGui::Button("Quit to Desktop")) {
        stonk.isRunning = false;
    }
    ImGui::End();
}

void Akuma::displayCombatLog() {
    ImGui::SetNextWindowSize(ImVec2(400, 120), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("Combat Log");
    for (auto n : CombatLog::log()) {
        ImGui::Text("%s", n.c_str());
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::End();
}

void Akuma::generateLevel() {
    unsigned int enemyCount = diceRoller.Roll(floorLevel, 3u);
    for (unsigned i = 0; i <= enemyCount; ++i) {
        enemies.push_back(&manager.addEntity());
        enemies.at(i)->addComponentID<ScaleComponent>(glm::vec3{0.5, 0.5, 0.5});
        enemies.at(i)->addComponentID<PositionComponent>();
        bool walkable    = false;
        auto maxDistance = floor.getGridSize();
        glm::vec2 temp   = {0, 0};
        do {
            temp.x = diceRoller.Roll(static_cast<int>(maxDistance.x - 1));
            temp.y = diceRoller.Roll(static_cast<int>(maxDistance.y - 1));
            if (floor.getGridNode(temp)->walkable) {
                enemies.at(i)->getComponent<PositionComponent>().setNode(
                    floor.getGridNode(temp));
                walkable = true;
            }
        } while (!walkable);
        enemies.at(i)->addComponentID<ModelComponent>();
        enemies.at(i)->getComponent<ModelComponent>().setModel(
            "goblin_warrior_spear.obj");
        enemies.at(i)->addComponentID<MoveComponent>();
        enemies.at(i)->addComponentID<FloorComponent>();
        enemies.at(i)->getComponent<FloorComponent>().setFloor(floor);
        enemies.at(i)->addComponentID<EnemyComponent>();
        enemies.at(i)->getComponent<EnemyComponent>().SetPlayerTarget(player);
        enemies.at(i)->addComponentID<EquipmentComponent>();
        enemies.at(i)->addComponentID<CombatComponent>();
        enemies.at(i)->addComponentID<StatComponent>();
        string name = "Orc " + std::to_string(i);
        enemies.at(i)->getComponent<StatComponent>().stat.name = name;
        enemies.at(i)->addComponentID<TurnComponent>();
        turnManager.addEntity(enemies.at(i));
    }
}

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
    player->getComponent<InventoryComponent>().addItemToInventory(
        ItemManager::getItem(3));
    player->getComponent<InventoryComponent>().addItemToInventory(
        ItemManager::getItem(4));
    player->getComponent<InventoryComponent>().addItemToInventory(
        ItemManager::getItem(5));
}

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
        for (auto n : inventory) {
            ImGui::Text("%s", n.mItem.name.c_str());
            ImGui::SameLine(ImGui::GetWindowWidth() - 130);
            ImGui::Text(" (%zu)", n.quantitiy);
            ImGui::SameLine(ImGui::GetWindowWidth()-100);
            if (ImGui::Button("Equip")) {
                player->getComponent<InventoryComponent>().equipItemtoSlot(n.mItem);
                break;
            }
        }
    }
    ImGui::End();
}
