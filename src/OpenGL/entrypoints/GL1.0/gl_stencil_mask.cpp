/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_stencil_mask.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilMask(GLuint mask)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glStencilMask(mask=[%u])",
             mask);

    if (OpenGL::g_cached_gl_stencil_mask == nullptr)
    {
        OpenGL::g_cached_gl_stencil_mask = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glStencilMask");
    }

    reinterpret_cast<PFNGLSTENCILMASKPROC>(g_cached_gl_stencil_mask)(mask);
}