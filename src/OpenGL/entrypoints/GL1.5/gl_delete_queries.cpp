/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteQueries(GLsizei       n,
                                         const GLuint* ids)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteQueries(n=[%d] ids=[%p])",
             static_cast<int32_t>(n),
             ids);

    reinterpret_cast<PFNGLDELETEQUERIESPROC>(OpenGL::g_cached_gl_delete_queries)(n,
                                                                                 ids);
}