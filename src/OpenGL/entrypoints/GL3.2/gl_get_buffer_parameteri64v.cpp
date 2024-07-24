/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_get_buffer_parameteri64v.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBufferParameteri64v(GLenum   target,
                                                  GLenum   pname,
                                                  GLint64* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetBufferParameteri64v(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_buffer_parameteri64v == nullptr)
    {
        OpenGL::g_cached_gl_get_buffer_parameteri64v = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetBufferParameteri64v");
    }

    reinterpret_cast<PFNGLGETBUFFERPARAMETERI64VPROC>(OpenGL::g_cached_gl_get_buffer_parameteri64v)(target,
                                                                                                    pname,
                                                                                                    params);
}