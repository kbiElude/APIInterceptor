/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_booleani_v.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBooleani_v(GLenum     target,
                                         GLuint     index,
                                         GLboolean* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetBooleani_v(target=[%s] index=[%u] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             data);

    reinterpret_cast<PFNGLGETBOOLEANI_VPROC>(OpenGL::g_cached_gl_get_booleani_v)(target,
                                                                                 index,
                                                                                 data);
}