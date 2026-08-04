/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage_multisample.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRenderbufferStorageMultisample(GLenum  target,
                                                          GLsizei samples,
                                                          GLenum  internalformat,
                                                          GLsizei width,
                                                          GLsizei height)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glRenderbufferStorageMultisample(target=[%s] samples=[%d] internalformat=[%s] width=[%d] height=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(samples),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRENDERBUFFERSTORAGEMULTISAMPLE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (samples),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRENDERBUFFERSTORAGEMULTISAMPLE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(g_cached_gl_renderbuffer_storage_multisample)(target,
                                                                                                               samples,
                                                                                                               internalformat,
                                                                                                               width,
                                                                                                               height);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRENDERBUFFERSTORAGEMULTISAMPLE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (samples),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (height),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRENDERBUFFERSTORAGEMULTISAMPLE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
