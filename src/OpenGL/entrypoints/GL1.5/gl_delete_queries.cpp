/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteQueries(GLsizei       n,
                                         const GLuint* ids)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDeleteQueries(n=[%d] ids=[%p])",
                 static_cast<int32_t>(n),
                 ids);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETEQUERIES,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const auto ids_chunk_id = APIInterceptor::register_data_chunk(ids,
                                                                          (ids != nullptr) ? sizeof(GLuint) * static_cast<uint32_t>(n) : 0);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32          (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(ids_chunk_id),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETEQUERIES,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDELETEQUERIESPROC>(OpenGL::g_cached_gl_delete_queries)(n,
                                                                                     ids);
    }
}