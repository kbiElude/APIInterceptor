/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorPointer(GLint        size,
                                       GLenum        type,
                                       GLsizei       stride,
                                       const GLvoid* pointer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glColorPointer(size=[%d] type=[%s] stride=[%d] pointer=[%p])",
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             stride,
             pointer);

    reinterpret_cast<PFNGLCOLORPOINTERPROC>(OpenGL::g_cached_gl_color_pointer)(size,
                                                                               type,
                                                                               stride,
                                                                               pointer);
}