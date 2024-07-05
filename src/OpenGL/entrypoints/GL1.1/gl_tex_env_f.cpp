/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexEnvf(GLenum  target,
                                   GLenum  pname,
                                   GLfloat param)
{
    AI_TRACE("glTexEnvf(target=[%s], pname=[%s], param=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    reinterpret_cast<PFNGLTEXENVFPROC>(OpenGL::g_cached_gl_tex_env_f)(target,
                                                                      pname,
                                                                      param);
}