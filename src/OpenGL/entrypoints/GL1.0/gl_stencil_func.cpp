/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilFunc(GLenum func,
                                       GLint  ref,
                                       GLuint mask)
{
    AI_TRACE("glStencilFunc(func=[%s] ref=[%d] mask=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref,
             mask);

    if (OpenGL::g_cached_gl_stencil_func == nullptr)
    {
        OpenGL::g_cached_gl_stencil_func = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glStencilFunc");
    }

    reinterpret_cast<PFNGLSTENCILFUNCPROC>(g_cached_gl_stencil_func)(func,
                                                                     ref,
                                                                     mask);
}