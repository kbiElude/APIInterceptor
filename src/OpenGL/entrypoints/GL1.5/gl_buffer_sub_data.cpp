/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferSubData(GLenum     target,
                                         GLintptr   offset,
                                         GLsizeiptr size,
                                         void*      data)
{
    AI_TRACE("glBufferSubData(target=[%s] offset=[%d] size=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<uint32_t>(offset),
             static_cast<uint32_t>(size),
             data);

    if (OpenGL::g_cached_gl_buffer_sub_data == nullptr)
    {
        OpenGL::g_cached_gl_buffer_sub_data = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBufferSubData");
    }

    reinterpret_cast<PFNGLBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_buffer_sub_data)(target,
                                                                                  offset,
                                                                                  size,
                                                                                  data);
}