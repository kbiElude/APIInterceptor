/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_draw_buffers.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawBuffers(GLsizei       n,
                                       const GLenum* bufs)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                bufs_chunk_id          = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawBuffers(n=[%d] bufs=[%p])",
                 static_cast<int32_t>(n),
                 bufs);

        bufs_chunk_id = APIInterceptor::register_data_chunk(bufs,
                                                            (bufs != nullptr) ? static_cast<uint32_t>(n) * static_cast<uint32_t>(sizeof(GLenum)) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFERS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32           (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (bufs_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFERS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWBUFFERSPROC>(OpenGL::g_cached_gl_draw_buffers)(n,
                                                                                 bufs);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFERS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32           (n),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (bufs_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFERS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
