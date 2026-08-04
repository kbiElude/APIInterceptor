/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetCompressedTexImage(GLenum target,
                                                 GLint  level,
                                                 void*  img)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetCompressedTexImage(target=[%s] level=[%d] img=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 img);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXIMAGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (img),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXIMAGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(OpenGL::g_cached_gl_get_compressed_tex_image)(target,
                                                                                                       level,
                                                                                                       img);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXIMAGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        uint32_t img_chunk_id = 0;

        if (img != nullptr)
        {
            TextureBindingTarget binding_target;

            if (Utils::get_texture_binding_target_for_gl_enum(target,
                                                             &binding_target) )
            {
                const auto& context     = get_context_state              ();
                const auto  texture_id  = context.bound_textures         [static_cast<size_t>(binding_target)];
                const auto  level_props = context.get_texture_level_props(texture_id,
                                                                          level);

                AI_ASSERT(level_props.compressed_size_bytes != 0);

                img_chunk_id = APIInterceptor::register_data_chunk(img,
                                                                   level_props.compressed_size_bytes);
            }
        }

        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_i32          (level),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(img_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXIMAGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
