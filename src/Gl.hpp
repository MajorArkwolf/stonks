#pragma once

#if defined(__APPLE__)
#    define GL_SILENCE_DEPRECATION
#endif

#if __has_include(<GL/gl.h>)
#    include <GL/gl.h>
#    include <GL/glu.h>
#elif __has_include(<OpenGL/gl.h>)
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#endif
