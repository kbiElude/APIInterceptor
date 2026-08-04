/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_transform_feedback_varyings.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTransformFeedbackVaryings(GLuint               program,
                                                     GLsizei              count,
                                                     const GLchar* const* varyings,
                                                     GLenum               bufferMode)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTransformFeedbackVaryings(program=[%u] count=[%d] varyings=[%p] bufferMode=[%s])",
                 program,
                 static_cast<int32_t>(count),
                 varyings,
                 OpenGL::Utils::get_raw_string_for_gl_enum(bufferMode) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKVARYINGS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (program),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (varyings),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(bufferMode),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKVARYINGS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(OpenGL::g_cached_gl_transform_feedback_varyings)(program,
                                                                                                             count,
                                                                                                             varyings,
                                                                                                             bufferMode);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKVARYINGS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (program),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (varyings),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(bufferMode),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTRANSFORMFEEDBACKVARYINGS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
