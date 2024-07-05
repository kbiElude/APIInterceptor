/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3s(GLshort x,
                                    GLshort y,
                                    GLshort z)
{
    AI_TRACE("glVertex3s(x=[%d], y=[%d], z=[%d])",
             static_cast<int32_t>(x),
             static_cast<int32_t>(y),
             static_cast<int32_t>(z) );

    reinterpret_cast<PFNGLVERTEX3SPROC>(OpenGL::g_cached_gl_vertex_3s)(x,
                                                                       y,
                                                                       z);
}