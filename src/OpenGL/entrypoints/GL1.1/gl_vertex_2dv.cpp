/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2dv(const GLdouble* v)
{
    AI_TRACE("glVertex2dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLVERTEX2DVPROC>(OpenGL::g_cached_gl_vertex_2dv)(v);
}