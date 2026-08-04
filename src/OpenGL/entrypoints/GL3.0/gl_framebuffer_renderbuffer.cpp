/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_renderbuffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFramebufferRenderbuffer(GLenum target,
                                                   GLenum attachment,
                                                   GLenum renderbuffertarget,
                                                   GLuint renderbuffer)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glFramebufferRenderbuffer(target=[%s] attachment=[%s] renderbuffertarget=[%s] renderbuffer=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(attachment),
                 OpenGL::Utils::get_raw_string_for_gl_enum(renderbuffertarget),
                 renderbuffer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFRAMEBUFFERRENDERBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(attachment),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(renderbuffertarget),
                APIInterceptor::APIFunctionArgument::create_u32       (renderbuffer),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFRAMEBUFFERRENDERBUFFER,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(OpenGL::g_cached_gl_framebuffer_renderbuffer)(target,
                                                                                                         attachment,
                                                                                                         renderbuffertarget,
                                                                                                         renderbuffer);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFRAMEBUFFERRENDERBUFFER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(attachment),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(renderbuffertarget),
            APIInterceptor::APIFunctionArgument::create_u32       (renderbuffer),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFRAMEBUFFERRENDERBUFFER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
