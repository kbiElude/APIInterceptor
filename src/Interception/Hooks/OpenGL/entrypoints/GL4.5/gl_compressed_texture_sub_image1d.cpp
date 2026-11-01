/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL4.5/gl_compressed_texture_sub_image1d.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/pixel_data_chunk.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiCompressedTextureSubImage1D(GLuint      texture,
                                                                            GLint       level,
                                                                            GLint       xoffset,
                                                                            GLsizei     width,
                                                                            GLenum      format,
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
        AI_TRACE("glCompressedTextureSubImage1D(texture=[%u] level=[%d] xoffset=[%d] width=[%d] format=[%s] imageSize=[%d] data=[%p])",
                 texture,
                 level,
                 xoffset,
                 static_cast<int32_t>(width),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(format),
                 static_cast<int32_t>(imageSize),
                 data);

        pixels_chunk = Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack_bytes(data,
                                                                                            static_cast<uint64_t>(imageSize));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE1D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_i32       (xoffset),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
                pixels_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE1D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC>(Interception::Hooks::OpenGL::g_cached_gl_compressed_texture_sub_image1d)(texture,
                                                                                                                                        level,
                                                                                                                                        xoffset,
                                                                                                                                        width,
                                                                                                                                        format,
                                                                                                                                        imageSize,
                                                                                                                                        data);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE1D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_i32       (level),
            APIInterceptor::APIFunctionArgument::create_i32       (xoffset),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            APIInterceptor::APIFunctionArgument::create_i32       (imageSize),
            pixels_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE1D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
