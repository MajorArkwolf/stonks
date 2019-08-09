#pragma once

#if defined(__APPLE__)
#    define GL_SILENCE_DEPRECATION
#endif

#if __has_include(<OpenGL/gl.h>)
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#else
#    include <GL/gl.h>
#    include <GL/glu.h>
#endif

#if defined(_WIN32)
#    include <windows.h>
/* windows.h *helpfully* defines a macro for near and far. */
#    undef near
#    undef far

/* Windows GLUT doesn't have the normal BGR. */
#    ifndef GL_BGR
#        define GL_BGR GL_BGR_EXT
#    endif
#endif
