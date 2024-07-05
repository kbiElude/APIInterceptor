/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_depth_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDepthFunc(GLenum func)
{
    AI_TRACE("glDepthFunc(func=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func) );

    if (OpenGL::g_cached_gl_depth_func == nullptr)
    {
        OpenGL::g_cached_gl_depth_func = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDepthFunc");
    }

    reinterpret_cast<PFNGLDEPTHFUNCPROC>(OpenGL::g_cached_gl_depth_func)(func);
}