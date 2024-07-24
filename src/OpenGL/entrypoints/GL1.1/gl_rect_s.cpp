/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRects(GLshort x1,
                                 GLshort y1,
                                 GLshort x2,
                                 GLshort y2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRects(x1=[%d], y1=[%d], x2=[%d], y2=[%d])",
             static_cast<int32_t>(x1),
             static_cast<int32_t>(y1),
             static_cast<int32_t>(x2),
             static_cast<int32_t>(y2) );

    reinterpret_cast<PFNGLRECTSPROC>(OpenGL::g_cached_gl_rect_s)(x1,
                                                                 y1,
                                                                 x2,
                                                                 y2);
}