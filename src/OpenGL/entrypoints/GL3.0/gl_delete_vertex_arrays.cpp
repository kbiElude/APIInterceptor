/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_vertex_arrays.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteVertexArrays(GLsizei       n,
                                              const GLuint* arrays)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                arrays_chunk_id        = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDeleteVertexArrays(n=[%d] arrays=[%p])",
                 static_cast<int32_t>(n),
                 arrays);

        arrays_chunk_id = APIInterceptor::register_data_chunk(arrays,
                                                              (arrays != nullptr) ? sizeof(GLuint) * static_cast<uint32_t>(n) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETEVERTEXARRAYS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32           (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (arrays_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETEVERTEXARRAYS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(OpenGL::g_cached_gl_delete_vertex_arrays)(n,
                                                                                                arrays);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETEVERTEXARRAYS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32           (n),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (arrays_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETEVERTEXARRAYS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
