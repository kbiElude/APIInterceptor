/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLenum AI_APIENTRY OpenGL::aiClientWaitSync(GLsync     sync,
                                            GLbitfield flags,
                                            GLuint64   timeout)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLenum                                  result                 = GL_WAIT_FAILED;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glClientWaitSync(sync=[%p] flags=[%s] timeout=[%llu])",
                 sync,
                 OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Wait_Sync_Mask, flags),
                 timeout);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLIENTWAITSYNC,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(sync),
                APIInterceptor::APIFunctionArgument::create_u32     (flags),
                APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<const void*>(&timeout)),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLIENTWAITSYNC,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLCLIENTWAITSYNCPROC>(OpenGL::g_cached_gl_client_wait_sync)(sync,
                                                                                                  flags,
                                                                                                  timeout);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLIENTWAITSYNC,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_u32_glenum(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLIENTWAITSYNC,
                                   post_callback_func_arg,
                                   0,       /* in_n_args_out   */
                                   nullptr, /* in_args_out_ptr */
                                  &result_arg);
        }
    }

    return result;
}