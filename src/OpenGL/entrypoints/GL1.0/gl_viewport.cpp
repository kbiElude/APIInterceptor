/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_viewport.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiViewport(GLint   x,
                                    GLint   y,
                                    GLsizei width,
                                    GLsizei height)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glViewport(x=[%d] y=[%d] width=[%d] height=[%d])",
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    if (OpenGL::g_cached_gl_viewport == nullptr)
    {
        OpenGL::g_cached_gl_viewport = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glViewport");
    }

    reinterpret_cast<PFNGLVIEWPORTPROC>(OpenGL::g_cached_gl_viewport)(x,
                                                                      y,
                                                                      width,
                                                                      height);
}