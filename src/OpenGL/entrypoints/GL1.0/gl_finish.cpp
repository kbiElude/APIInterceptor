/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFinish(void)
{
    AI_TRACE("glFinish()");

    if (OpenGL::g_cached_gl_finish == nullptr)
    {
        OpenGL::g_cached_gl_finish = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFinish");
    }

    reinterpret_cast<PFNGLFINISHPROC>(OpenGL::g_cached_gl_finish)();
}