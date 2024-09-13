/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_disable_vertex_attrib_array.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDisableVertexAttribArray(GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDisableVertexAttribArray(index=[%d])",
             index);

    reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(OpenGL::g_cached_gl_disable_vertex_attrib_array)(index);
}