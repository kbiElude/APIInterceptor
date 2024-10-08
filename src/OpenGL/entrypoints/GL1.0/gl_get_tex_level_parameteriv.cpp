/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexLevelParameteriv(GLenum target,
                                                  GLint  level,
                                                  GLenum pname,
                                                  GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTexLevelParameteriv(target=[%s] level=[%d] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>(OpenGL::g_cached_gl_get_tex_level_parameteriv)(target,
                                                                                                     level,
                                                                                                     pname,
                                                                                                     params);
}