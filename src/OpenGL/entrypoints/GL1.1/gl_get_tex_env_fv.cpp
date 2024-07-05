/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_env_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexEnvfv(GLenum   target,
                                       GLenum   pname,
                                       GLfloat* params)
{
    AI_TRACE("glGetTexEnvfv(target=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETTEXENVFVPROC>(OpenGL::g_cached_gl_get_tex_env_fv)(target,
                                                                               pname,
                                                                               params);
}