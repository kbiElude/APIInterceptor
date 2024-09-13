/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_doublev.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetDoublev(GLenum    pname,
                                      GLdouble* data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetDoublev(pname=[%s] data=[%s]",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
    }

    reinterpret_cast<PFNGLGETDOUBLEVPROC>(OpenGL::g_cached_gl_get_doublev)(pname,
                                                                           data);

}