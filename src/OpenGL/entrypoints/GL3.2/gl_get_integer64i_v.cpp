/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64i_v.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetInteger64i_v(GLenum   target,
                                           GLuint   index,
                                           GLint64* data)
{
    AI_TRACE("glGetInteger64i_v(target=[%s] index=[%u] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             data);

    if (OpenGL::g_cached_gl_get_integer64i_v == nullptr)
    {
        OpenGL::g_cached_gl_get_integer64i_v = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetInteger64i_v");
    }

    reinterpret_cast<PFNGLGETINTEGER64I_VPROC>(OpenGL::g_cached_gl_get_integer64i_v)(target,
                                                                                     index,
                                                                                     data);
}