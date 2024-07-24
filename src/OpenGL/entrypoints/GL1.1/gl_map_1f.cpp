/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_1f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMap1f(GLenum         target,
                                 GLfloat        u1,
                                 GLfloat        u2,
                                 GLint          stride,
                                 GLint          order,
                                 const GLfloat* points)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMap1f(target=[%s], u1=[%f], u2=[%f], stride=[%d], order=[%d], points=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             u1,
             u2,
             stride,
             order,
             points);

    reinterpret_cast<PFNGLMAP1FPROC>(OpenGL::g_cached_gl_map_1f)(target,
                                                                 u1,
                                                                 u2,
                                                                 stride,
                                                                 order,
                                                                 points);
}