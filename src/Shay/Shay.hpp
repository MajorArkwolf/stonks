#pragma once

#include <time.h>

#include <SDL2/SDL.h>

#include "Camera.hpp"
#include "ObjLoader/ObjLoader.hpp"
#include "Stonk/BaseState.hpp"
#include "TexturedPolygons.hpp"

/**
 * @namespace Shay
 * @brief The global Shay namespace
 */
namespace Shay {

    /**
     * @brief A shay enum, no one knows
     */
    enum ShayAxis : GLuint { XY = 0, XZ, YZ, YZ_FLIP, XY_FLIP };

    /**
     * @brief Enum list for all texture types
     */
    enum ShayTexture : GLuint {
        GRASS = 0,
        GRASS_2,
        GRASS_HILL,
        PAVEMENT,
        PAVEMENT_TOP,
        PAVEMENTSIDE_LEFT,
        PAVEMENTSIDE_RIGHT,
        PAVEMENTSIDE_TOP,
        PAVEMENT_CORNER_1,
        PAVEMENT_CORNER_2,
        PAVEMENT_FLIP,
        PAVEMENT_TOP_FLIP,
        PAVEMENT_16,
        DOORPAVE_1,
        WALL_BRICK_YZ,
        WALL_BRICK_XY,
        WALL_BRICK_XY_87WIDTH,
        WALL_BRICK_GAP_YZ,
        WALL_BRICK_GAP2_YZ,
        WALL_BRICK_USD_YZ,
        WALL_BRICK_XY_END,
        WALL_BRICK_YZ_END,
        WALL_GAP_1,
        WALL_BRICK_3_4,
        SHADOW_BRICK,
        WALL_BRICK_SEC_SIGN,
        WINDOWPOST_CHANC_FRONT,
        WINDOWPOST_CHANC_RIGHT,
        WINDOWPOST_CHANC_LEFT,
        WINDOWLEDGE_CHANC_FRONT,
        WINDOWLEDGE_CHANC_TOP,
        WINDOWPOST_PHYSSCI_FRONT,
        WINDOWPOST_PHYSSCI_RIGHT,
        WINDOWPOST_PHYSSCI_LEFT,
        WINDOWPOST_LIB_FRONT,
        WINDOWPOST_LIB_LEFT,
        WINDOWPOST_LIB_RIGHT,
        DOOR_POST_SECURITY,
        WINDOWLEDGE_PS_FRONT,
        WINDOWLEDGE_PS_TOP,
        WINDOWLEDGE_PS_BOTT,
        WINDOWLEDGE_LIB_A,
        WINDOWLEDGE_LIB_B,
        WINDOWLEDGE_LIB_TOP_A,
        WINDOWLEDGE_LIB_TOP_B,
        WINDOW_LEDGE_END_1,
        WINDOW_LEDGE_END_2,
        MAIN_POST,
        MAIN_POST_2,
        DOOR_POST_CHANC,
        DOOR_SIDEPOST_CHANC,
        DOOR_POST_LIB,
        PURPLE_POST,
        PURPLE_POSTSIDE,
        RED_POST,
        RED_POSTSIDE,
        ROOF_TOP,
        ROOF_TOP_LIB,
        ROOF_PLANKS,
        ROOF_BEAM_1,
        ROOF_PLANKS_2,
        ROOF_BEAM_2,
        BELOW_ROOF_FILL,
        ROOF_BEAM_3,
        ROOF_BEAM_4,
        ROOF_BEAM_3_TOP,
        KBLT,
        KBLT_EDGE,
        KBLT_EDGE_2,
        KBLT_EDGE_CORNER,
        KBLT_SIDE_1,
        KBLT_SIDE_2,
        NEXUS_SIGN,
        NEXUS_SIDE,
        SECURITY_SIGN,
        SECURITY_SIGN_2,
        SIGN_1,
        SIGN_1_SIDE_1,
        SIGN_1_SIDE_2,
        SIGN_2,
        SIGN_2_SIDE,
        PSC_SIGN,
        PSC_SIGN_2,
        CO_SIGN,
        STA_TRAVEL,
        STA_TRAVEL_EDGE,
        STA_TRAVEL_BRACKET,
        STA_TRAVEL_2,
        STA_TRAVEL_BOTTOM,
        TOILET_MEN,
        TOILET_WOMEN,
        GS_SIGN,
        GS_SIGN_2,
        GS_SIGN_EDGE,
        MAP_2,
        GLASS_BOARD,
        GLASS_BOARD_2,
        GLASS_BOARD_3,
        GLASS_B_SIDE,
        RUSTY_MAN,
        NO_SMOKE_SIGN,
        CARPET,
        DRINKS_SIDE,
        DRINKS_TOP,
        DRINKS_EDGE,
        DRINKS_SIDE_2,
        COKE_MACHINE,
        COFFEE_MACHINE,
        SWEET_MACHINE,
        MACHINE_SIDES,
        MACHINE_SIDES_2,
        Textures,
        TELEPHONE_BACK,
        TELEPHONE_FRONT,
        TELEPHONE_SIDE_1,
        TELEPHONE_FRONT_2,
        TELEPHONE_MAIN_SIDE,
        TELEPHONE_TOP_1,
        TELEPHONE_SIDE_2,
        TELEPHONE_TOP_2,
        TELEPHONE_BOTTOM,
        TELEPHONE_FILL,
        TELEPHONE_FRONT_3,
        STEPS_LIBRARY,
        STEPS_LIBRARY_TOP,
        STEP_PAVING_1,
        STEP_EDGE,
        WINDOW_1,
        WINDOW_2,
        WINDOW_3,
        WINDOW_4,
        WINDOW_5,
        WINDOW_6,
        WINDOW_7,
        WINDOW_8,
        WINDOW_9,
        WINDOW_10,
        WINDOW_11,
        WINDOW_12,
        WINDOW_13,
        WINDOW_14,
        WINDOW_14B,
        WINDOW_15,
        WINDOW_16,
        WINDOW_17,
        WINDOW_2B,
        WINDOW_2C,
        WINDOW_2US,
        WINDOW_3B,
        WINDOW_2USB,
        WINDOW_LIB_1,
        WINDOW_LIB_1A,
        WINDOW_LIB_1B,
        WINDOW_LIB_1C,
        WINDOW_LIB_US_A,
        WINDOW_LIB_US_B,
        WINDOW_LIB_DOOR_1,
        WINDOW_LIB_DOOR_2,
        WINDOW_LIB_LONG,
        ENTRANCE,
        ENTRANCE_2,
        EXIT_EAST,
        EXIT_WEST,
        CHANC_DOOR_1,
        CHANC_DOOR_2,
        WINDOW_2D,
        WINDOW_2E,
        WINDOW_1B,
        STEP_WINDOW,
        ABOVE_WINDOW_BLOCK,
        ABOVE_WINDOW_BLOCK_2,
        ABOVE_WINDOW_BLOCK_3,
        ABOVE_WINDOW_EDGE_3B,
        ABOVE_WINDOW_BLOCK_XY_3,
        ABOVE_LIB,
        ABOVE_UNDER_POSTS,
        ABOVE_UNDER_POSTS_2,
        ABOVE_WINDOW_UNDER_LIB,
        ABOVE_WINDOW_BLOCK_CHANC,
        ABOVE_WINDOW_EDGE_3B_LIB,
        ABOVE_WINDOW_EDGE_4B_LIB,
        ABOVE_UNDER_4B,
        ABOVE_CHANC_TEXT,
        ABOVE_CHANC_TEXT_2,
        ABOVE_PHYS_SCI_TEXT,
        ABOVE_CHANC_TEXT_3,
        ABOVE_LIB_TEXT,
        ABOVE_LIB_TEXT_2,
        ABOVE_TICKETS_TEXT,
        ABOVE_CHANC_EDGE,
        TOILET_DOOR_TOP,
        LIGHT,
        LIGHT_SUPPORT,
        LIGHT_SUPPORT_2,
        BENCH_TOP,
        BENCH_SIDE,
        BENCH_SIDE_2,
        BENCH_EDGE,
        BENCH_EDGE_TOP,
        BENCH_EDGE_SIDE,
        BENCH_EDGE_TOP_2,
        BENCH_EDGE_2,
        BENCH_EDGE_3,
        TICKET_COUNTER_TOP,
        TICKET_COUNTER_EDGE,
        TICKET_COUNTER_EDGE_2,
        TICKET_COUNTER_EDGE_3,
        TICKET_LEDGE,
        TICKET_LEDGE_EDGE,
        TICKET_LEDGE_EDGE_2,
        WALL_BRICK_STEPS_TOP,
        WALL_BRICK_STEPS,
        WALL_BRICK_STEPS_COVER,
        WALL_BRICK_STEPS_EDGE,
        WALL_BRICK_STEPS_EDGE_2,
        DRAINPIPE,
        COUNTER_TOP,
        COUNTER_SIDE,
        MAP,
        WELCOME,
        EXIT,
        NO_EXIT,
    };

    /**
     * @class ShaysWorld
     * @brief The ultimate Shay class used to handle all others
     */
    class ShaysWorld : public BaseState {
      public:
        GLfloat stepIncrement  = 0.0f;
        GLfloat angleIncrement = 0.0f;

        int frameCount    = 0;
        clock_t lastClock = {};

        /// Toggle for displaying on screen map
        bool DisplayMap = false;

        /// Toggle for displaying the welcome screen
        bool DisplayWelcome = true;

        /// Toggle for displaying the exit screen
        bool DisplayExit = false;

        /// Toggle for displaying all lights
        bool lightsOn = true;

        /// Toggle for displaying ECL
        bool displayECL = true;

        /// Toggle for displaying the debugMenu
        bool displayDebug = true;

        /// Toggle for drawing 3d axis
        bool shouldDrawAxis = false;

        int portalSpinAngle = 0;

        GLfloat step                = 0.0f;
        GLfloat step2               = 0.0f;
        GLfloat stepLength          = 0.0f;
        GLUquadricObj *glu_cylinder = nullptr;
        std::vector<Model> modelList;
        /**
         * @brief Camera object
         */
        Camera cam = {};

        /**
         * @brief Textured polygon object
         */
        TexturedPolygons tp = {};

        GLfloat light_position[4];
        GLfloat light_position1[4];

        ShaysWorld();

        static auto get() -> ShaysWorld &;

        auto hardInit() -> void;

        auto softInit() -> void;

        auto handleInput(SDL_Event &event) -> void;

        auto unInit() -> void;

        auto displayModel(const Model &model, float scale, bool colourFaces) -> void;

        auto handleKeyEvents(SDL_Event &event) -> void;

        auto handleMouseEvents(SDL_Event &event) -> void;

        auto DisplaySigns() -> void;

        auto drawAxis(float x, float y, float z, float length) -> void;

        void drawSolidCube(float scale);

        void displayPentagram(void);

        void displayTavern();

        void DisplayDebugMenu();

        void display();

        void update(double dt);

        void DrawBackdrop();

        void DisplayAboveWindowBlock();

        void DisplayBench();

        void DisplayBricks();

        void DisplayChancPosts();

        void DisplayCylinders();

        void DisplayDoorPaving();

        void DisplayDoorPosts();

        void DisplayEntranceSteps();

        void DisplayTavSteps();

        void DisplayExtras();

        void DisplayGrass();

        void DisplayLargerTextures();

        void DisplayLibraryPosts();

        void DisplayMainPosts();

        void DisplayPavement();

        void DisplayPhysSciPosts();

        void DisplayPurplePosts();

        void DisplayRedPosts();

        void DisplayRoof();

        void DisplayStepBricks();

        void DisplayTavStepBricks();

        void DisplayLights();

        void CreateTextureList();

        void DrawGrass();

        void DrawChancPosts();

        void DrawDoorPosts();

        void DrawPurplePosts();

        void DrawRedPosts();

        void DrawMainPosts();

        void DrawAboveWindowBlock();

        void DrawDoorPaving();

        void DrawPhysSciPosts();

        void DrawLibraryPosts();

        void DrawBricks();

        void DrawPavement();

        void DrawExtras();

        void DrawRoof();

        void DrawEntranceSteps();

        void DrawTavSteps();

        void DrawLargerTextures();

        void DrawLights();

        void DrawBench();

        void DrawCylinders();

        void DrawAngledRoofBeam(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                                GLfloat beamSize);

        void DrawAngledRoofBeam2(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                                 GLfloat beamSize);

        void DrawStepBricks();

        void DrawTavStepBricks();

        void DrawMapExit();

        void IncrementFrameCount();

        void CreateTextures();

        void CreateBoundingBoxes();

        void CreatePostBoundingBoxes();

        void CreatePlains();

        auto getCamPtr() -> Shay::Camera *;
    };
}
