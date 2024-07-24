/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectf(GLfloat x1,
                                 GLfloat y1,
                                 GLfloat x2,
                                 GLfloat y2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRectf(x1=[%.4f], y1=[%.4f], x2=[%.4f], y2=[%.4f])",
             x1,
             y1,
             x2,
             y2);

    reinterpret_cast<PFNGLRECTFPROC>(OpenGL::g_cached_gl_rect_f)(x1,
                                                                 y1,
                                                                 x2,
                                                                 y2);
}