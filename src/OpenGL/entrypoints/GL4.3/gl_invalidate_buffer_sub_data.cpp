/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_invalidate_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInvalidateBufferSubData(GLuint     buffer,
                                                   GLintptr   offset,
                                                   GLsizeiptr length)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glInvalidateBufferSubData(buffer=[%u] offset=[%d] length=[%d])",
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(length));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATEBUFFERSUBDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(buffer),
                APIInterceptor::APIFunctionArgument::create_i32(offset),
                APIInterceptor::APIFunctionArgument::create_i32(length),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATEBUFFERSUBDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLINVALIDATEBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_invalidate_buffer_sub_data)(buffer,
                                                                                                            offset,
                                                                                                            length);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATEBUFFERSUBDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(buffer),
            APIInterceptor::APIFunctionArgument::create_i32(offset),
            APIInterceptor::APIFunctionArgument::create_i32(length),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATEBUFFERSUBDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
