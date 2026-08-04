/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_name.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformName(GLuint   program,
                                                GLuint   uniformIndex,
                                                GLsizei  bufSize,
                                                GLsizei* length,
                                                GLchar*  uniformName)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetActiveUniformName(program=[%u] uniformIndex=[%u] bufSize=[%d] length=[%p] uniformName=[%p])",
                 program,
                 uniformIndex,
                 static_cast<int32_t>(bufSize),
                 length,
                 uniformName);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMNAME,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (program),
                APIInterceptor::APIFunctionArgument::create_u32      (uniformIndex),
                APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
                APIInterceptor::APIFunctionArgument::create_void_ptr (length),
                APIInterceptor::APIFunctionArgument::create_void_ptr (uniformName),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMNAME,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETACTIVEUNIFORMNAMEPROC>(OpenGL::g_cached_gl_get_active_uniform_name)(program,
                                                                                                     uniformIndex,
                                                                                                     bufSize,
                                                                                                     length,
                                                                                                     uniformName);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMNAME,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32      (program),
            APIInterceptor::APIFunctionArgument::create_u32      (uniformIndex),
            APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
            APIInterceptor::APIFunctionArgument::create_void_ptr (length),
            APIInterceptor::APIFunctionArgument::create_void_ptr (uniformName),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMNAME,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
