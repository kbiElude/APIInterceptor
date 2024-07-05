/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_booleanv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBooleanv(GLenum     pname,
                                       GLboolean* data)
{
    AI_TRACE("glGetBooleanv(pname=[%s] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    if (OpenGL::g_cached_gl_get_booleanv == nullptr)
    {
        OpenGL::g_cached_gl_get_booleanv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetBooleanv");
    }

    reinterpret_cast<PFNGLGETBOOLEANVPROC>(OpenGL::g_cached_gl_get_booleanv)(pname,
                                                                             data);
}