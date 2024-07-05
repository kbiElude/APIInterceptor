/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_sample_maski.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiSampleMaski(GLuint     maskNumber,
                                       GLbitfield mask)
{
    AI_TRACE("glSampleMaski(maskNumber=[%u] mask=[%x])",
             maskNumber,
             mask);

    if (OpenGL::g_cached_gl_sample_maski == nullptr)
    {
        OpenGL::g_cached_gl_sample_maski = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glSampleMaski");
    }

    reinterpret_cast<PFNGLSAMPLEMASKIPROC>(g_cached_gl_sample_maski)(maskNumber,
                                                                     mask);
}