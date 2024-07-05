/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_blend_equation.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendEquation(GLenum mode)
{
    AI_TRACE("glBlendEquation(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (OpenGL::g_cached_gl_blend_equation == nullptr)
    {
        OpenGL::g_cached_gl_blend_equation = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlendEquation");
    }

    reinterpret_cast<PFNGLBLENDEQUATIONPROC>(OpenGL::g_cached_gl_blend_equation)(mode);
}