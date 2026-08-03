/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x4_fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformMatrix3x4fv(GLint          location,
                                              GLsizei        count,
                                              GLboolean      transpose,
                                              const GLfloat* value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                value_chunk_id         = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUniformMatrix3x4fv(location=[%d] count=[%d] transpose=[%d] value=[%p])",
                 location,
                 static_cast<int32_t>(count),
                 (transpose == GL_TRUE) ? 1 : 0,
                 value);

        value_chunk_id = APIInterceptor::register_data_chunk(value,
                                                             (value != nullptr) ? static_cast<uint32_t>(count) * 12u * static_cast<uint32_t>(sizeof(GLfloat)) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX3X4FV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32           (location),
                APIInterceptor::APIFunctionArgument::create_i32           (count),
                APIInterceptor::APIFunctionArgument::create_u8            (transpose),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (value_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX3X4FV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>(OpenGL::g_cached_gl_uniform_matrix_3x4_fv)(location,
                                                                                                  count,
                                                                                                  transpose,
                                                                                                  value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX3X4FV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32           (location),
            APIInterceptor::APIFunctionArgument::create_i32           (count),
            APIInterceptor::APIFunctionArgument::create_u8            (transpose),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (value_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX3X4FV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
