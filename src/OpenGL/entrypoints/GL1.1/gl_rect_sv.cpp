/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rect_sv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectsv(const GLshort* v1,
                                  const GLshort* v2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRectsv(v1=[%p], v2=[%p])",
             v1,
             v2);

    reinterpret_cast<PFNGLRECTSVPROC>(OpenGL::g_cached_gl_rect_sv)(v1,
                                                                   v2);
}