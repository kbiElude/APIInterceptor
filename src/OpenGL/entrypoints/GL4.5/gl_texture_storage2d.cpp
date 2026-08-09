/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_texture_storage2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"
#include <algorithm>

void AI_APIENTRY OpenGL::aiTextureStorage2D(GLuint  texture,
                                            GLsizei levels,
                                            GLenum  internalformat,
                                            GLsizei width,
                                            GLsizei height)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTextureStorage2D(texture=[%u] levels=[%d] internalformat=[%s] width=[%d] height=[%d])",
                 texture,
                 static_cast<int32_t>(levels),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_i32       (levels),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXTURESTORAGE2DPROC>(OpenGL::g_cached_gl_texture_storage2d)(texture,
                                                                                           levels,
                                                                                           internalformat,
                                                                                           width,
                                                                                           height);

        if (tracker.is_top_level_api_call() )
        {
            auto&    context    = OpenGL::get_context_state();
            uint32_t mip_width  = static_cast<uint32_t>(width);
            uint32_t mip_height = static_cast<uint32_t>(height);

            for (GLsizei level = 0;
                         level < levels;
                       ++level)
            {
                context.set_texture_level_props(texture,
                                                level,
                                                mip_width,
                                                mip_height,
                                                1);

                mip_width  = (std::max)(1u,
                                        mip_width  / 2u);
                mip_height = (std::max)(1u,
                                        mip_height / 2u);
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_i32       (levels),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (height),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
