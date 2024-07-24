/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_pointerv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBufferPointerv(GLenum target,
                                             GLenum pname,
                                             void** params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetBufferPointerv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_buffer_pointerv == nullptr)
    {
        OpenGL::g_cached_gl_get_buffer_pointerv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetBufferPointerv");
    }

    reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(OpenGL::g_cached_gl_get_buffer_pointerv)(target,
                                                                                          pname,
                                                                                          params);
}