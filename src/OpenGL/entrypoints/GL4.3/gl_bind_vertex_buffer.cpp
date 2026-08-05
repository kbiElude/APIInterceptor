/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_bind_vertex_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindVertexBuffer(GLuint   bindingindex,
                                            GLuint   buffer,
                                            GLintptr offset,
                                            GLsizei  stride)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindVertexBuffer(bindingindex=[%u] buffer=[%u] offset=[%d] stride=[%d])",
                 bindingindex,
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(stride));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDVERTEXBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(bindingindex),
                APIInterceptor::APIFunctionArgument::create_u32(buffer),
                APIInterceptor::APIFunctionArgument::create_i32(offset),
                APIInterceptor::APIFunctionArgument::create_i32(stride),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDVERTEXBUFFER,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDVERTEXBUFFERPROC>(OpenGL::g_cached_gl_bind_vertex_buffer)(bindingindex,
                                                                                             buffer,
                                                                                             offset,
                                                                                             stride);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDVERTEXBUFFER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(bindingindex),
            APIInterceptor::APIFunctionArgument::create_u32(buffer),
            APIInterceptor::APIFunctionArgument::create_i32(offset),
            APIInterceptor::APIFunctionArgument::create_i32(stride),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDVERTEXBUFFER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
