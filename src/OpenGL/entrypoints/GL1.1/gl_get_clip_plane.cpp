/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_clip_plane.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetClipPlane(GLenum    plane,
                                        GLdouble* equation)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("gGetClipPlane(plane=[%s], equation=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(plane),
             equation);

    reinterpret_cast<PFNGLGETCLIPPLANEPROC>(OpenGL::g_cached_gl_get_clip_plane)(plane,
                                                                                equation);
}