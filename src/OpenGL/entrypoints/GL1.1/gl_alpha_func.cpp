/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_alpha_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiAlphaFunc(GLenum   func,
                                     GLclampf ref)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glAlphaFunc(func=[%s], ref=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (func),
            APIInterceptor::APIFunctionArgument::create_fp32(ref),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLALPHAFUNC,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLACCUMPROC>(OpenGL::g_cached_gl_alpha_func)(func,
                                                                     ref);
}