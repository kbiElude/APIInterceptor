/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferData(GLenum      target,
                                      GLsizeiptr  size,
                                      const void* data,
                                      GLenum      usage)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBufferData(target=[%s] size=[%d] data=[%p] usage=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<uint32_t>(size),
                 data,
                 OpenGL::Utils::get_raw_string_for_gl_enum(usage) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            /* data may be nullptr when the call is allocation-only (no initial upload). */
            const auto data_chunk_id = APIInterceptor::register_data_chunk(data,
                                                                           (data != nullptr) ? static_cast<uint32_t>(size) : 0);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<int32_t>(size) ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (usage),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBUFFERDATA,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBUFFERDATAPROC>(OpenGL::g_cached_gl_buffer_data)(target,
                                                                               size,
                                                                               data,
                                                                               usage);
    }
}