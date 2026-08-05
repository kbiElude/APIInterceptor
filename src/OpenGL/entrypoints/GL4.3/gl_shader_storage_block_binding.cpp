/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_shader_storage_block_binding.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiShaderStorageBlockBinding(GLuint program,
                                                     GLuint storageBlockIndex,
                                                     GLuint storageBlockBinding)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glShaderStorageBlockBinding(program=[%u] storageBlockIndex=[%u] storageBlockBinding=[%u])",
                 program,
                 storageBlockIndex,
                 storageBlockBinding);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERSTORAGEBLOCKBINDING,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(program),
                APIInterceptor::APIFunctionArgument::create_u32(storageBlockIndex),
                APIInterceptor::APIFunctionArgument::create_u32(storageBlockBinding),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERSTORAGEBLOCKBINDING,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSHADERSTORAGEBLOCKBINDINGPROC>(OpenGL::g_cached_gl_shader_storage_block_binding)(program,
                                                                                                                storageBlockIndex,
                                                                                                                storageBlockBinding);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSHADERSTORAGEBLOCKBINDING,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(program),
            APIInterceptor::APIFunctionArgument::create_u32(storageBlockIndex),
            APIInterceptor::APIFunctionArgument::create_u32(storageBlockBinding),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSHADERSTORAGEBLOCKBINDING,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
