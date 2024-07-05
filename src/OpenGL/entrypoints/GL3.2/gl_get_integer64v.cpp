/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64v.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetInteger64v(GLenum   pname,
                                         GLint64* data)
{
    AI_TRACE("glGetInteger64v(pname=[%s] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    if (OpenGL::g_cached_gl_get_integer64v == nullptr)
    {
        OpenGL::g_cached_gl_get_integer64v = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetInteger64v");
    }

    reinterpret_cast<PFNGLGETINTEGER64VPROC>(OpenGL::g_cached_gl_get_integer64v)(pname,
                                                                                 data);
}