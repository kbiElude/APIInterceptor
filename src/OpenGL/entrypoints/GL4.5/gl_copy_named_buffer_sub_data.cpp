/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_copy_named_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyNamedBufferSubData(GLuint     readBuffer,
                                                  GLuint     writeBuffer,
                                                  GLintptr   readOffset,
                                                  GLintptr   writeOffset,
                                                  GLsizeiptr size)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCopyNamedBufferSubData(readBuffer=[%u] writeBuffer=[%u] readOffset=[%d] writeOffset=[%d] size=[%d])",
                 readBuffer,
                 writeBuffer,
                 static_cast<int32_t>(readOffset),
                 static_cast<int32_t>(writeOffset),
                 static_cast<int32_t>(size) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYNAMEDBUFFERSUBDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(readBuffer),
                APIInterceptor::APIFunctionArgument::create_u32(writeBuffer),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(readOffset) ),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(writeOffset) ),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(size) ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYNAMEDBUFFERSUBDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOPYNAMEDBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_copy_named_buffer_sub_data)(readBuffer,
                                                                                                         writeBuffer,
                                                                                                         readOffset,
                                                                                                         writeOffset,
                                                                                                         size);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYNAMEDBUFFERSUBDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(readBuffer),
            APIInterceptor::APIFunctionArgument::create_u32(writeBuffer),
            APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(readOffset) ),
            APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(writeOffset) ),
            APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(size) ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYNAMEDBUFFERSUBDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
