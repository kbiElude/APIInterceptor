/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferfv(GLenum         buffer,
                                         GLint          drawbuffer,
                                         const GLfloat* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClearBufferfv(buffer=[%s] drawbuffer=[%d] *value=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
            *value);

    if (OpenGL::g_cached_gl_clear_buffer_fv == nullptr)
    {
        OpenGL::g_cached_gl_clear_buffer_fv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearBufferfv");
    }

    reinterpret_cast<PFNGLCLEARBUFFERFVPROC>(OpenGL::g_cached_gl_clear_buffer_fv)(buffer,
                                                                                  drawbuffer,
                                                                                  value);
}