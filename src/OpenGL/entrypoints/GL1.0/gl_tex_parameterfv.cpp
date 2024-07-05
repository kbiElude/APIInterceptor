/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameterfv(GLenum         target,
                                          GLenum         pname,
                                          const GLfloat* params)
{
    const auto dispatch_table_ptr = OpenGL::g_dispatch_table_ptr;

    AI_TRACE("glTexParameterfv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_tex_parameterfv == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameterfv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameterfv");
    }

    reinterpret_cast<PFNGLTEXPARAMETERFVPROC>(OpenGL::g_cached_gl_tex_parameterfv)(target,
                                                                                   pname,
                                                                                   params);
}