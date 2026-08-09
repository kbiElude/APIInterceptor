/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteTextures(GLsizei       n,
                                          const GLuint* textures)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
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
                APIInterceptor::APIFunctionArgument::create_i32    (n),
                APIInterceptor::APIFunctionArgument::create_void_ptr(textures),
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
        reinterpret_cast<PFNGLDELETETEXTURESPROC>(OpenGL::g_cached_gl_delete_textures)(n,
                                                                                       textures);

        if (tracker.is_top_level_api_call() && textures != nullptr)
        {
            auto& context = OpenGL::get_context_state();

            for (GLsizei n_texture = 0;
                         n_texture < n;
                       ++n_texture)
            {
                const uint64_t texture_id   = static_cast<uint64_t>(textures[n_texture]);
                const uint64_t key_base     = texture_id << 16;
                const uint64_t key_mask     = ~static_cast<uint64_t>(0xFFFFu);
                auto           it           = context.texture_level_props_map.begin();

                while (it != context.texture_level_props_map.end() )
                {
                    if ((it->first & key_mask) == key_base)
                    {
                        it = context.texture_level_props_map.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
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
            APIInterceptor::APIFunctionArgument::create_i32    (n),
            APIInterceptor::APIFunctionArgument::create_void_ptr(textures),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}