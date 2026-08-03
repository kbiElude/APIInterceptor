/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_func_separate.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFuncSeparate(GLenum sfactorRGB,
                                             GLenum dfactorRGB,
                                             GLenum sfactorAlpha,
                                             GLenum dfactorAlpha)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBlendFuncSeparate(sfactorRGB=[%s] dfactorRGB=[%s] sfactorAlpha=[%s] dfactorAlpha=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(sfactorRGB),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dfactorRGB),
                 OpenGL::Utils::get_raw_string_for_gl_enum(sfactorAlpha),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dfactorAlpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(sfactorRGB),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dfactorRGB),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(sfactorAlpha),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dfactorAlpha),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(OpenGL::g_cached_gl_blend_func_separate)(sfactorRGB,
                                                                                              dfactorRGB,
                                                                                              sfactorAlpha,
                                                                                              dfactorAlpha);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(sfactorRGB),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dfactorRGB),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(sfactorAlpha),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dfactorAlpha),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
