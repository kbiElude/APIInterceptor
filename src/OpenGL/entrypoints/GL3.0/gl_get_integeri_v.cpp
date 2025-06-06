/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_integeri_v.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetIntegeri_v(GLenum target,
                                         GLuint index,
                                         GLint* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetIntegeri_v(target=[%s] index=[%u] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             data);

    reinterpret_cast<PFNGLGETINTEGERI_VPROC>(OpenGL::g_cached_gl_get_integeri_v)(target,
                                                                                 index,
                                                                                 data);
}