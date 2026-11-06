/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.0/gl_clear_buffer_iv.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/param_counts.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiClearBufferiv(GLenum       buffer,
                                                              GLint        drawbuffer,
                                                              const GLint* value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    const uint32_t                          n_values = Interception::Hooks::OpenGL::Utils::get_n_clear_buffer_values(buffer);
    APIInterceptor::MemoryChunk             value_chunk(value,
                                                        n_values,
                                                        sizeof(GLint));

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glClearBufferiv(buffer=[%s] drawbuffer=[%d] value=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(buffer),
                 drawbuffer,
                 value);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (buffer),
                APIInterceptor::APIFunctionArgument::create_i32          (drawbuffer),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(value_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERIV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCLEARBUFFERIVPROC>(Interception::Hooks::OpenGL::g_cached_gl_clear_buffer_iv)(buffer,
                                                                                                           drawbuffer,
                                                                                                           value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (buffer),
            APIInterceptor::APIFunctionArgument::create_i32          (drawbuffer),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(value_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
