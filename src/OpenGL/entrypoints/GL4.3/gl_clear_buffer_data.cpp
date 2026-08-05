/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_clear_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferData(GLenum      target,
                                           GLenum      internalformat,
                                           GLenum      format,
                                           GLenum      type,
                                           const void* data)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glClearBufferData(target=[%s] internalformat=[%s] format=[%s] type=[%s] data=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 data);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCLEARBUFFERDATAPROC>(OpenGL::g_cached_gl_clear_buffer_data)(target,
                                                                                           internalformat,
                                                                                           format,
                                                                                           type,
                                                                                           data);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (data),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARBUFFERDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
