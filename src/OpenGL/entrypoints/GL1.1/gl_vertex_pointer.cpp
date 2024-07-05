/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_vertex_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexPointer(GLint         size,
                                         GLenum        type,
                                         GLsizei       stride,
                                         const GLvoid* pointer)
{
    AI_TRACE("glVertexPointer(size={%d], type=[%s], stride=[%d], pointer=[%p])",
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             stride,
             pointer);

    reinterpret_cast<PFNGLVERTEXPOINTERPROC>(OpenGL::g_cached_gl_vertex_pointer)(size,
                                                                                 type,
                                                                                 stride,
                                                                                 pointer);
}