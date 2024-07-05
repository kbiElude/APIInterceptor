/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_scissor.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiScissor(GLint   x,
                                   GLint   y,
                                   GLsizei width,
                                   GLsizei height)
{
    AI_TRACE("glScissor(x=[%d] y=[%d] width=[%d] height=[%d])",
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    if (OpenGL::g_cached_gl_scissor == nullptr)
    {
        OpenGL::g_cached_gl_scissor = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glScissor");
    }

    reinterpret_cast<PFNGLSCISSORPROC>(g_cached_gl_scissor)(x,
                                                            y,
                                                            width,
                                                            height);
}