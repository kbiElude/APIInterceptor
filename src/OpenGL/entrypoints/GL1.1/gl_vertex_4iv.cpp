/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4iv(const GLint* v)
{
    AI_TRACE("glVertex4iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLVERTEX4IVPROC>(OpenGL::g_cached_gl_vertex_4iv)(v);
}