/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_gen_queries.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenQueries(GLsizei n,
                                      GLuint* ids)
{
    AI_TRACE("glGenQueries(n=[%d] id=[%p])",
             static_cast<int32_t>(n),
             ids);

    if (OpenGL::g_cached_gl_gen_queries == nullptr)
    {
        OpenGL::g_cached_gl_gen_queries = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGenQueries");
    }

    reinterpret_cast<PFNGLGENQUERIESPROC>(OpenGL::g_cached_gl_gen_queries)(n,
                                                                           ids);
}