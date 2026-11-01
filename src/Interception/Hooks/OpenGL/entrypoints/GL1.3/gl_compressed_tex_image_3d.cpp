/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_3d.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/pixel_data_chunk.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexImage3D(GLenum      target,
                                                GLint       level,
                                                GLenum      internalformat,
                                                GLsizei     width,
                                                GLsizei     height,
                                                GLsizei     depth,
                                                GLint       border,
                                                GLsizei     imageSize,
                                                const void* data)
{
    OpenGL::PixelDataChunk                  pixels_chunk;
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCompressedTexImage3D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] depth=[%d] border=[%d] imageSize=[%d] data=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 static_cast<int32_t>(depth),
                 border,
                 static_cast<int32_t>(imageSize),
                 data);

        pixels_chunk = OpenGL::PixelDataChunk::create_for_unpack_bytes(data,
                                                                       static_cast<uint64_t>(imageSize));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE3D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
                APIInterceptor::APIFunctionArgument::create_i32       (depth),
                APIInterceptor::APIFunctionArgument::create_i32       (border),
                APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
                pixels_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE3D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(OpenGL::g_cached_gl_compressed_tex_image_3D)(target,
                                                                                                     level,
                                                                                                     internalformat,
                                                                                                     width,
                                                                                                     height,
                                                                                                     depth,
                                                                                                     border,
                                                                                                     imageSize,
                                                                                                     data);

        TextureBindingTarget binding_target;

        if (tracker.is_top_level_api_call                ()               &&
            Utils::get_texture_binding_target_for_gl_enum(target,
                                                         &binding_target) )
        {
            auto& context = get_context_state();

            context.texture_manager.set_compressed_level_props(context.texture_manager.get_bound_texture(binding_target),
                                                               level,
                                                               static_cast<uint32_t>(imageSize),
                                                               static_cast<uint32_t>(width),
                                                               static_cast<uint32_t>(height),
                                                               static_cast<uint32_t>(depth));
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE3D,
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
            APIInterceptor::APIFunctionArgument::create_i32       (height),
            APIInterceptor::APIFunctionArgument::create_i32       (depth),
            APIInterceptor::APIFunctionArgument::create_i32       (border),
            APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
            pixels_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE3D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
