/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribIPointer(GLuint      index,
                                                GLint       size,
                                                GLenum      type,
                                                GLsizei     stride,
                                                const void* pointer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glVertexAttribIPointer(index=[%u] size=[%d] type=[%s] stride=[%d] pointer=[%p])",
             index,
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             static_cast<int32_t>(stride),
             pointer);

    reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>(OpenGL::g_cached_gl_vertex_attrib_i_pointer)(index,
                                                                                                 size,
                                                                                                 type,
                                                                                                 stride,
                                                                                                 pointer);
}