/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_buffers.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteBuffers(GLsizei       n,
                                         const GLuint* buffers)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                buffers_chunk_id       = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDeleteBuffers(n=[%d] buffers=[%p])",
                 static_cast<int32_t>(n),
                 buffers);

        buffers_chunk_id = APIInterceptor::register_data_chunk(buffers,
                                                               (buffers != nullptr) ? sizeof(GLuint) * static_cast<uint32_t>(n) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETEBUFFERS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32          (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(buffers_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETEBUFFERS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDELETEBUFFERSPROC>(OpenGL::g_cached_gl_delete_buffers)(n,
                                                                                     buffers);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETEBUFFERS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32          (n),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(buffers_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETEBUFFERS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }

    if (tracker.is_top_level_api_call() && buffers != nullptr)
    {
        auto& context = OpenGL::get_context_state();

        for (GLsizei n_buffer = 0;
                     n_buffer < n;
                   ++n_buffer)
        {
            context.buffer_object_id_to_buffer_props_ptr_map.erase(buffers[n_buffer]);
        }
    }
}
