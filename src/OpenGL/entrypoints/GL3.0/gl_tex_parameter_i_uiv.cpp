/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameterIuiv(GLenum        target,
                                            GLenum        pname,
                                            const GLuint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexParameterIuiv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLTEXPARAMETERIUIVPROC>(OpenGL::g_cached_gl_tex_parameter_i_uiv)(target,
                                                                                         pname,
                                                                                         params);
}