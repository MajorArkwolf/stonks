#pragma once

#if __APPLE__
#    define GL_SILENCE_DEPRECATION
#endif

#if __has_include(<GL/glut.h>)
#    include <GL/glut.h>
#elif __has_include(<GLUT/glut.h>)
#    include <GLUT/glut.h>
#endif

#if __APPLE__
#    include <ApplicationServices/ApplicationServices.h>
#elif _WIN32
/* windows.h *helpfully* declares a macro for near and far. */
#    undef near
#    undef far

/* Windows GLUT doesn't have the normal BGR. */
#    ifndef GL_BGR
#        define GL_BGR GL_BGR_EXT
#    endif
#endif
