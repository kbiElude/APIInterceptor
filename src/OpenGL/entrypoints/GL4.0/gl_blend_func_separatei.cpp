/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.0/gl_blend_func_separatei.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFuncSeparatei(GLuint buf,
                                              GLenum srcRGB,
                                              GLenum dstRGB,
                                              GLenum srcAlpha,
                                              GLenum dstAlpha)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBlendFuncSeparatei(buf=[%u] srcRGB=[%s] dstRGB=[%s] srcAlpha=[%s] dstAlpha=[%s])",
                 buf,
                 OpenGL::Utils::get_raw_string_for_gl_enum(srcRGB),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dstRGB),
                 OpenGL::Utils::get_raw_string_for_gl_enum(srcAlpha),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dstAlpha) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATEI,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (buf),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(srcRGB),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dstRGB),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(srcAlpha),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dstAlpha),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATEI,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLENDFUNCSEPARATEIPROC>(OpenGL::g_cached_gl_blend_func_separatei)(buf,
                                                                                                srcRGB,
                                                                                                dstRGB,
                                                                                                srcAlpha,
                                                                                                dstAlpha);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATEI,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (buf),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(srcRGB),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dstRGB),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(srcAlpha),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dstAlpha),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNCSEPARATEI,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
