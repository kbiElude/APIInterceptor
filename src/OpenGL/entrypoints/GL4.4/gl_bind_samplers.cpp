/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.4/gl_bind_samplers.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindSamplers(GLuint        first,
                                        GLsizei       count,
                                        const GLuint* samplers)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindSamplers(first=[%u] count=[%d] samplers=[%p])",
                 first,
                 static_cast<int32_t>(count),
                 samplers);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDSAMPLERS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32    (first),
                APIInterceptor::APIFunctionArgument::create_i32    (count),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(samplers),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDSAMPLERS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDSAMPLERSPROC>(OpenGL::g_cached_gl_bind_samplers)(first,
                                                                                    count,
                                                                                    samplers);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDSAMPLERS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32    (first),
            APIInterceptor::APIFunctionArgument::create_i32    (count),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(samplers),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDSAMPLERS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
