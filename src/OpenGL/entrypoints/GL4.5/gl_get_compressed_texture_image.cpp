/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_get_compressed_texture_image.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetCompressedTextureImage(GLuint  texture,
                                                     GLint   level,
                                                     GLsizei bufSize,
                                                     void*   pixels)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetCompressedTextureImage(texture=[%u] level=[%d] bufSize=[%d] pixels=[%p])",
                 texture,
                 level,
                 static_cast<int32_t>(bufSize),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTUREIMAGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (texture),
                APIInterceptor::APIFunctionArgument::create_i32      (level),
                APIInterceptor::APIFunctionArgument::create_i32      (bufSize),
                APIInterceptor::APIFunctionArgument::create_void_ptr (pixels),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTUREIMAGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC>(OpenGL::g_cached_gl_get_compressed_texture_image)(texture,
                                                                                                               level,
                                                                                                               bufSize,
                                                                                                               pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTUREIMAGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          pixels_chunk_id = APIInterceptor::register_data_chunk(pixels,
                                                                                                  (pixels != nullptr) ? static_cast<uint32_t>(bufSize) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (texture),
            APIInterceptor::APIFunctionArgument::create_i32           (level),
            APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (pixels_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTUREIMAGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
