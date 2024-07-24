/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_end.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEnd()
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glEnd()");

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLEND,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLEND,
                          0,
                          nullptr,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLENDPROC>(OpenGL::g_cached_gl_end)();
}