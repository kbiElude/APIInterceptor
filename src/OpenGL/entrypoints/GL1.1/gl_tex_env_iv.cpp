/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexEnviv(GLenum       target,
                                    GLenum       pname,
                                    const GLint* params)
{
    AI_TRACE("glTexEnviv(target=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLTEXENVIVPROC>(OpenGL::g_cached_gl_tex_env_iv)(target,
                                                                        pname,
                                                                        params);
}