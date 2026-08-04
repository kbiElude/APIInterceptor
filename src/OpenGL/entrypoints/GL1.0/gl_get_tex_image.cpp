/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexImage(GLenum target,
                                       GLint  level,
                                       GLenum format,
                                       GLenum type,
                                       void*  pixels)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetTexImage(target=[%s] level=[%d] format=[%s] type=[%s] pixels=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETTEXIMAGEPROC>(OpenGL::g_cached_gl_get_tex_image)(target,
                                                                                  level,
                                                                                  format,
                                                                                  type,
                                                                                  pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        uint32_t pixels_data_chunk_id = 0;

        if (pixels != nullptr)
        {
            TextureBindingTarget binding_target;

            if (Utils::get_texture_binding_target_for_gl_enum(target, &binding_target) )
            {
                const auto& context     = get_context_state              ();
                const auto  texture_id  = context.bound_textures         [static_cast<size_t>(binding_target)];
                const auto  level_props = context.get_texture_level_props(texture_id,
                                                                          level);

                AI_ASSERT(level_props.width != 0);

                pixels_data_chunk_id = APIInterceptor::register_data_chunk(pixels,
                                                                           Utils::get_n_texture_data_bytes(level_props.width,
                                                                                                           level_props.height != 0 ? level_props.height
                                                                                                                                   : 1u,
                                                                                                           level_props.depth  != 0 ? level_props.depth
                                                                                                                                   : 1u,
                                                                                                           format,
                                                                                                           type) );
            }
        }

        {
            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (level),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(pixels_data_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }
}
