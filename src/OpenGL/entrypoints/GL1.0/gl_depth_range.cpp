/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_depth_range.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDepthRange(GLdouble n,
                                      GLdouble f)
{
    AI_TRACE("glDepthRange(n=[%.4f] f=[%.4f])",
             n,
             f);

    if (OpenGL::g_cached_gl_depth_range == nullptr)
    {
        OpenGL::g_cached_gl_depth_range = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDepthRange");
    }

    reinterpret_cast<PFNGLDEPTHRANGEPROC>(OpenGL::g_cached_gl_depth_range)(n,
                                                                           f);
}