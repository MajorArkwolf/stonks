#pragma once

#include <time.h>

#include "Camera.h"
#include "TexturedPolygons.h"

namespace Shay {
    enum ShayAxis : GLuint { XY = 0, XZ, YZ, YZ_FLIP, XY_FLIP };

    enum ShayPlain : GLuint {
        FLAT_PLAIN = 0,
        XY_PLAIN,
        ZY_PLAIN,
    };

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

    class ShaysWorld {
      public:
        static constexpr GLfloat movementSpeed = 10.0f;
        static constexpr GLfloat rotationSpeed = 0.005f;

        static GLfloat stepIncrement;
        static GLfloat angleIncrement;
        static int frameCount;
        static clock_t lastClock;

        static int width;
        static int height;
        static double ratio;

        static bool DisplayMap;
        static bool DisplayWelcome;
        static bool DisplayExit;
        static bool lightsOn;
        static bool displayECL;
        static bool displayDebug;
        static int calcFPS;

        static GLfloat step;
        static GLfloat step2;
        static GLfloat stepLength;
        static GLUquadricObj *glu_cylinder;
        static unsigned char *image;
        static Camera cam;
        static TexturedPolygons tp;

        static void Init();
        static void Display();
        static void DrawBackdrop();
        static void DisplayAboveWindowBlock();
        static void DisplayBench();
        static void DisplayBricks();
        static void DisplayChancPosts();
        static void DisplayCylinders();
        static void DisplayDoorPaving();
        static void DisplayDoorPosts();
        static void DisplayEntranceSteps();
        static void DisplayExtras();
        static void DisplayGrass();
        static void DisplayLargerTextures();
        static void DisplayLibraryPosts();
        static void DisplayMainPosts();
        static void DisplayPavement();
        static void DisplayPhysSciPosts();
        static void DisplayPurplePosts();
        static void DisplayRedPosts();
        static void DisplayRoof();
        static void DisplayStepBricks();
        static void DisplayLights();
        static void DisplayECL();
        static void CreateTextureList();
        static void DrawGrass();
        static void DrawChancPosts();
        static void DrawDoorPosts();
        static void DrawPurplePosts();
        static void DrawRedPosts();
        static void DrawMainPosts();
        static void DrawAboveWindowBlock();
        static void DrawDoorPaving();
        static void DrawPhysSciPosts();
        static void DrawLibraryPosts();
        static void DrawBricks();
        static void DrawPavement();
        static void DrawExtras();
        static void DrawRoof();
        static void DrawEntranceSteps();
        static void DrawLargerTextures();
        static void DrawLights();
        static void DrawBench();
        static void DrawCylinders();
        static void DrawAngledRoofBeam(GLuint listNo, GLfloat x, GLfloat y,
                                       GLfloat z, GLfloat beamSize);
        static void DrawAngledRoofBeam2(GLuint listNo, GLfloat x, GLfloat y,
                                        GLfloat z, GLfloat beamSize);
        static void DrawStepBricks();
        static void DrawMapExit();
        static void DrawECL();
        static void BindBridgeWall(GLint LR);
        static void BindBuildingWall();
        static void BindWallPosts(GLint LR);
        static void IncrementFrameCount();
        static void CreateTextures();
        static void CreateBoundingBoxes();
        static void CreatePlains();
        static void DeleteImageFromMemory(unsigned char *tempImage);
        static Camera * getCamPtr();
    };
};
