#pragma once

#include <SDL2/SDL_opengl.h>

#if __has_include(<OpenGL/glu.h>)
#    include <OpenGL/glu.h>
#else
#    include <GL/glu.h>
#endif
