/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_map_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMap2d(GLenum          target,
                                 GLdouble        u1,
                                 GLdouble        u2,
                                 GLint           ustride,
                                 GLint           uorder,
                                 GLdouble        v1,
                                 GLdouble        v2,
                                 GLint           vstride,
                                 GLint           vorder,
                                 const GLdouble* points)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMap2d(target=[%s], u1=[%lf], u2=[%lf], ustride=[%d], uorder=[%d], v1=[%lf], v2=[%lf], vstride=[%d], vorder=[%d], points=[%p])",
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

    reinterpret_cast<PFNGLMAP2DPROC>(OpenGL::g_cached_gl_map_2d)(target,
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