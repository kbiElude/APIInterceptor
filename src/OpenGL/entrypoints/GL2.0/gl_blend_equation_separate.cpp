/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_blend_equation_separate.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendEquationSeparate(GLenum modeRGB,
                                                 GLenum modeAlpha)
{
    AI_TRACE("glBlendEquationSeparate(modeRGB=[%s] modeAlpha=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(modeRGB),
             OpenGL::Utils::get_raw_string_for_gl_enum(modeAlpha) );

    if (OpenGL::g_cached_gl_blend_equation_separate == nullptr)
    {
        OpenGL::g_cached_gl_blend_equation_separate = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlendEquationSeparate");
    }

    reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>(OpenGL::g_cached_gl_blend_equation_separate)(modeRGB,
                                                                                                  modeAlpha);
}