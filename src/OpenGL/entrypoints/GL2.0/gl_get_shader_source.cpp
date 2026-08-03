/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_source.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetShaderSource(GLuint   shader,
                                           GLsizei  bufSize,
                                           GLsizei* length,
                                           GLchar*  source)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetShaderSource(shader=[%u] bufSize=[%d] length=[%p] source=[%p])",
                 shader,
                 static_cast<int32_t>(bufSize),
                 length,
                 source);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSHADERSOURCE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32     (shader),
                APIInterceptor::APIFunctionArgument::create_i32     (bufSize),
                APIInterceptor::APIFunctionArgument::create_void_ptr(length),
                APIInterceptor::APIFunctionArgument::create_void_ptr(source),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSHADERSOURCE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(OpenGL::g_cached_gl_get_shader_source)(shader,
                                                                                          bufSize,
                                                                                          length,
                                                                                          source);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSHADERSOURCE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (shader),
            APIInterceptor::APIFunctionArgument::create_i32     (bufSize),
            APIInterceptor::APIFunctionArgument::create_void_ptr(length),
            APIInterceptor::APIFunctionArgument::create_void_ptr(source),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSHADERSOURCE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
