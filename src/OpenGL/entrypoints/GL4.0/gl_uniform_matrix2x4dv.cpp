/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.0/gl_uniform_matrix2x4dv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiUniformMatrix2x4dv(GLint           location,
                                              GLsizei         count,
                                              GLboolean       transpose,
                                              const GLdouble* value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUniformMatrix2x4dv(location=[%d] count=[%d] transpose=[%u] value=[%p])",
                 location,
                 static_cast<int32_t>(count),
                 static_cast<uint32_t>(transpose),
                 value);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX2X4DV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32      (location),
                APIInterceptor::APIFunctionArgument::create_i32      (count),
                APIInterceptor::APIFunctionArgument::create_u8       (transpose),
                APIInterceptor::APIFunctionArgument::create_fp64_ptr (value),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX2X4DV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLUNIFORMMATRIX2X4DVPROC>(OpenGL::g_cached_gl_uniform_matrix2x4dv)(location,
                                                                                               count,
                                                                                               transpose,
                                                                                               value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX2X4DV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32      (location),
            APIInterceptor::APIFunctionArgument::create_i32      (count),
            APIInterceptor::APIFunctionArgument::create_u8       (transpose),
            APIInterceptor::APIFunctionArgument::create_fp64_ptr (value),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNIFORMMATRIX2X4DV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
