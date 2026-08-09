/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_transform_feedback_buffer_range.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTransformFeedbackBufferRange(GLuint     xfb,
                                                        GLuint     index,
                                                        GLuint     buffer,
                                                        GLintptr   offset,
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
        AI_TRACE("glTransformFeedbackBufferRange(xfb=[%u] index=[%u] buffer=[%u] offset=[%d] size=[%d])",
                 xfb,
                 index,
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(size) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(xfb),
                APIInterceptor::APIFunctionArgument::create_u32(index),
                APIInterceptor::APIFunctionArgument::create_u32(buffer),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(size) ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC>(OpenGL::g_cached_gl_transform_feedback_buffer_range)(xfb,
                                                                                                                     index,
                                                                                                                     buffer,
                                                                                                                     offset,
                                                                                                                     size);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERRANGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(xfb),
            APIInterceptor::APIFunctionArgument::create_u32(index),
            APIInterceptor::APIFunctionArgument::create_u32(buffer),
            APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(offset) ),
            APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(size) ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERRANGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
