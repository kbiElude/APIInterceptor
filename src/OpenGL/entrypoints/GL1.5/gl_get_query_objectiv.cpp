/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetQueryObjectiv(GLuint id,
                                            GLenum pname,
                                            GLint* params)
{
    AI_TRACE("glGetQueryObjectiv(id=[%u] pname=[%s] params=[%p])",
             id,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_query_objectiv == nullptr)
    {
        OpenGL::g_cached_gl_get_query_objectiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetQueryObjectiv");
    }

    reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(OpenGL::g_cached_gl_get_query_objectiv)(id,
                                                                                        pname,
                                                                                        params);
}