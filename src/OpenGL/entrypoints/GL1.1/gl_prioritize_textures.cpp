/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_prioritize_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPrioritizeTextures(GLsizei n,
                                              const GLuint* textures,
                                              const GLclampf* priorities)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                textures_chunk_id             = 0;
    uint32_t                                priorities_chunk_id             = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPrioritizeTexturesEXT(n=[%d] textures=[%p] priorities=[%p])",
                 n,
                 textures,
                 priorities);

        textures_chunk_id = APIInterceptor::register_data_chunk(textures,
                                                          (textures != nullptr) ? static_cast<uint32_t>(n) * sizeof(GLuint) : 0u);

        priorities_chunk_id = APIInterceptor::register_data_chunk(priorities,
                                                          (priorities != nullptr) ? static_cast<uint32_t>(n) * sizeof(GLclampf) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32     (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(textures_chunk_id),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(priorities_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPRIORITIZETEXTURESEXTPROC>(OpenGL::g_cached_prioritize_textures_ext)(n,
                                                                                                   textures,
                                                                                                   priorities);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32     (n),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(textures_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(priorities_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}