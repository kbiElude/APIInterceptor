/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4fv(const GLfloat* v)
{
    AI_TRACE("glColor4fv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR4FVPROC>(OpenGL::g_cached_gl_color_4fv)(v);
}