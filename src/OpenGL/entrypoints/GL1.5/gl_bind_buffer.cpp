/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_bind_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindBuffer(GLenum target,
                                      GLuint buffer)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindBuffer(target=[%s] buffer=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 buffer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFER,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32       (buffer),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDBUFFERPROC>(OpenGL::g_cached_gl_bind_buffer)(target,
                                                                               buffer);
    }

    if (tracker.is_top_level_api_call() )
    {
        OpenGL::BufferBindingTarget binding_target;

        if (OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                 &binding_target) )
        {
            auto& context = OpenGL::get_context_state();

            context.bound_buffers[static_cast<size_t>(binding_target)] = buffer;
        }
    }
}