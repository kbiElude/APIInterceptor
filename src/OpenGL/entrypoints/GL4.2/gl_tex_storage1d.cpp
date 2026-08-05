/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.2/gl_tex_storage1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"
#include <algorithm>

void AI_APIENTRY OpenGL::aiTexStorage1D(GLenum  target,
                                        GLsizei levels,
                                        GLenum  internalformat,
                                        GLsizei width)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexStorage1D(target=[%s] levels=[%d] internalformat=[%s] width=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(levels),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXSTORAGE1D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (levels),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXSTORAGE1D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXSTORAGE1DPROC>(OpenGL::g_cached_gl_tex_storage1d)(target,
                                                                                    levels,
                                                                                    internalformat,
                                                                                    width);

        TextureBindingTarget binding_target;

        if (tracker.is_top_level_api_call                 ()              &&
            Utils::get_texture_binding_target_for_gl_enum(target,
                                                         &binding_target) )
        {
            auto&          context    = get_context_state();
            const GLuint   texture_id = context.bound_textures[static_cast<size_t>(binding_target)];
            uint32_t       mip_width  = static_cast<uint32_t>(width);

            for (GLsizei level = 0;
                         level < levels;
                       ++level)
            {
                context.set_texture_level_props(texture_id,
                                                level,
                                                mip_width,
                                                1,
                                                1);

                mip_width = (std::max)(1u,
                                       mip_width / 2u);
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXSTORAGE1D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (levels),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXSTORAGE1D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
