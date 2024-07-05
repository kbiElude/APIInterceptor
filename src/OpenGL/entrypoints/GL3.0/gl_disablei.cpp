/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_disablei.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDisablei(GLenum target,
                                    GLuint index)
{
    AI_TRACE("glDisablei(target=[%s] index=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index);

    if (OpenGL::g_cached_gl_disablei == nullptr)
    {
        OpenGL::g_cached_gl_disablei = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDisablei");
    }

    reinterpret_cast<PFNGLDISABLEIPROC>(OpenGL::g_cached_gl_disablei)(target,
                                                                      index);
}