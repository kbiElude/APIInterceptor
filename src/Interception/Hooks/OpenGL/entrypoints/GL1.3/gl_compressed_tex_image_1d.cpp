/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_1d.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/pixel_data_chunk.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiCompressedTexImage1D(GLenum      target,
                                                                     GLint       level,
                                                                     GLenum      internalformat,
                                                                     GLsizei     width,
                                                                     GLint       border,
                                                                     GLsizei     imageSize,
                                                                     const void* data)
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
        AI_TRACE("glCompressedTexImage1D(target=[%s] level=[%d] internalformat=[%s] width=[%d] border=[%d] imageSize=[%d] data=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target),
                 level,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 border,
                 imageSize,
                 data);

        pixels_chunk = Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack_bytes(data,
                                                                                            static_cast<uint64_t>(imageSize));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE1D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (border),
                APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
                pixels_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE1D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(Interception::Hooks::OpenGL::g_cached_gl_compressed_tex_image_1D)(target,
                                                                                                                          level,
                                                                                                                          internalformat,
                                                                                                                          width,
                                                                                                                          border,
                                                                                                                          imageSize,
                                                                                                                          data);

        TextureBindingTarget binding_target;

        const bool is_top_level = tracker.is_top_level_api_call();

        if (is_top_level)
        {
            const bool is_binding_target_known = Utils::get_texture_binding_target_for_gl_enum(target,
                                                                                               &binding_target);

            if (is_binding_target_known)
            {
                auto& context = get_context_state();

                context.texture_manager.set_compressed_level_props(context.texture_manager.get_bound_texture(binding_target),
                                                                   level,
                                                                   static_cast<uint32_t>(imageSize),
                                                                   static_cast<uint32_t>(width),
                                                                   1,
                                                                   1);
            }
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE1D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i32       (level),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (border),
            APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
            pixels_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE1D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
