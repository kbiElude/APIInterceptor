/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilFunc(GLenum func,
                                       GLint  ref,
                                       GLuint mask)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glStencilFunc(func=[%s] ref=[%d] mask=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(func),
                 ref,
                 mask);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(func),
                APIInterceptor::APIFunctionArgument::create_i32       (ref),
                APIInterceptor::APIFunctionArgument::create_u32       (mask),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSTENCILFUNCPROC>(g_cached_gl_stencil_func)(func,
                                                                         ref,
                                                                         mask);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(func),
            APIInterceptor::APIFunctionArgument::create_i32       (ref),
            APIInterceptor::APIFunctionArgument::create_u32       (mask),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
