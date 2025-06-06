/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribPointer(GLuint      index,
                                               GLint       size,
                                               GLenum      type,
                                               GLboolean   normalized,
                                               GLsizei     stride,
                                               const void* pointer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribPointer(index=[%u] size=[%d] type=[%s] normalized=[%d] stride=[%d] pointer=[%p])",
             index,
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             (normalized == GL_TRUE) ? 1 : 0,
             static_cast<int32_t>(stride),
             pointer);

    reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(OpenGL::g_cached_gl_vertex_attrib_pointer)(index,
                                                                                              size,
                                                                                              type,
                                                                                              normalized,
                                                                                              stride,
                                                                                              pointer);
}