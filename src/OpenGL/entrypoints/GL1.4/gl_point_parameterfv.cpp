/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameterfv(GLenum         pname,
                                            const GLfloat* params)
{
    AI_TRACE("glPointParameterfv(pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_point_parameterfv == nullptr)
    {
        OpenGL::g_cached_gl_point_parameterfv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPointParameterfv");
    }

    reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(g_cached_gl_point_parameterfv)(pname,
                                                                               params);
}