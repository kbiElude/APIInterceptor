/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2i(GLint x,
                                    GLint y)
{
    AI_TRACE("glVertex2i(x=[%d], y=[%d])",
             x,
             y);

    reinterpret_cast<PFNGLVERTEX2IPROC>(OpenGL::g_cached_gl_vertex_2i)(x,
                                                                       y);
}