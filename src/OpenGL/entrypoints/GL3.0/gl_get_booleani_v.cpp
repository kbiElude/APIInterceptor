/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_booleani_v.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBooleani_v(GLenum     target,
                                         GLuint     index,
                                         GLboolean* data)
{
    AI_TRACE("glGetBooleani_v(target=[%s] index=[%u] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             data);

    if (OpenGL::g_cached_gl_get_booleani_v == nullptr)
    {
        OpenGL::g_cached_gl_get_booleani_v = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetBooleani_v");
    }

    reinterpret_cast<PFNGLGETBOOLEANI_VPROC>(OpenGL::g_cached_gl_get_booleani_v)(target,
                                                                                 index,
                                                                                 data);
}