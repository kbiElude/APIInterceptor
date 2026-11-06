/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/memory_chunk.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/state_tracker.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiDeleteTextures(GLsizei       n,
                                                               const GLuint* textures)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::MemoryChunk             textures_chunk(textures,
                                                           n,
                                                           sizeof(GLuint));
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDeleteTextures(n=[%d] texture=[%p])",
                 static_cast<int32_t>(n),
                 textures);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32          (n),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(textures_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDELETETEXTURESPROC>(Interception::Hooks::OpenGL::g_cached_gl_delete_textures)(n,
                                                                                                            textures);

        const bool is_top_level = tracker.is_top_level_api_call();

        if (is_top_level)
        {
            if (textures != nullptr)
            {
                auto& context = Interception::Hooks::OpenGL::get_context_state();

                for (GLsizei n_texture = 0;
                             n_texture < n;
                           ++n_texture)
                {
                    context.texture_manager.on_texture_deleted(textures[n_texture]);
                }
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32          (n),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(textures_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}