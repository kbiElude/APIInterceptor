/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_op_separate.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilOpSeparate(GLenum face,
                                             GLenum sfail,
                                             GLenum dpfail,
                                             GLenum dppass)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glStencilOpSeparate(face=[%s] sfail=[%s] dpfail=[%s] dppass=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(face),
                 OpenGL::Utils::get_raw_string_for_gl_enum(sfail),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dpfail),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dppass) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILOPSEPARATE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(face),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(sfail),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dpfail),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dppass),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILOPSEPARATE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(OpenGL::g_cached_gl_stencil_op_separate)(face,
                                                                                              sfail,
                                                                                              dpfail,
                                                                                              dppass);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILOPSEPARATE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(face),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(sfail),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dpfail),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dppass),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILOPSEPARATE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
