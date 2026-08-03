/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawArrays(GLenum         mode,
                                           const GLint*   first,
                                           const GLsizei* count,
                                           GLsizei        drawcount)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                first_chunk_id         = 0;
    uint32_t                                count_chunk_id         = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiDrawArrays(mode=[%s] first=[%p] count=[%p] drawcount=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 first,
                 count,
                 static_cast<int32_t>(drawcount) );

        first_chunk_id = APIInterceptor::register_data_chunk(first,
                                                             (first != nullptr) ? sizeof(GLint)   * static_cast<uint32_t>(drawcount) : 0);
        count_chunk_id = APIInterceptor::register_data_chunk(count,
                                                             (count != nullptr) ? sizeof(GLsizei) * static_cast<uint32_t>(drawcount) : 0);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(first_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk_id),
                APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(g_cached_gl_multi_draw_arrays)(mode,
                                                                                  first,
                                                                                  count,
                                                                                  drawcount);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(first_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk_id),
            APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
