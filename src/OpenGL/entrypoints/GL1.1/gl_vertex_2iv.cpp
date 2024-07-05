/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2iv(const GLint* v)
{
    AI_TRACE("glVertex2iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLVERTEX2IVPROC>(OpenGL::g_cached_gl_vertex_2iv)(v);
}