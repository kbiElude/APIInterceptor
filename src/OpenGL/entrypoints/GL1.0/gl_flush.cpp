/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_flush.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFlush(void)
{
    AI_TRACE("glFlush()");

    if (OpenGL::g_cached_gl_flush == nullptr)
    {
        OpenGL::g_cached_gl_flush = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFlush");
    }

    reinterpret_cast<PFNGLFLUSHPROC>(OpenGL::g_cached_gl_flush)();
}