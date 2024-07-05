/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectiv(const GLint* v1,
                                  const GLint* v2)
{
    AI_TRACE("glRectiv(v1=[%p], v2=[%p])",
             v1,
             v2);

    reinterpret_cast<PFNGLRECTIVPROC>(OpenGL::g_cached_gl_rect_iv)(v1,
                                                                   v2);
}