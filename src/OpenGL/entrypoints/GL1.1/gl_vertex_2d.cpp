/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2d(GLdouble x,
                                    GLdouble y)
{
    AI_TRACE("glVertex2d(x=[%.4lf], y=[%.4lf])",
             x,
             y);

    reinterpret_cast<PFNGLVERTEX2DPROC>(OpenGL::g_cached_gl_vertex_2d)(x,
                                                                       y);
}