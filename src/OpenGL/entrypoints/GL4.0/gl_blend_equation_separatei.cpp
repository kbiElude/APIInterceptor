/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.0/gl_blend_equation_separatei.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendEquationSeparatei(GLuint buf,
                                                  GLenum modeRGB,
                                                  GLenum modeAlpha)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBlendEquationSeparatei(buf=[%u] modeRGB=[%s] modeAlpha=[%s])",
                 buf,
                 OpenGL::Utils::get_raw_string_for_gl_enum(modeRGB),
                 OpenGL::Utils::get_raw_string_for_gl_enum(modeAlpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATEI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (buf),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(modeRGB),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(modeAlpha),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATEI,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEIPROC>(OpenGL::g_cached_gl_blend_equation_separatei)(buf,
                                                                                                        modeRGB,
                                                                                                        modeAlpha);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATEI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (buf),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(modeRGB),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(modeAlpha),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATEI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
