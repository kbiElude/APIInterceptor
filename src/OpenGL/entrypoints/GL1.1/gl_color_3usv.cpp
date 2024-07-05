/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3usv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3usv(const GLushort* v)
{
    AI_TRACE("glColor3usv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR3USVPROC>(OpenGL::g_cached_gl_color_3usv)(v);
}