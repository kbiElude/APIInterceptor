/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_enable_vertex_attrib_array.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEnableVertexAttribArray(GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEnableVertexAttribArray(index=[%u])",
             index);

    reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(OpenGL::g_cached_gl_enable_vertex_attrib_array)(index);
}