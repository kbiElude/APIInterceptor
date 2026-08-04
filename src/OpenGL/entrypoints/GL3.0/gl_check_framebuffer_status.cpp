/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLenum AI_APIENTRY OpenGL::aiCheckFramebufferStatus(GLenum target)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLenum                                  result                 = 0;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCheckFramebufferStatus(target=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCHECKFRAMEBUFFERSTATUS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCHECKFRAMEBUFFERSTATUS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(OpenGL::g_cached_gl_check_framebuffer_status)(target);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCHECKFRAMEBUFFERSTATUS,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_u32_glenum(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCHECKFRAMEBUFFERSTATUS,
                                   post_callback_func_arg,
                                   0,
                                   nullptr,
                                  &result_arg);
        }
    }

    return result;
}
