/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_invalidate_sub_framebuffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInvalidateSubFramebuffer(GLenum        target,
                                                    GLsizei       numAttachments,
                                                    const GLenum* attachments,
                                                    GLint         x,
                                                    GLint         y,
                                                    GLsizei       width,
                                                    GLsizei       height)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glInvalidateSubFramebuffer(target=[%s] numAttachments=[%d] attachments=[%p] x=[%d] y=[%d] width=[%d] height=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(numAttachments),
                 attachments,
                 x,
                 y,
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATESUBFRAMEBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (numAttachments),
                APIInterceptor::APIFunctionArgument::create_u32_ptr   (attachments),
                APIInterceptor::APIFunctionArgument::create_i32       (x),
                APIInterceptor::APIFunctionArgument::create_i32       (y),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATESUBFRAMEBUFFER,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(OpenGL::g_cached_gl_invalidate_sub_framebuffer)(target,
                                                                                                             numAttachments,
                                                                                                             attachments,
                                                                                                             x,
                                                                                                             y,
                                                                                                             width,
                                                                                                             height);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATESUBFRAMEBUFFER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (numAttachments),
            APIInterceptor::APIFunctionArgument::create_u32_ptr   (attachments),
            APIInterceptor::APIFunctionArgument::create_i32       (x),
            APIInterceptor::APIFunctionArgument::create_i32       (y),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (height),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATESUBFRAMEBUFFER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
