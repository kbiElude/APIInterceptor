/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMap2f(GLenum         target,
                                 GLfloat        u1,
                                 GLfloat        u2,
                                 GLint          ustride,
                                 GLint          uorder,
                                 GLfloat        v1,
                                 GLfloat        v2,
                                 GLint          vstride,
                                 GLint          vorder,
                                 const GLfloat* points)
{
    AI_TRACE("glMap2f(target=[%s], u1=[%f], u2=[%f], ustride=[%d], uorder=[%d], v1=[%f], v2=[%f], vstride=[%d], vorder=[%d], points=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             u1,
             u2,
             ustride,
             uorder,
             v1,
             v2,
             vstride,
             vorder,
             points);

    reinterpret_cast<PFNGLMAP2FPROC>(OpenGL::g_cached_gl_map_2f)(target,
                                                                 u1,
                                                                 u2,
                                                                 ustride,
                                                                 uorder,
                                                                 v1,
                                                                 v2,
                                                                 vstride,
                                                                 vorder,
                                                                 points);
}