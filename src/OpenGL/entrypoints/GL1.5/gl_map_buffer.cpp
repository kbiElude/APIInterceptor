/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void *APIENTRY OpenGL::aiMapBuffer(GLenum target,
                                   GLenum access)
{
    AI_TRACE("glMapBuffer(target=[%s] access=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(access) );

    if (OpenGL::g_cached_gl_map_buffer == nullptr)
    {
        OpenGL::g_cached_gl_map_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glMapBuffer");
    }

    return reinterpret_cast<PFNGLMAPBUFFERPROC>(OpenGL::g_cached_gl_map_buffer)(target,
                                                                                access);
}
