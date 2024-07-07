/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_begin.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBegin(GLenum mode)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glBegin(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBEGIN,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(mode) 
        };

        callback_func_ptr(sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLBEGINPROC>(OpenGL::g_cached_gl_begin)(mode);
}