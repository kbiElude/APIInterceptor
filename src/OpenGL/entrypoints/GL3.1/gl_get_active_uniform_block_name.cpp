/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_block_name.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformBlockName(GLuint   program,
                                                     GLuint   uniformBlockIndex,
                                                     GLsizei  bufSize,
                                                     GLsizei* length,
                                                     GLchar*  uniformBlockName)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetActiveUniformBlockName(program=[%u] uniformBlockIndex=[%u] bufSize=[%d] length=[%p] uniformBlockName=[%p])",
                 program,
                 uniformBlockIndex,
                 static_cast<int32_t>(bufSize),
                 length,
                 uniformBlockName);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKNAME,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (program),
                APIInterceptor::APIFunctionArgument::create_u32      (uniformBlockIndex),
                APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
                APIInterceptor::APIFunctionArgument::create_void_ptr (length),
                APIInterceptor::APIFunctionArgument::create_void_ptr (uniformBlockName),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKNAME,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(OpenGL::g_cached_gl_get_active_uniform_block_name)(program,
                                                                                                               uniformBlockIndex,
                                                                                                               bufSize,
                                                                                                               length,
                                                                                                               uniformBlockName);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKNAME,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32      (program),
            APIInterceptor::APIFunctionArgument::create_u32      (uniformBlockIndex),
            APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
            APIInterceptor::APIFunctionArgument::create_void_ptr (length),
            APIInterceptor::APIFunctionArgument::create_void_ptr (uniformBlockName),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKNAME,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
