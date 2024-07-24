/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferiv(GLenum       buffer,
                                         GLint        drawbuffer,
                                         const GLint* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClearBufferiv(buffer=[%s] drawbuffer=[%d] *value=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
             *value);

    if (OpenGL::g_cached_gl_clear_buffer_iv == nullptr)
    {
        OpenGL::g_cached_gl_clear_buffer_iv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearBufferfv");
    }

    reinterpret_cast<PFNGLCLEARBUFFERIVPROC>(OpenGL::g_cached_gl_clear_buffer_iv)(buffer,
                                                                                  drawbuffer,
                                                                                  value);
}