/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_feedback_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFeedbackBuffer(GLsizei  size,
                                          GLenum   type,
                                          GLfloat* buffer)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glFeedbackBuffer(size={%d], type=[%s], buffer=[%p])",
                 size,
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 buffer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFEEDBACKBUFFER,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32       (size),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_fp32_ptr  (buffer),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFEEDBACKBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFEEDBACKBUFFERPROC>(OpenGL::g_cached_gl_feedback_buffer)(size,
                                                                                       type,
                                                                                       buffer);
    }
}