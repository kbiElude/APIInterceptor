/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4uiv(const GLuint* v)
{
    AI_TRACE("glColor4uiv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR4UIVPROC>(OpenGL::g_cached_gl_color_4uiv)(v);
}