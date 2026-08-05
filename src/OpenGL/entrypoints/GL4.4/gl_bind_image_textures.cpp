/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.4/gl_bind_image_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindImageTextures(GLuint        first,
                                             GLsizei       count,
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
        AI_TRACE("glBindImageTextures(first=[%u] count=[%d] textures=[%p])",
                 first,
                 static_cast<int32_t>(count),
                 textures);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURES,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32    (first),
                APIInterceptor::APIFunctionArgument::create_i32    (count),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURES,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDIMAGETEXTURESPROC>(OpenGL::g_cached_gl_bind_image_textures)(first,
                                                                                               count,
                                                                                               textures);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURES,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32    (first),
            APIInterceptor::APIFunctionArgument::create_i32    (count),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURES,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
