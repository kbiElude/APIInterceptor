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
    AI_TRACE("glGetDoublev(pname=[%s] data=[%s]",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             data);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETDOUBLEVPROC>(OpenGL::g_cached_gl_get_doublev)(pname,
                                                                           data);

}