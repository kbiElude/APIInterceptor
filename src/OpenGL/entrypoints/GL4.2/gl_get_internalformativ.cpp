/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.2/gl_get_internalformativ.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetInternalformativ(GLenum  target,
                                               GLenum  internalformat,
                                               GLenum  pname,
                                               GLsizei bufSize,
                                               GLint*  params)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetInternalformativ(target=[%s] internalformat=[%s] pname=[%s] bufSize=[%d] params=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 static_cast<int32_t>(bufSize),
                 params);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETINTERNALFORMATIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_i32       (bufSize),
                APIInterceptor::APIFunctionArgument::create_i32_ptr   (params),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETINTERNALFORMATIV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETINTERNALFORMATIVPROC>(OpenGL::g_cached_gl_get_internalformativ)(target,
                                                                                                 internalformat,
                                                                                                 pname,
                                                                                                 bufSize,
                                                                                                 params);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETINTERNALFORMATIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          params_chunk_id = APIInterceptor::register_data_chunk(params,
                                                                                                  (params != nullptr) ? sizeof(GLint) * static_cast<uint32_t>(bufSize) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (target),
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (internalformat),
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (pname),
            APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (params_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETINTERNALFORMATIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
