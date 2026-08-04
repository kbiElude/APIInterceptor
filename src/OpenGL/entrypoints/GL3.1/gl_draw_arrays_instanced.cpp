/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_arrays_instanced.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawArraysInstanced(GLenum  mode,
                                               GLint   first,
                                               GLsizei count,
                                               GLsizei instancecount)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawArraysInstanced(mode=[%s] first=[%d] count=[%d] instancecount=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 first,
                 static_cast<int32_t>(count),
                 static_cast<int32_t>(instancecount) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINSTANCED,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (first),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINSTANCED,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(OpenGL::g_cached_gl_draw_arrays_instanced)(mode,
                                                                                                  first,
                                                                                                  count,
                                                                                                  instancecount);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINSTANCED,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_i32       (first),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINSTANCED,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
