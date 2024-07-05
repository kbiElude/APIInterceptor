/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteQueries(GLsizei       n,
                                         const GLuint* ids)
{
    AI_TRACE("glDeleteQueries(n=[%d] ids=[%p])",
             static_cast<int32_t>(n),
             ids);

    if (OpenGL::g_cached_gl_delete_queries == nullptr)
    {
        OpenGL::g_cached_gl_delete_queries = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteQueries");
    }

    reinterpret_cast<PFNGLDELETEQUERIESPROC>(OpenGL::g_cached_gl_delete_queries)(n,
                                                                                 ids);
}