/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_ortho.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiOrtho(GLdouble left,
                                 GLdouble right,
                                 GLdouble bottom,
                                 GLdouble top,
                                 GLdouble zNear,
                                 GLdouble zFar)
{
    AI_TRACE("glOrtho(left=[%.4lf] right=[%.4lf] bottom=[%.4lf] top=[%.4lf] zNear=[%.4lf] zFar=[%.4lf])",
             left,
             right,
             bottom,
             top,
             zNear,
             zFar);

    reinterpret_cast<PFNGLORTHOPROC>(OpenGL::g_cached_gl_ortho)(left,
                                                                right,
                                                                bottom,
                                                                top,
                                                                zNear,
                                                                zFar);
}