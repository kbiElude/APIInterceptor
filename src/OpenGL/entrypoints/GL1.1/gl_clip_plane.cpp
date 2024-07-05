/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_clip_plane.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClipPlane(GLenum          plane,
                                     const GLdouble* equation)
{
    AI_TRACE("glClipPlane(plane=[%s], equation=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(plane),
             equation);

    reinterpret_cast<PFNGLCLIPPLANEPROC>(OpenGL::g_cached_gl_clip_plane)(plane,
                                                                         equation);
}