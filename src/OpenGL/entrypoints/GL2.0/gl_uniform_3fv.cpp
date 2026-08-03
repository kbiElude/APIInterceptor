/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3fv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniform3fv(GLint          location,
                                      GLsizei        count,
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
        AI_TRACE("glUniform3fv(location=[%d] count=[%d] value=[%p])",
                 location,
                 static_cast<int32_t>(count),
                 value);

        value_chunk_id = APIInterceptor::register_data_chunk(value,
                                                             (value != nullptr) ? static_cast<uint32_t>(count) * 3u * static_cast<uint32_t>(sizeof(GLfloat)) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3FV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32           (location),
                APIInterceptor::APIFunctionArgument::create_i32           (count),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (value_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3FV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLUNIFORM3FVPROC>(OpenGL::g_cached_gl_uniform_3fv)(location,
                                                                               count,
                                                                               value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3FV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32           (location),
            APIInterceptor::APIFunctionArgument::create_i32           (count),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (value_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORM3FV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
