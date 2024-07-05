/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_cull_face.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCullFace(GLenum mode)
{
    AI_TRACE("glCullFace(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (OpenGL::g_cached_gl_cull_face == nullptr)
    {
        OpenGL::g_cached_gl_cull_face = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCullFace");
    }

    reinterpret_cast<PFNGLCULLFACEPROC>(OpenGL::g_cached_gl_cull_face)(mode);
}