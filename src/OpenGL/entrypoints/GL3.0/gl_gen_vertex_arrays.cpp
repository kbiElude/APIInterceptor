/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_vertex_arrays.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenVertexArrays(GLsizei n,
                                           GLuint* arrays)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGenVertexArrays(n=[%d] arrays=[%p])",
             static_cast<int32_t>(n),
             arrays);

    reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(OpenGL::g_cached_gl_gen_vertex_arrays)(n,
                                                                                      arrays);
}