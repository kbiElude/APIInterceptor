/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_elements_instanced.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElementsInstanced(GLenum      mode,
                                                 GLsizei     count,
                                                 GLenum      type,
                                                 const void* indices,
                                                 GLsizei     instancecount)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawElementsInstanced(mode=[%s] count=[%d] type=[%s] indices=[%p] instancecount=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 static_cast<int32_t>(count),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices,
                 static_cast<int32_t>(instancecount) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCED,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
                APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCED,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>(OpenGL::g_cached_gl_draw_elements_instanced)(mode,
                                                                                                      count,
                                                                                                      type,
                                                                                                      indices,
                                                                                                      instancecount);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCED,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
            APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCED,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
