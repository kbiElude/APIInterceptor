/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64v.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetInteger64v(GLenum   pname,
                                         GLint64* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetInteger64v(pname=[%s] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    reinterpret_cast<PFNGLGETINTEGER64VPROC>(OpenGL::g_cached_gl_get_integer64v)(pname,
                                                                                 data);
}