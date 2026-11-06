/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.1/gl_tex_gen_iv.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/param_counts.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiTexGeniv(GLenum       coord,
                                                         GLenum       pname,
                                                         const GLint* params)
{
    const uint32_t                          n_params = Interception::Hooks::OpenGL::Utils::get_n_tex_gen_params(pname);
    APIInterceptor::MemoryChunk             params_chunk(params,
                                                         n_params,
                                                         sizeof(GLint));
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexGeniv(coord=[%s], pname=[%s], params=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(coord),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(pname),
                 params);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXGENIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (coord),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXGENIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXGENIVPROC>(Interception::Hooks::OpenGL::g_cached_gl_tex_gen_iv)(coord,
                                                                                                 pname,
                                                                                                 params);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXGENIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (coord),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXGENIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}