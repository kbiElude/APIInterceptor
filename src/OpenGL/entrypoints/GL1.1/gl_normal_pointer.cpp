/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormalPointer(GLenum        type,
                                         GLsizei       stride,
                                         const GLvoid* pointer)
{
    AI_TRACE("glNormalPointer(type=[%s], stride=[%d], pointer=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             stride,
             pointer);

    reinterpret_cast<PFNGLNORMALPOINTERPROC>(OpenGL::g_cached_gl_normal_pointer)(type,
                                                                                 stride,
                                                                                 pointer);
}