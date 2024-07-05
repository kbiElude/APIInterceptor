/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRecti(GLint x1,
                                 GLint y1,
                                 GLint x2,
                                 GLint y2)
{
    AI_TRACE("glRecti(x1=[%d], y1=[%d], x2=[%d], y2=[%d])",
             x1,
             y1,
             x2,
             y2);

    reinterpret_cast<PFNGLRECTIPROC>(OpenGL::g_cached_gl_rect_i)(x1,
                                                                 y1,
                                                                 x2,
                                                                 y2);
}