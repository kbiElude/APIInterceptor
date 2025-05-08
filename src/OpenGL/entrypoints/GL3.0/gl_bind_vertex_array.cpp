/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_vertex_array.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindVertexArray(GLuint array)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindVertexArray(array=[%d])",
             array);

    reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(OpenGL::g_cached_gl_bind_vertex_array)(array);
}