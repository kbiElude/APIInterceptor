/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoordPointer(GLint         size,
                                           GLenum        type,
                                           GLsizei       stride,
                                           const GLvoid* pointer)
{
    AI_TRACE("glTexCoordPointer(size=[%d], type=[%s], stride=[%d], pointer=[%p])",
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             stride,
             pointer);

    reinterpret_cast<PFNGLTEXCOORDPOINTERPROC>(OpenGL::g_cached_gl_tex_coord_pointer)(size,
                                                                                      type,
                                                                                      stride,
                                                                                      pointer);
}