/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferuiv(GLenum        buffer,
                                          GLint         drawbuffer,
                                          const GLuint* value)
{
    AI_TRACE("glClearBufferuiv(buffer=[%s] drawbuffer=[%d] *value=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
            *value);

    if (OpenGL::g_cached_gl_clear_buffer_uiv == nullptr)
    {
        OpenGL::g_cached_gl_clear_buffer_uiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearBufferuiv");
    }

    reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>(OpenGL::g_cached_gl_clear_buffer_uiv)(buffer,
                                                                                    drawbuffer,
                                                                                    value);
}