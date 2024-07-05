/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_clear_stencil.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearStencil(GLint s)
{
    AI_TRACE("glClearStencil(s=[%d])",
             s);

    if (OpenGL::g_cached_gl_clear_stencil == nullptr)
    {
        OpenGL::g_cached_gl_clear_stencil = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearStencil");
    }

    reinterpret_cast<PFNGLCLEARSTENCILPROC>(OpenGL::g_cached_gl_clear_stencil)(s);
}