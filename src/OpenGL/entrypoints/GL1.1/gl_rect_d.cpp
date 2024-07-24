/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectd(GLdouble x1,
                                 GLdouble y1,
                                 GLdouble x2,
                                 GLdouble y2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRectd(x1=[%.4lf], y1=[%.4lf], x2=[%.4lf], y2=[%.4lf])",
             x1,
             y1,
             x2,
             y2);

    reinterpret_cast<PFNGLRECTDPROC>(OpenGL::g_cached_gl_rect_d)(x1,
                                                                 y1,
                                                                 x2,
                                                                 y2);
}