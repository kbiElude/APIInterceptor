/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2s(GLshort x,
                                    GLshort y)
{
    AI_TRACE("glVertex2s(x=[%d], y=[%d])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y) );

    reinterpret_cast<PFNGLVERTEX2SPROC>(OpenGL::g_cached_gl_vertex_2s)(x,
                                                                       y);
}