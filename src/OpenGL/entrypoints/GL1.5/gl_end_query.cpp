/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_end_query.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEndQuery(GLenum target)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEndQuery(query=[%s])",
             target);

    if (OpenGL::g_cached_gl_end_query == nullptr)
    {
        OpenGL::g_cached_gl_end_query = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndQuery");
    }

    reinterpret_cast<PFNGLENDQUERYPROC>(OpenGL::g_cached_gl_end_query)(target);
}