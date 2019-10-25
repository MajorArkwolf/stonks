#include "Menu.hpp"

#include "Akuma/Pathing/Pathfinding.hpp"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"

/**
 * @brief Method for displaying the main menu window
 */
void Menu::displayMenuWindow() {
    auto &stonk  = Stonk::Engine::get();
    auto display = SDL_DisplayMode{};
    SDL_GetCurrentDisplayMode(0, &display);

    ImGui::SetNextWindowSize(ImVec2(300, 500), 1);
    ImGui::SetNextWindowPosCenter(1);

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
    if (ImGui::Button("Settings")) {
        stonk.showSettingsMenu = stonk.showSettingsMenu ? false : true;
    }
    if (ImGui::Button("Quit")) {
        stonk.isRunning = false;
    }

    ImGui::End();
}

/**
 * @brief Display function that is called every frame
 */
void Menu::display() {
    auto &stonk = Stonk::Engine::get();

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(stonk.window.get());
    ImGui::NewFrame();

    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    gluLookAt(-5, (floor.getGridSize().x + floor.getGridSize().y) / 2, -5,
              floor.getGridSize().x / 2, 0, floor.getGridSize().y / 2, 0, 1, 0);

    glPushMatrix();

    displayGrid();

    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    // Akuma::drawRectangle(20, 20, 0);
    glPopMatrix();

    displayMenuWindow();
    if (stonk.showSettingsMenu) {
        stonk.settingsMenu();
    }

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(stonk.window.get());
}
/**
 * @brief Displays the grid beind the main menu
 */
auto Menu::displayGrid() -> void {
    auto gridSize = floor.getGridSize();

    glPushMatrix();

    glTranslatef(gridSize.x / 2, 0, (gridSize.y / 2));
    glRotatef(gridRotation, 0, 1, 0);
    for (unsigned x = 0; x < gridSize.x; x++) {
        for (unsigned y = 0; y < gridSize.y; y++) {
            glPushMatrix();
            glTranslatef(x - 0.5f * gridSize.x, 0, (y - 0.5f * gridSize.y));
            glPushMatrix();
            glTranslatef(0.f, 0.03f, 0.f);
            Akuma::drawSquare(1, 1);
            glPopMatrix();
            if (!floor.getGridNode(x, y)->walkable) {
                glPushMatrix();
                glColor3f(0.7f, 0.7f, 0.7f);
                glTranslatef(0.f, 0.f, -0.01f);
                glPushMatrix();
                glTranslatef(0, 0.5, 0);

                drawCube(1.f, 0.f);
                glPopMatrix();
                glColor3f(1.f, 1.f, 1.f);
                glPopMatrix();
            }
            if (floor.getGridNode(x, y)->walkable) {
                glPushMatrix();
                // glColor3f(0.2, .2f, .2f);
                glEnable(GL_TEXTURE_2D);
                glTranslatef(-0.5f, 0.0f, -0.5);
                // drawSquare(1.f, 0.f);
                // glNormal3f(0, 1, 0);
                // OBJ::displayModel(modelList[0], 0.2f);
                glDisable(GL_TEXTURE_2D);
                glColor3f(1.f, 1.f, 1.f);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }
    for (auto n : currentPath) {
        glPushMatrix();
        glTranslatef(n->x - 0.5f * gridSize.x, 0, (n->y - 0.5f * gridSize.y));
        glPushMatrix();
        glTranslatef(0.f, 0.04f, 0.f);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(1, 1, 0);

        Akuma::drawSquare(1, 0);
        glColor3f(1, 1, 1);
        glDisable(GL_COLOR_MATERIAL);
        glPopMatrix();

        glPopMatrix();
    }
    glPopMatrix();
}
/**
 * @brief Draws cubes, used to display walls on the grid
 * @param size The relative size of the cube
 * @param wireframe Whether to draw wireframe cube
 */
void Menu::drawCube(float size, bool wireframe) {

    float vertices[8][3] = {{-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5},
                            {0.5, 0.5, -0.5},   {0.5, -0.5, -0.5},
                            {-0.5, -0.5, 0.5},  {-0.5, 0.5, 0.5},
                            {0.5, 0.5, 0.5},    {0.5, -0.5, 0.5}};
    glPushMatrix();
    glScalef(size, size, size);
    if (wireframe) { // FRONT?
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[3]);
    glEnd();

    if (wireframe) {
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }

    glVertex3fv(vertices[7]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[4]);

    glEnd();

    if (wireframe) {
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }
    glVertex3fv(vertices[3]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[7]);

    glEnd();

    if (wireframe) {
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }

    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[0]);

    glEnd();

    if (wireframe) { // Top
        glBegin(GL_LINE_LOOP);
    } else {
        glBegin(GL_POLYGON);
    }
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[1]);
    glEnd();

    glPopMatrix();
}

/**
 * @brief Window event handler used to handle window resizes
 * @param event The SDL Event containing the window event
 */
void Menu::handleWindowEvent(SDL_Event &event) {

    switch (event.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        case SDL_WINDOWEVENT_RESIZED: {
            auto &engine = Stonk::Engine::get();

            SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
            ratio = static_cast<double>(width) / static_cast<double>(height);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glViewport(0, 0, width, height);
            gluPerspective(60, ratio, 1, 150);
            glMatrixMode(GL_MODELVIEW);

        } break;
        default: break;
    }
}

/**
 * @brief Updates the currently rendered path on the grid
 */
auto Menu::updatePath() -> void {
    auto roomList     = floor.getRoomList();
    auto startNode    = (*roomList.begin())->getCentrePoint();
    auto endNode      = (*(roomList.end() - 1))->getCentrePoint();
    auto startingNode = floor.getGridNode(static_cast<unsigned>(startNode.x),
                                          static_cast<unsigned>(startNode.y));
    auto endingNode   = floor.getGridNode(static_cast<unsigned>(endNode.x),
                                        static_cast<unsigned>(endNode.y));

    currentPath = Pathing::Pathfinding::findPath(floor.getGrid(), *startingNode,
                                                 *endingNode, 0);
}

/**
 * @brief Used for resetting variables after the previous game state has been popped
 */
void Menu::softInit() {
    relativeMouse = 0;
    updatePath();
    glDisable(GL_LIGHTING);

    glLoadIdentity();
    glLineWidth(1);
    auto &engine = Stonk::Engine::get();

    SDL_GL_GetDrawableSize(engine.window.get(), &width, &height);
    ratio = static_cast<double>(width) / static_cast<double>(height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(60, ratio, 1, 300);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);

    glEnable(GL_DEPTH_TEST);
}
/**
 * @brief Used to load data into memory, called after creating new instance on the stack
 */
void Menu::hardInit() {
    softInit();
}

/**
 * @brief Default constructor for the Akuma game state
 */
void Menu::unInit() {}

/**
 * @brief Handles SDL events for the menu state
 * @param event The SDL event being passed in
 */
void Menu::handleInput(SDL_Event &event) {
    switch (event.type) {
        case SDL_WINDOWEVENT: {
            this->handleWindowEvent(event);
        } break;
        default: break;
    }
}

/**
 * @brief Used to decouple physics from frame rate
 * @param dt Delta time since last frame
 */
void Menu::update(double dt) {
    gridRotation = gridRotation + static_cast<float>(dt) * 40;
    if (gridRotation > 359) {
        gridRotation = 0;
        floor.regen(glm::ivec2(30, 30), 3);
        updatePath();
    }
}
