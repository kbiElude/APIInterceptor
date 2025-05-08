/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexParameterIuiv(GLenum  target,
                                               GLenum  pname,
                                               GLuint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTexParameterIuiv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_tex_parameter_i_uiv == nullptr)
    {
    }

    reinterpret_cast<PFNGLGETTEXPARAMETERIUIVPROC>(OpenGL::g_cached_gl_get_tex_parameter_i_uiv)(target,
                                                                                                pname,
                                                                                                params);
}