/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_is_query.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsQuery(GLuint id)
{
    AI_TRACE("glIsQuery(id=[%u])",
             id);

    if (OpenGL::g_cached_gl_is_query == nullptr)
    {
        OpenGL::g_cached_gl_is_query = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsQuery");
    }

    return reinterpret_cast<PFNGLISQUERYPROC>(OpenGL::g_cached_gl_is_query)(id);
}