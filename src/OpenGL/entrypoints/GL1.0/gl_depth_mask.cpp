/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_depth_mask.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDepthMask(GLboolean flag)
{
    AI_TRACE("glDepthMask(flag=[%d])",
             (flag == GL_TRUE) ? 1 : 0);

    if (OpenGL::g_cached_gl_depth_mask == nullptr)
    {
        OpenGL::g_cached_gl_depth_mask = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDepthMask");
    }

    reinterpret_cast<PFNGLDEPTHMASKPROC>(OpenGL::g_cached_gl_depth_mask)(flag);
}