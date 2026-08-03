/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_iv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectiv(const GLint* v1,
                                  const GLint* v2)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                v1_chunk_id             = 0;
    uint32_t                                v2_chunk_id             = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRectiv(v1=[%p], v2=[%p])",
                 v1,
                 v2);

        v1_chunk_id = APIInterceptor::register_data_chunk(v1,
                                                          (v1 != nullptr) ? 2 * static_cast<uint32_t>(sizeof(GLint)) : 0u);

        v2_chunk_id = APIInterceptor::register_data_chunk(v2,
                                                          (v2 != nullptr) ? 2 * static_cast<uint32_t>(sizeof(GLint)) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(v1_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(v2_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTIVPROC>(OpenGL::g_cached_gl_rect_iv)(v1,
                                                                       v2);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(v1_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(v2_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}