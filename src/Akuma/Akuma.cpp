#include "Akuma.hpp"

#include <iostream>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"

using std::stringstream;

/**
 * @brief Default constructor for the Akuma game state
 */
Akuma::Akuma::Akuma() {

    light_position[0] = 10;
    light_position[1] = 4;
    light_position[2] = 10;
    light_position[3] = 1;
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
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
              camera.look.x, camera.look.y, camera.look.z, camera.up.x,
              camera.up.y, camera.up.z);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.051f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.f);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1);
    glLightf(GL_LIGHT0, GL_SPOT_DIRECTION, 1);

    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(stonk.window.get());
    ImGui::NewFrame();

    glPushMatrix();
    // glTranslatef(gridTranslation.x, gridTranslation.y, gridTranslation.z);
    displayGrid();
    glPopMatrix();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0, 0, -20);
    // OBJ::displayModel(modelList[0], 5, 1);
    glPopMatrix();

	manager.draw();

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    displayDebugMenu();

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



    player = &manager.addEntity();
    player->addComponentID<ScaleComponent>();
    player->getComponent<ScaleComponent>().setScale(glm::vec3{0.5, 0.5, 0.5});
    player->addComponentID<PositionComponent>();
    player->getComponent<PositionComponent>().setPos(glm::vec3{2, 0, 1});
    player->addComponentID<ModelComponent>();
    player->getComponent<ModelComponent>().setModel("player_female.obj");
    player->addComponentID<MoveComponent>();
}

/**
 * @brief Hard initialiser for the Akuma gamestate
 */
auto Akuma::Akuma::hardInit() -> void {
    // Load models textures etc here
    modelList.push_back(OBJ::Load("flattile.obj"));
    modelList.push_back(OBJ::Load("flatwall.obj"));
    softInit();
}

/**
 * @brief Displays the IMGUI debug menu
 */
void Akuma::Akuma::displayDebugMenu() {
    auto &stonk = Stonk::Engine::get();
    auto buffer = stringstream{};

    if (stonk.showDebugMenu) {
        auto &pos    = this->camera.position;
        auto &look   = this->camera.look;
        auto &angles = this->camera.up;

        ImGui::Begin("Debug Menu");
        ImGui::Text("Camera: %.2f, %.2f, %.2f", static_cast<double>(pos.x),
                    static_cast<double>(pos.y), static_cast<double>(pos.z));
        ImGui::Text("Look: %.2f, %.2f, %.2f", static_cast<double>(look.x),
                    static_cast<double>(look.y), static_cast<double>(look.z));
        ImGui::Text("Angles: %.2f, %.2f", static_cast<double>(angles.x),
                    static_cast<double>(angles.y));
        ImGui::Separator();
        ImGui::Checkbox("Quit", &stonk.isRunning);
        ImGui::End();

        ImGui::Begin("FPS", nullptr,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::Text("%.0f", std::ceil(stonk.fps));

        ImGui::End();
    }
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
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            this->handleKeyPress(event);
        } break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION: {
            // this->handleMouseEvents(event);
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
}

/**
 * @brief Handles key presses for the Akuma game state
 * @param event The SDL event containing the key press event
 */
void Akuma::handleKeyPress(SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W: {
            camera.position.z++;
        } break;
        case SDL_SCANCODE_A: {
            camera.position.x--;
        } break;
        case SDL_SCANCODE_S: {
            camera.position.z--;
        } break;
        case SDL_SCANCODE_D: {
            camera.position.x++;
        } break;
        case SDL_SCANCODE_I: {
            camera.position.y++;
        } break;
        case SDL_SCANCODE_K: {
            camera.position.y--;
        } break;

        default: break;
    }

    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
              camera.look.x, camera.look.y, camera.look.z, camera.up.x,
              camera.up.y, camera.up.z);
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
                OBJ::displayModel(modelList[0], 0.2f);
                glDisable(GL_TEXTURE_2D);
                glColor3f(1.f, 1.f, 1.f);
                glPopMatrix();
            }
            /*if (x == grid.selected[0] && y == grid.selected[1]) {
                glColor3f(1.f, 0.f, 0.f);
                drawSquare(0.8f, 0.f);
                glColor3f(1.f, 1.f, 1.f);
            }
            if (x == grid.pathStart[0] && y == grid.pathStart[1]) {
                glColor3f(0.f, 1.f, 0.f);
                drawSquare(0.8f, 0.f);
                glColor3f(1.f, 1.f, 1.f);
            }
            if (x == grid.pathEnd[0] && y == grid.pathEnd[1]) {
                glColor3f(0.f, 0.f, 1.f);
                drawSquare(0.8f, 0.f);
                glColor3f(1.f, 1.f, 1.f);
            }*/
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
void Akuma::Akuma::drawSquare(float size, bool wireframe) {
    drawRectangle(size, size, wireframe);
}

/**
 * @brief Draws a rectangle on screen matching the given parameters
 * @param _height The height of the rectangle to create
 * @param _width The width of the rectangle to create
 * @param wireframe Whether to draw a wireframe or polygon
 */
auto Akuma::Akuma::drawRectangle(float _width, float _height, bool wireframe)
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
    // float vertices[8][3] = {{-0.5, -0.5, -0.5}, {-0.5, 1.5, -0.5},
    //                        {0.5, 1.5, -0.5},   {0.5, -0.5, -0.5},
    //                        {-0.5, -0.5, 0.5},  {-0.5, 1.5, 0.5},
    //                        {0.5, 1.5, 0.5},    {0.5, -0.5, 0.5}};
    // glPushMatrix();
    // glScalef(size, size, size);
    // if (wireframe) { // FRONT?
    //    glBegin(GL_LINE_LOOP);
    //} else {
    //    glBegin(GL_POLYGON);
    //}
    // glVertex3fv(vertices[0]);
    // glVertex3fv(vertices[1]);
    // glVertex3fv(vertices[2]);
    // glVertex3fv(vertices[3]);
    // glEnd();

    // if (wireframe) {
    //    glBegin(GL_LINE_LOOP);
    //} else {
    //    glBegin(GL_POLYGON);
    //}

    // glVertex3fv(vertices[7]);
    // glVertex3fv(vertices[6]);
    // glVertex3fv(vertices[5]);
    // glVertex3fv(vertices[4]);

    // glEnd();

    // if (wireframe) {
    //    glBegin(GL_LINE_LOOP);
    //} else {
    //    glBegin(GL_POLYGON);
    //}
    // glVertex3fv(vertices[3]);
    // glVertex3fv(vertices[2]);
    // glVertex3fv(vertices[6]);
    // glVertex3fv(vertices[7]);

    // glEnd();

    // if (wireframe) {
    //    glBegin(GL_LINE_LOOP);
    //} else {
    //    glBegin(GL_POLYGON);
    //}

    // glVertex3fv(vertices[4]);
    // glVertex3fv(vertices[5]);
    // glVertex3fv(vertices[1]);
    // glVertex3fv(vertices[0]);

    // glEnd();

    // if (wireframe) { // Top
    //    glBegin(GL_LINE_LOOP);
    //} else {
    //    glBegin(GL_POLYGON);
    //}
    // glVertex3fv(vertices[5]);
    // glVertex3fv(vertices[6]);
    // glVertex3fv(vertices[2]);
    // glVertex3fv(vertices[1]);
    // glEnd();

    // glPopMatrix();
}
