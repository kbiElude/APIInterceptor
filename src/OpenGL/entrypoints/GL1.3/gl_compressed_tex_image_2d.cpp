/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompressedTexImage2D(GLenum      target,
                                                GLint       level,
                                                GLenum      internalformat,
                                                GLsizei     width,
                                                GLsizei     height,
                                                GLint       border,
                                                GLsizei     imageSize,
                                                const void* data)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                data_chunk_id          = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCompressedTexImage2D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] border=[%d] imageSize=[%d] data=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 border,
                 imageSize,
                 data);

        data_chunk_id = APIInterceptor::register_data_chunk(data,
                                                            (data != nullptr) ? static_cast<uint32_t>(imageSize) : 0);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE2D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (level),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (internalformat),
                APIInterceptor::APIFunctionArgument::create_i32          (width),
                APIInterceptor::APIFunctionArgument::create_i32          (height),
                APIInterceptor::APIFunctionArgument::create_i32          (border),
                APIInterceptor::APIFunctionArgument::create_i32          (imageSize),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE2D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(OpenGL::g_cached_gl_compressed_tex_image_2D)(target,
                                                                                                     level,
                                                                                                     internalformat,
                                                                                                     width,
                                                                                                     height,
                                                                                                     border,
                                                                                                     imageSize,
                                                                                                     data);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE2D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_i32          (level),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (internalformat),
            APIInterceptor::APIFunctionArgument::create_i32          (width),
            APIInterceptor::APIFunctionArgument::create_i32          (height),
            APIInterceptor::APIFunctionArgument::create_i32          (border),
            APIInterceptor::APIFunctionArgument::create_i32          (imageSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE2D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
