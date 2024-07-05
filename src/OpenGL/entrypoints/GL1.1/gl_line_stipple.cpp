/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_line_stipple.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLineStipple(GLint    factor,
                                       GLushort pattern)
{
    AI_TRACE("glLineStipple(factor=[%d], pattern=[%d])",
             factor,
             static_cast<uint32_t>(pattern) );

    reinterpret_cast<PFNGLLINESTIPPLEPROC>(OpenGL::g_cached_gl_line_stipple)(factor,
                                                                             pattern);
}