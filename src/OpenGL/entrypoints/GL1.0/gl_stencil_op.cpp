/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_stencil_op.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilOp(GLenum fail,
                                     GLenum zfail,
                                     GLenum zpass)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glStencilOp(fail=[%s] zfail=[%s] zpass=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(fail),
             OpenGL::Utils::get_raw_string_for_gl_enum(zfail),
             OpenGL::Utils::get_raw_string_for_gl_enum(zpass) );

    if (OpenGL::g_cached_gl_stencil_op == nullptr)
    {
        OpenGL::g_cached_gl_stencil_op = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glStencilOp");
    }

    reinterpret_cast<PFNGLSTENCILOPPROC>(g_cached_gl_stencil_op)(fail,
                                                                 zfail,
                                                                 zpass);
}