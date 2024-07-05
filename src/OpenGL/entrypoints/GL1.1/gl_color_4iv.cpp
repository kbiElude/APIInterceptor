/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4iv(const GLint* v)
{
    AI_TRACE("glColor4iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR4IVPROC>(OpenGL::g_cached_gl_color_4iv)(v);
}