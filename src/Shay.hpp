#include <time.h>
#include "Camera.h"
#include "TexturedPolygons.h"

// TEXTURE IMAGE AXISES
constexpr GLuint XY      = 0;
constexpr GLuint XZ      = 1;
constexpr GLuint YZ      = 2;
constexpr GLuint YZ_FLIP = 3;
constexpr GLuint XY_FLIP = 4;

// PLAIN TYPES
constexpr GLuint FLAT_PLAIN = 0;
constexpr GLuint XY_PLAIN   = 1;
constexpr GLuint ZY_PLAIN   = 2;

// TEXTURES
// Grass Textures
constexpr GLuint GRASS      = 1;
constexpr GLuint GRASS_2    = 2;
constexpr GLuint GRASS_HILL = 3;
// Pavement Textures
constexpr GLuint PAVEMENT           = 4;
constexpr GLuint PAVEMENT_TOP       = 5;
constexpr GLuint PAVEMENTSIDE_LEFT  = 6;
constexpr GLuint PAVEMENTSIDE_RIGHT = 7;
constexpr GLuint PAVEMENTSIDE_TOP   = 8;
constexpr GLuint PAVEMENT_CORNER_1  = 9;
constexpr GLuint PAVEMENT_CORNER_2  = 10;
constexpr GLuint PAVEMENT_FLIP      = 11;
constexpr GLuint PAVEMENT_TOP_FLIP  = 12;
constexpr GLuint PAVEMENT_16        = 13;
constexpr GLuint DOORPAVE_1         = 14;
// Wall Brick Textures
constexpr GLuint WALL_BRICK_YZ         = 15;
constexpr GLuint WALL_BRICK_XY         = 16;
constexpr GLuint WALL_BRICK_XY_87WIDTH = 17;
constexpr GLuint WALL_BRICK_GAP_YZ     = 18;
constexpr GLuint WALL_BRICK_GAP2_YZ    = 19;
constexpr GLuint WALL_BRICK_USD_YZ     = 20;
constexpr GLuint WALL_BRICK_XY_END     = 21;
constexpr GLuint WALL_BRICK_YZ_END     = 22;
constexpr GLuint WALL_GAP_1            = 23;
constexpr GLuint WALL_BRICK_3_4        = 24;
constexpr GLuint SHADOW_BRICK          = 25;
constexpr GLuint WALL_BRICK_SEC_SIGN   = 216;
// Window Post Textures
constexpr GLuint WINDOWPOST_CHANC_FRONT   = 26;
constexpr GLuint WINDOWPOST_CHANC_RIGHT   = 27;
constexpr GLuint WINDOWPOST_CHANC_LEFT    = 28;
constexpr GLuint WINDOWLEDGE_CHANC_FRONT  = 29;
constexpr GLuint WINDOWLEDGE_CHANC_TOP    = 30;
constexpr GLuint WINDOWPOST_PHYSSCI_FRONT = 31;
constexpr GLuint WINDOWPOST_PHYSSCI_RIGHT = 32;
constexpr GLuint WINDOWPOST_PHYSSCI_LEFT  = 33;
constexpr GLuint WINDOWPOST_LIB_FRONT     = 34;
constexpr GLuint WINDOWPOST_LIB_LEFT      = 35;
constexpr GLuint WINDOWPOST_LIB_RIGHT     = 36;
// Door Post Textures
constexpr GLuint DOOR_POST_SECURITY = 37;
// Window Ledge Textures
constexpr GLuint WINDOWLEDGE_PS_FRONT  = 38;
constexpr GLuint WINDOWLEDGE_PS_TOP    = 39;
constexpr GLuint WINDOWLEDGE_PS_BOTT   = 40;
constexpr GLuint WINDOWLEDGE_LIB_A     = 41;
constexpr GLuint WINDOWLEDGE_LIB_B     = 42;
constexpr GLuint WINDOWLEDGE_LIB_TOP_A = 43;
constexpr GLuint WINDOWLEDGE_LIB_TOP_B = 44;
constexpr GLuint WINDOW_LEDGE_END_1    = 45;
constexpr GLuint WINDOW_LEDGE_END_2    = 46;
// Main Post Textures
constexpr GLuint MAIN_POST   = 47;
constexpr GLuint MAIN_POST_2 = 48;
// Door Post Textures
constexpr GLuint DOOR_POST_CHANC     = 49;
constexpr GLuint DOOR_SIDEPOST_CHANC = 50;
constexpr GLuint DOOR_POST_LIB       = 215;
// Coloured Posts Textures
constexpr GLuint PURPLE_POST     = 51;
constexpr GLuint PURPLE_POSTSIDE = 52;
constexpr GLuint RED_POST        = 53;
constexpr GLuint RED_POSTSIDE    = 54;
// Roof Textures
constexpr GLuint ROOF_TOP        = 55;
constexpr GLuint ROOF_TOP_LIB    = 56;
constexpr GLuint ROOF_PLANKS     = 57;
constexpr GLuint ROOF_BEAM_1     = 58;
constexpr GLuint ROOF_PLANKS_2   = 59;
constexpr GLuint ROOF_BEAM_2     = 60;
constexpr GLuint BELOW_ROOF_FILL = 61;
constexpr GLuint ROOF_BEAM_3     = 62;
constexpr GLuint ROOF_BEAM_4     = 63;
constexpr GLuint ROOF_BEAM_3_TOP = 64;
// KBLT Textures
constexpr GLuint KBLT             = 65;
constexpr GLuint KBLT_EDGE        = 66;
constexpr GLuint KBLT_EDGE_2      = 67;
constexpr GLuint KBLT_EDGE_CORNER = 68;
constexpr GLuint KBLT_SIDE_1      = 69;
constexpr GLuint KBLT_SIDE_2      = 70;
// Sign and Other Textures
constexpr GLuint NEXUS_SIGN         = 71;
constexpr GLuint NEXUS_SIDE         = 72;
constexpr GLuint SECURITY_SIGN      = 73;
constexpr GLuint SECURITY_SIGN_2    = 74;
constexpr GLuint SIGN_1             = 75;
constexpr GLuint SIGN_1_SIDE_1      = 76;
constexpr GLuint SIGN_1_SIDE_2      = 77;
constexpr GLuint SIGN_2             = 78;
constexpr GLuint SIGN_2_SIDE        = 79;
constexpr GLuint PSC_SIGN           = 80;
constexpr GLuint PSC_SIGN_2         = 81;
constexpr GLuint CO_SIGN            = 82;
constexpr GLuint STA_TRAVEL         = 83;
constexpr GLuint STA_TRAVEL_EDGE    = 84;
constexpr GLuint STA_TRAVEL_BRACKET = 85;
constexpr GLuint STA_TRAVEL_2       = 86;
constexpr GLuint STA_TRAVEL_BOTTOM  = 87;
constexpr GLuint TOILET_MEN         = 88;
constexpr GLuint TOILET_WOMEN       = 89;
constexpr GLuint GS_SIGN            = 90;
constexpr GLuint GS_SIGN_2          = 91;
constexpr GLuint GS_SIGN_EDGE       = 92;
constexpr GLuint MAP_2              = 93;
constexpr GLuint GLASS_BOARD        = 94;
constexpr GLuint GLASS_BOARD_2      = 95;
constexpr GLuint GLASS_BOARD_3      = 96;
constexpr GLuint GLASS_B_SIDE       = 97;
constexpr GLuint RUSTY_MAN          = 98;
constexpr GLuint NO_SMOKE_SIGN      = 99;
constexpr GLuint CARPET             = 100;
// Drinks Machine Textures
constexpr GLuint DRINKS_SIDE     = 101;
constexpr GLuint DRINKS_TOP      = 102;
constexpr GLuint DRINKS_EDGE     = 103;
constexpr GLuint DRINKS_SIDE_2   = 104;
constexpr GLuint COKE_MACHINE    = 105;
constexpr GLuint COFFEE_MACHINE  = 106;
constexpr GLuint SWEET_MACHINE   = 107;
constexpr GLuint MACHINE_SIDES   = 108;
constexpr GLuint MACHINE_SIDES_2 = 109;
// Telephone Box Textures
constexpr GLuint TELEPHONE_BACK      = 110;
constexpr GLuint TELEPHONE_FRONT     = 111;
constexpr GLuint TELEPHONE_SIDE_1    = 112;
constexpr GLuint TELEPHONE_FRONT_2   = 113;
constexpr GLuint TELEPHONE_MAIN_SIDE = 114;
constexpr GLuint TELEPHONE_TOP_1     = 115;
constexpr GLuint TELEPHONE_SIDE_2    = 116;
constexpr GLuint TELEPHONE_TOP_2     = 117;
constexpr GLuint TELEPHONE_BOTTOM    = 118;
constexpr GLuint TELEPHONE_FILL      = 119;
constexpr GLuint TELEPHONE_FRONT_3   = 120;
// Step Textures
constexpr GLuint STEPS_LIBRARY     = 121;
constexpr GLuint STEPS_LIBRARY_TOP = 122;
constexpr GLuint STEP_PAVING_1     = 123;
constexpr GLuint STEP_EDGE         = 124;

// Larger Window and Door Textures Etc
constexpr GLuint WINDOW_1          = 125;
constexpr GLuint WINDOW_2          = 126;
constexpr GLuint WINDOW_3          = 127;
constexpr GLuint WINDOW_4          = 128;
constexpr GLuint WINDOW_5          = 129;
constexpr GLuint WINDOW_6          = 130;
constexpr GLuint WINDOW_7          = 131;
constexpr GLuint WINDOW_8          = 132;
constexpr GLuint WINDOW_9          = 133;
constexpr GLuint WINDOW_10         = 134;
constexpr GLuint WINDOW_11         = 135;
constexpr GLuint WINDOW_12         = 136;
constexpr GLuint WINDOW_13         = 137;
constexpr GLuint WINDOW_14         = 138;
constexpr GLuint WINDOW_14B        = 139;
constexpr GLuint WINDOW_15         = 140;
constexpr GLuint WINDOW_16         = 141;
constexpr GLuint WINDOW_17         = 142;
constexpr GLuint WINDOW_2B         = 143;
constexpr GLuint WINDOW_2C         = 144;
constexpr GLuint WINDOW_2US        = 145;
constexpr GLuint WINDOW_3B         = 146;
constexpr GLuint WINDOW_2USB       = 147;
constexpr GLuint WINDOW_LIB_1      = 148;
constexpr GLuint WINDOW_LIB_1A     = 149;
constexpr GLuint WINDOW_LIB_1B     = 150;
constexpr GLuint WINDOW_LIB_1C     = 151;
constexpr GLuint WINDOW_LIB_US_A   = 152;
constexpr GLuint WINDOW_LIB_US_B   = 153;
constexpr GLuint WINDOW_LIB_DOOR_1 = 154;
constexpr GLuint WINDOW_LIB_DOOR_2 = 155;
constexpr GLuint WINDOW_LIB_LONG   = 156;
constexpr GLuint ENTRANCE          = 157;
constexpr GLuint ENTRANCE_2        = 158;
constexpr GLuint EXIT_EAST         = 159;
constexpr GLuint EXIT_WEST         = 220;
constexpr GLuint CHANC_DOOR_1      = 160;
constexpr GLuint CHANC_DOOR_2      = 161;
constexpr GLuint WINDOW_2D         = 162;
constexpr GLuint WINDOW_2E         = 163;
constexpr GLuint WINDOW_1B         = 164;
constexpr GLuint STEP_WINDOW       = 221;

// Above Window Block Textures
constexpr GLuint ABOVE_WINDOW_BLOCK       = 165;
constexpr GLuint ABOVE_WINDOW_BLOCK_2     = 166;
constexpr GLuint ABOVE_WINDOW_BLOCK_3     = 167;
constexpr GLuint ABOVE_WINDOW_EDGE_3B     = 168;
constexpr GLuint ABOVE_WINDOW_BLOCK_XY_3  = 169;
constexpr GLuint ABOVE_LIB                = 170;
constexpr GLuint ABOVE_UNDER_POSTS        = 171;
constexpr GLuint ABOVE_UNDER_POSTS_2      = 172;
constexpr GLuint ABOVE_WINDOW_UNDER_LIB   = 173;
constexpr GLuint ABOVE_WINDOW_BLOCK_CHANC = 174;
constexpr GLuint ABOVE_WINDOW_EDGE_3B_LIB = 175;
constexpr GLuint ABOVE_WINDOW_EDGE_4B_LIB = 176;
constexpr GLuint ABOVE_UNDER_4B           = 177;
constexpr GLuint ABOVE_CHANC_TEXT         = 178;
constexpr GLuint ABOVE_CHANC_TEXT_2       = 179;
constexpr GLuint ABOVE_PHYS_SCI_TEXT      = 180;
constexpr GLuint ABOVE_CHANC_TEXT_3       = 181;
constexpr GLuint ABOVE_LIB_TEXT           = 182;
constexpr GLuint ABOVE_LIB_TEXT_2         = 183;
constexpr GLuint ABOVE_TICKETS_TEXT       = 184;
constexpr GLuint ABOVE_CHANC_EDGE         = 185;
constexpr GLuint TOILET_DOOR_TOP          = 186;
// Light Fitting Textures
constexpr GLuint LIGHT           = 187;
constexpr GLuint LIGHT_SUPPORT   = 188;
constexpr GLuint LIGHT_SUPPORT_2 = 189;
// Bench Textures
constexpr GLuint BENCH_TOP        = 190;
constexpr GLuint BENCH_SIDE       = 191;
constexpr GLuint BENCH_SIDE_2     = 192;
constexpr GLuint BENCH_EDGE       = 193;
constexpr GLuint BENCH_EDGE_TOP   = 194;
constexpr GLuint BENCH_EDGE_SIDE  = 195;
constexpr GLuint BENCH_EDGE_TOP_2 = 196;
constexpr GLuint BENCH_EDGE_2     = 197;
constexpr GLuint BENCH_EDGE_3     = 198;
// Ticket Counter and Ledge Textures
constexpr GLuint TICKET_COUNTER_TOP    = 200;
constexpr GLuint TICKET_COUNTER_EDGE   = 201;
constexpr GLuint TICKET_COUNTER_EDGE_2 = 202;
constexpr GLuint TICKET_COUNTER_EDGE_3 = 203;
constexpr GLuint TICKET_LEDGE          = 204;
constexpr GLuint TICKET_LEDGE_EDGE     = 205;
constexpr GLuint TICKET_LEDGE_EDGE_2   = 206;
// Wall by Steps Textures
constexpr GLuint WALL_BRICK_STEPS_TOP    = 207;
constexpr GLuint WALL_BRICK_STEPS        = 208;
constexpr GLuint WALL_BRICK_STEPS_COVER  = 209;
constexpr GLuint WALL_BRICK_STEPS_EDGE   = 210;
constexpr GLuint WALL_BRICK_STEPS_EDGE_2 = 211;
// Extra Textures
constexpr GLuint DRAINPIPE    = 212;
constexpr GLuint COUNTER_TOP  = 213;
constexpr GLuint COUNTER_SIDE = 214;
// Welcome, Exit and Map Screens
constexpr GLuint MAP     = 217;
constexpr GLuint WELCOME = 218;
constexpr GLuint EXIT    = 219;
constexpr GLuint NO_EXIT = 222;


static GLfloat stepIncrement  = 0.0f;
static GLfloat angleIncrement = 0.0f;
static int frameCount         = 0;
static clock_t lastClock{};

// ratio of screen
// screen width and height
// TODO: Strip shays code
static int width = 1280, height = 720;
static float ratio = static_cast<double>(width) / static_cast<double>(height);

// display campus map
static bool DisplayMap = false;
// display welcome screen
static bool DisplayWelcome = true;
// display exit screen
static bool DisplayExit = false;
// display light fittings
static bool lightsOn = false;
// display ECL block
static bool displayECL = true;
// display debug menu
static bool displayDebug = true;
// current fps
static int calcFPS = 0;

// varibles used for tarnslating graphics etc
static GLfloat step       = 0.0f;
static GLfloat step2      = 0.0f;
static GLfloat stepLength = 0.0f;

// Glut Cylinder
static GLUquadricObj *glu_cylinder = nullptr;

// Stores raw image file
static unsigned char *image = nullptr;

// objects

static Camera cam;
static TexturedPolygons tp;


class Shay {
  public:

	void myinit();
    void Display();
    // calls display functions below to draw the backdrops
    void DrawBackdrop();
    // functions to display display lists (images) and bind them to a texture
    void DisplayAboveWindowBlock();
    void DisplayBench();
    void DisplayBricks();
    void DisplayChancPosts();
    void DisplayCylinders();
    void DisplayDoorPaving();
    void DisplayDoorPosts();
    void DisplayEntranceSteps();
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
    void DisplayLights();
    void DisplayECL();

    // calls functions to create display lists (below)
    void CreateTextureList();
    // creates display lists
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
    void DrawLargerTextures();
    void DrawLights();
    void DrawBench();
    void DrawCylinders();
    void DrawAngledRoofBeam(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                            GLfloat beamSize);
    void DrawAngledRoofBeam2(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                             GLfloat beamSize);
    void DrawStepBricks();
    void DrawMapExit();
    void DrawECL();

    void BindBridgeWall(GLint LR);
    void BindBuildingWall();
    void BindWallPosts(GLint LR);

    void IncrementFrameCount();

    // loads images and creates texture
    void CreateTextures();
    // creates bounding boxes for collsion detection
    void CreateBoundingBoxes();
    // creates different plains
    void CreatePlains();

    // deletes image and clears memory
    void DeleteImageFromMemory(unsigned char *tempImage);

};