/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribfv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribfv(GLuint   index,
                                             GLenum   pname,
                                             GLfloat* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetVertexAttribfv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(OpenGL::g_cached_gl_get_vertex_attribfv)(index,
                                                                                          pname,
                                                                                          params);
}