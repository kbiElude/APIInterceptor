/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4dv(const GLdouble* v)
{
    AI_TRACE("glColor4dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR4DVPROC>(OpenGL::g_cached_gl_color_4dv)(v);
}