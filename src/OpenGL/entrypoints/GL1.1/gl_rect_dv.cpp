/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectdv(const GLdouble* v1,
                                  const GLdouble* v2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRectdv(v1=[%p], v2=[%p])",
             v1,
             v2);

    reinterpret_cast<PFNGLRECTDVPROC>(OpenGL::g_cached_gl_rect_dv)(v1,
                                                                   v2);
}