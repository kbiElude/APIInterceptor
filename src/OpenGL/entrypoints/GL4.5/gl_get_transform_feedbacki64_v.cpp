/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_get_transform_feedbacki64_v.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTransformFeedbacki64_v(GLuint   xfb,
                                                     GLenum   pname,
                                                     GLuint   index,
                                                     GLint64* param)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetTransformFeedbacki64_v(xfb=[%u] pname=[%s] index=[%u] param=[%p])",
                 xfb,
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 index,
                 param);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI64_V,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (xfb),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_u32       (index),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (param),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI64_V,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKI64_VPROC>(OpenGL::g_cached_gl_get_transform_feedbacki64_v)(xfb,
                                                                                                              pname,
                                                                                                              index,
                                                                                                              param);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI64_V,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          param_chunk_id = APIInterceptor::register_data_chunk(param,
                                                                                                 (param != nullptr) ? sizeof(GLint64) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (xfb),
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (pname),
            APIInterceptor::APIFunctionArgument::create_u32           (index),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (param_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI64_V,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
