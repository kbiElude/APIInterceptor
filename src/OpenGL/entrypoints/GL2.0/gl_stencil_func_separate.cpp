/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_stencil_func_separate.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilFuncSeparate(GLenum face,
                                               GLenum func,
                                               GLint  ref,
                                               GLuint mask)
{
    AI_TRACE("glStencilFuncSeparate(face=[%s] func=[%s] ref=[%d] mask=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref,
             mask);

    if (OpenGL::g_cached_gl_stencil_func_separate == nullptr)
    {
        OpenGL::g_cached_gl_stencil_func_separate = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glStencilFuncSeparate");
    }

    reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>(g_cached_gl_stencil_func_separate)(face,
                                                                                      func,
                                                                                      ref,
                                                                                      mask);
}