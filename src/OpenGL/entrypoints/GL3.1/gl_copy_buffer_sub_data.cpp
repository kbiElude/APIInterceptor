/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyBufferSubData(GLenum     readTarget,
                                             GLenum     writeTarget,
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
        AI_TRACE("glCopyBufferSubData(readTarget=[%s] writeTarget=[%s] readOffset=[%d] writeOffset=[%d] size=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(readTarget),
                 OpenGL::Utils::get_raw_string_for_gl_enum(writeTarget),
                 static_cast<int32_t>(readOffset),
                 static_cast<int32_t>(writeOffset),
                 static_cast<int32_t>(size) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYBUFFERSUBDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(readTarget),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(writeTarget),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(readOffset) ),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(writeOffset) ),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(size) ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYBUFFERSUBDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_copy_buffer_sub_data)(readTarget,
                                                                                               writeTarget,
                                                                                               readOffset,
                                                                                               writeOffset,
                                                                                               size);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYBUFFERSUBDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(readTarget),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(writeTarget),
            APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(readOffset) ),
            APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(writeOffset) ),
            APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(size) ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYBUFFERSUBDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
