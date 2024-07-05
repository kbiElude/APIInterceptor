/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_get_multisamplefv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetMultisamplefv(GLenum   pname,
                                            GLuint   index,
                                            GLfloat* val)
{
    AI_TRACE("glGetMultisamplefv(pname=[%s] index=[%u] val=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             index,
             val);

    if (OpenGL::g_cached_gl_get_multisamplefv == nullptr)
    {
        OpenGL::g_cached_gl_get_multisamplefv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetMultisamplefv");
    }

    reinterpret_cast<PFNGLGETMULTISAMPLEFVPROC>(OpenGL::g_cached_gl_get_multisamplefv)(pname,
                                                                                       index,
                                                                                       val);
}