/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_debug_message_control.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDebugMessageControl(GLenum         source,
                                               GLenum         type,
                                               GLenum         severity,
                                               GLsizei        count,
                                               const GLuint*  ids,
                                               GLboolean      enabled)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDebugMessageControl(source=[%s] type=[%s] severity=[%s] count=[%d] ids=[%p] enabled=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(source),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 OpenGL::Utils::get_raw_string_for_gl_enum(severity),
                 static_cast<int32_t>(count),
                 ids,
                 static_cast<uint32_t>(enabled));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDEBUGMESSAGECONTROL,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(source),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(severity),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_ptr   (ids),
                APIInterceptor::APIFunctionArgument::create_u8        (enabled),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDEBUGMESSAGECONTROL,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>(OpenGL::g_cached_gl_debug_message_control)(source,
                                                                                                   type,
                                                                                                   severity,
                                                                                                   count,
                                                                                                   ids,
                                                                                                   enabled);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDEBUGMESSAGECONTROL,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(source),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(severity),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_u32_ptr   (ids),
            APIInterceptor::APIFunctionArgument::create_u8        (enabled),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDEBUGMESSAGECONTROL,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
