#pragma once

#include <SDL2/SDL_opengl.h>

// initializes setting
void myinit();

// display functions
void Display();
void reshape(int w, int h);
void keys(unsigned char key, int x, int y);

// keyboard and mouse functions
void movementKeys(int key, int x, int y);
void releaseKey(int key, int x, int y);
void releaseKeys(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);

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
