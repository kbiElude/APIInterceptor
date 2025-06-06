/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_renderbuffer_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetRenderbufferParameteriv(GLenum target,
                                                      GLenum pname,
                                                      GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetRenderbufferParameteriv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(OpenGL::g_cached_gl_get_renderbuffer_parameteriv)(target,
                                                                                                            pname,
                                                                                                            params);
}