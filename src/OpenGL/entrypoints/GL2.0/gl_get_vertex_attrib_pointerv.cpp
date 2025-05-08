/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attrib_pointerv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribPointerv(GLuint index,
                                                   GLenum pname,
                                                   void** pointer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetVertexAttribPointerv(index=[%u] pname=[%s] pointer=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             pointer);

    reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(OpenGL::g_cached_gl_get_vertex_attrib_pointerv)(index,
                                                                                                       pname,
                                                                                                       pointer);
}