/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/pixel_data_chunk.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiTexImage1D(GLenum      target,
                                                           GLint       level,
                                                           GLint       internalformat,
                                                           GLsizei     width,
                                                           GLint       border,
                                                           GLenum      format,
                                                           GLenum      type,
                                                           const void* pixels)
{
    Interception::Hooks::OpenGL::PixelDataChunk pixels_chunk;
    void*                                       post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC     post_callback_func_ptr = nullptr;
    void*                                       pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC      pre_callback_func_ptr  = nullptr;
    bool                                        should_pass_through    = true;
    APIInterceptor::Tracker                     tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexImage1D(target=[%s] level=[%d] internalformat=[%s] width=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target),
                 level,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 border,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(format),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(type),
                 pixels);

        pixels_chunk = Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack(pixels,
                                                                                      static_cast<uint32_t>(width),
                                                                                      1,
                                                                                      1,
                                                                                      format,
                                                                                      type);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_i32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (border),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                pixels_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXIMAGE1DPROC>(Interception::Hooks::OpenGL::g_cached_gl_tex_image_1D)(target,
                                                                                                     level,
                                                                                                     internalformat,
                                                                                                     width,
                                                                                                     border,
                                                                                                     format,
                                                                                                     type,
                                                                                                     pixels);

        TextureBindingTarget binding_target;

        const bool is_top_level = tracker.is_top_level_api_call();

        if (is_top_level)
        {
            const bool is_binding_target_known = Utils::get_texture_binding_target_for_gl_enum(target,
                                                                                               &binding_target);

            if (is_binding_target_known)
            {
                auto& context = get_context_state();

                context.texture_manager.set_level_props(context.texture_manager.get_bound_texture(binding_target),
                                                level,
                                                static_cast<uint32_t>(width),
                                                1,
                                                1);
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (level),
            APIInterceptor::APIFunctionArgument::create_i32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (border),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            pixels_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
