/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferData(GLenum      target,
                                      GLsizeiptr  size,
                                      const void* data,
                                      GLenum      usage)
{
    AI_TRACE("glBufferData(target=[%s] size=[%d] data=[%p] usage=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<uint32_t>(size),
             data,
             OpenGL::Utils::get_raw_string_for_gl_enum(usage) );

    if (OpenGL::g_cached_gl_blit_framebuffer == nullptr)
    {
        OpenGL::g_cached_gl_blit_framebuffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlitFramebuffer");
    }

    reinterpret_cast<PFNGLBUFFERDATAPROC>(OpenGL::g_cached_gl_buffer_data)(target,
                                                                           size,
                                                                           data,
                                                                           usage);
}