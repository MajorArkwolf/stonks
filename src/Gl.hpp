#pragma once

#if defined(__APPLE__)
#    define GL_SILENCE_DEPRECATION
#endif

#if __has_include(<OpenGL/gl.h>)
#    include <OpenGL/gl.h>
#    include <OpenGL/glu.h>
#elif __has_include(<GL/gl.h>)
#    include <GL/gl.h>
#    include <GL/glu.h>
#endif

#if __has_include(<OpenGLES/ES2/gl.h>)
#    include <OpenGLES/ES2/gl.h>
#elif __has_include(<EGL/egl.h>)
#    include <EGL/egl.h>
#    include <GLES2/gl2.h>
#endif
