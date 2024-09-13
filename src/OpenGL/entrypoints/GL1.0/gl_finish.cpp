/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFinish(void)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glFinish()");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFINISH,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFINISH,
                          0,
                          nullptr,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_finish == nullptr)
    {
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFINISHPROC>(OpenGL::g_cached_gl_finish)();
    }
}