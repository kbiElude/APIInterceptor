/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_pointerv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBufferPointerv(GLenum target,
                                             GLenum pname,
                                             void** params)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    /* The only pname defined by GL 1.5 for this entrypoint. */
    AI_ASSERT(pname == GL_BUFFER_MAP_POINTER);

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetBufferPointerv(target=[%s] pname=[%s] params=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 params);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETBUFFERPOINTERV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (params),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETBUFFERPOINTERV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(OpenGL::g_cached_gl_get_buffer_pointerv)(target,
                                                                                              pname,
                                                                                              params);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETBUFFERPOINTERV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        /* params holds a void** — we capture the pointer value written into *params
         * (i.e. the mapped buffer address) as raw bytes. The address is only valid
         * for the lifetime of the mapping, so it is recorded for analysis purposes
         * only, not for replay. */
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          params_chunk_id = APIInterceptor::register_data_chunk(params,
                                                                                                  (params != nullptr) ? sizeof(void*) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETBUFFERPOINTERV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}