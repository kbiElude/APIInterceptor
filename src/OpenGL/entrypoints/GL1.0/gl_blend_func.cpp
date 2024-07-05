/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_blend_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFunc(GLenum sfactor,
                                     GLenum dfactor)
{
    AI_TRACE("glBlendFunc(sfactor=[%s] dfactor=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(sfactor),
             OpenGL::Utils::get_raw_string_for_gl_enum(dfactor) );

    if (OpenGL::g_cached_gl_blend_func == nullptr)
    {
        OpenGL::g_cached_gl_blend_func = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlendFunc");
    }

    reinterpret_cast<PFNGLBLENDFUNCPROC>(OpenGL::g_cached_gl_blend_func)(sfactor,
                                                                         dfactor);
}