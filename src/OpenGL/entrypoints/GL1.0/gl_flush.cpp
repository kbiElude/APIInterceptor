/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_flush.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFlush(void)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glFlush()");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFLUSH,
                          0,
                          nullptr,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_flush == nullptr)
    {
        OpenGL::g_cached_gl_flush = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFlush");
    }

    reinterpret_cast<PFNGLFLUSHPROC>(OpenGL::g_cached_gl_flush)();
}