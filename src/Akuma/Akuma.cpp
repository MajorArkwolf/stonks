#include "Akuma.hpp"

#include <iostream>
#include <sstream>

#include <glm/vec3.hpp>

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
    glLoadIdentity();

    auto &stonk = Stonk::Engine::get();
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
    gluPerspective(60, ratio, 1, 150);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
}

/**
 * @brief Hard initialiser for the Akuma gamestate
 */
auto Akuma::Akuma::hardInit() -> void {
    generateLevel();
    // Load models textures etc here
    modelList.push_back(OBJ::Load("flattile.obj"));
    modelList.push_back(OBJ::Load("flatwall.obj"));

    player = &manager.addEntity();
    player->addComponentID<FloorComponent>();
    player->getComponent<FloorComponent>().setFloor(floor);
    player->addComponentID<ScaleComponent>();
    player->getComponent<ScaleComponent>().setScale(glm::vec3{0.5, 0.5, 0.5});
    player->addComponentID<PositionComponent>();
    auto roomList = floor.getRoomList();
    glm::uvec2 pos      = roomList[0]->getCentrePoint();
    auto roomNode = floor.getGridNode(pos);
    player->getComponent<PositionComponent>().setPos(roomNode);
    player->addComponentID<ModelComponent>();
    player->getComponent<ModelComponent>().setModel("player_female.obj");
    player->addComponentID<PlayerComponent>();
    player->addComponentID<MoveComponent>();
    player->addComponentID<StatComponent>();
    player->getComponent<StatComponent>().stat.name = "Waman";
    player->addComponentID<CameraComponent>();
    player->addComponentID<TurnComponent>();
    player->getComponent<TurnComponent>().startYourTurn();

    softInit();
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

    auto display      = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);

    ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(display.w-300, 0), ImGuiCond_Once);

    ImGui::Begin("Game Info", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Separator();
    ImGui::Text("Player Stats");
    ImGui::Separator();
    std::string name       = "Name        : ";
    std::string playerName = playerStats.name;
    name                   = name + playerName;
    ImGui::Text(name.c_str());
    ImGui::Text("Level       :  %.0d", playerStats.level);
    ImGui::Text("HP          :  %.0d", playerStats.HP);
    ImGui::Text("Strength    :  %.0d", playerStats.strength);
    ImGui::Text("Dexterity   :  %.0d", playerStats.dexterity);
    ImGui::Text("Luck        :  %.0d", playerStats.luck);
    ImGui::Text("Vitality    :  %.0d", playerStats.vitality);
    ImGui::Text("Intelligence:  %.0d", playerStats.intelligence);

    ImGui::Separator();
    ImGui::Text("Selected Enemy Stats");
    ImGui::Separator();

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
        case SDL_KEYDOWN: {
            this->handleKeyRelease(event);
            break;
        }
        case SDL_KEYUP: {
            this->handleKeyPress(event);
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
    manager.update();
    // player->getComponent<PositionComponent>().setXPos(
    //    player->getComponent<PositionComponent>().getXPos() + 0.01f);
    // player->getComponent<PositionComponent>().setZPos(
    //    player->getComponent<PositionComponent>().getZPos() + 0.01f);
    light_position[0] = player->getComponent<PositionComponent>().getXPos();
    // light_position[1] = 2;
    light_position[2] = player->getComponent<PositionComponent>().getZPos();
    // light_position[3] = 1;
}

/**
 * @brief Handles key presses for the Akuma game state
 * @param event The SDL event containing the key press event
 */
void Akuma::handleKeyPress(SDL_Event &event) {
    auto &camera     = player->getComponent<CameraComponent>().camera;
    auto &cameraComp = player->getComponent<CameraComponent>();
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q: {
            camera.position.x--;
        } break;
        case SDL_SCANCODE_E: {
            camera.position.x++;
        } break;
        case SDL_SCANCODE_W: {
            camera.position.y++;
        } break;
        case SDL_SCANCODE_S: {
            camera.position.y--;
        } break;
        case SDL_SCANCODE_I: {
            cameraComp.rotateCamera(1);
        } break;
        case SDL_SCANCODE_K: {
            cameraComp.rotateCamera(-1);
        } break;
        case SDL_SCANCODE_Z: {
            camera.position.z++;
            break;
		}
        case SDL_SCANCODE_X: {
            camera.position.z--;
			break;
		}
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
        case SDL_SCANCODE_SPACE: {
            player->getComponent<PlayerComponent>().moveEntity();
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
    auto gridSize   = floor.getGridSize();
    auto playerComp = player->getComponent<PositionComponent>();
    Pathing::Node *playerNode =
        floor.getGridNode(static_cast<unsigned>(playerComp.getXPos()),
                          static_cast<unsigned>(playerComp.getZPos()));

    std::vector<Pathing::Node *> playerSurroundings =
        floor.getNeighbours(*playerNode);

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

    if (player->getComponent<TurnComponent>().getIsTurn()) {

        glLineWidth(3);
        for (auto n : playerSurroundings) {
            if (n->walkable) {

                glPushMatrix();
                glTranslatef(n->x - 0.5f * gridSize.x, 0,
                             (n->y - 0.5f * gridSize.y));
                glPushMatrix();
                glTranslatef(0.f, 0.04f, 0.f);
                glEnable(GL_COLOR_MATERIAL);
                glColor3f(1, 1, 0);

                drawSquare(1, 1);
                glColor3f(1, 1, 1);
                glDisable(GL_COLOR_MATERIAL);
                glPopMatrix();

                glPopMatrix();
            }
        }

        glLineWidth(1);
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
auto Akuma::drawRectangle(float _width, float _height, bool wireframe)
    -> void {
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
    floor.regen();
    floorLevel++;
    generateLevel();
}

void Akuma::ClearEnemies() {
    for (auto &i : enemies) {
        i->destroy();
    }
    enemies.clear();
}

void Akuma::generateLevel() {
    ClearEnemies();
    unsigned int enemyCount = diceRoller.Roll(floorLevel, 3u);
    for (unsigned i = 0; i <= enemyCount; ++i) {
        enemies.push_back(&manager.addEntity());
        enemies.at(i)->addComponentID<TurnComponent>();
        enemies.at(i)->addComponentID<ScaleComponent>(glm::vec3{0.5, 0.5, 0.5});
        enemies.at(i)->addComponentID<PositionComponent>();
        bool walkable    = false;
        auto maxDistance = floor.getGridSize();
        glm::vec2 temp   = {0, 0};
        do {
            temp.x = diceRoller.Roll(static_cast<int>(maxDistance.x - 1));
            temp.y = diceRoller.Roll(static_cast<int>(maxDistance.y - 1));
            if (floor.getGridNode(temp)->walkable) {
                enemies.at(i)->getComponent<PositionComponent>().setPos(
                    glm::vec3{temp.x, 0, temp.y});
                walkable = true;
            }
        } while (!walkable);
        enemies.at(i)->addComponentID<ModelComponent>();
        enemies.at(i)->getComponent<ModelComponent>().setModel(
            "goblin_warrior_spear.obj");
        // enemies.at(i)->addComponentID<MoveComponent>();
    }
}
