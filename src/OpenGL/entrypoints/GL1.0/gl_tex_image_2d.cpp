/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage2D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLsizei     height,
                                      GLint       border,
                                      GLenum      format,
                                      GLenum      type,
                                      const void* pixels)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    bool                                    should_pass_through     = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                pixels_data_chunk_id    = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexImage2D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 border,
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        const auto n_pixels_bytes = Utils::get_n_texture_data_bytes(width,
                                                                    height,
                                                                    1,
                                                                    format,
                                                                    type);

        pixels_data_chunk_id = APIInterceptor::register_data_chunk(pixels,
                                                                   n_pixels_bytes);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (level),
                APIInterceptor::APIFunctionArgument::create_i32_glenum   (internalformat),
                APIInterceptor::APIFunctionArgument::create_i32          (width),
                APIInterceptor::APIFunctionArgument::create_i32          (height),
                APIInterceptor::APIFunctionArgument::create_i32          (border),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(pixels_data_chunk_id)
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXIMAGE2DPROC>(OpenGL::g_cached_gl_tex_image_2D)(target,
                                                                                level,
                                                                                internalformat,
                                                                                width,
                                                                                height,
                                                                                border,
                                                                                format,
                                                                                type,
                                                                                pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_i32          (level),
            APIInterceptor::APIFunctionArgument::create_i32_glenum   (internalformat),
            APIInterceptor::APIFunctionArgument::create_i32          (width),
            APIInterceptor::APIFunctionArgument::create_i32          (height),
            APIInterceptor::APIFunctionArgument::create_i32          (border),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(pixels_data_chunk_id)
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
