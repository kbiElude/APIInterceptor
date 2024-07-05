/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fi.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferfi(GLenum  buffer,
                                         GLint   drawbuffer,
                                         GLfloat depth,
                                         GLint   stencil)
{
    AI_TRACE("glClearBufferfi(buffer=[%s] drawbuffer=[%d] depth=[%.4f] stencil=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
             depth,
             stencil);

    if (OpenGL::g_cached_gl_clear_buffer_fi == nullptr)
    {
        OpenGL::g_cached_gl_clear_buffer_fi = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearBufferfi");
    }

    reinterpret_cast<PFNGLCLEARBUFFERFIPROC>(OpenGL::g_cached_gl_clear_buffer_fi)(buffer,
                                                                                  drawbuffer,
                                                                                  depth,
                                                                                  stencil);
}