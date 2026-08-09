/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_texture_sub_image3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTextureSubImage3D(GLuint      texture,
                                             GLint       level,
                                             GLint       xoffset,
                                             GLint       yoffset,
                                             GLint       zoffset,
                                             GLsizei     width,
                                             GLsizei     height,
                                             GLsizei     depth,
                                             GLenum      format,
                                             GLenum      type,
                                             const void* pixels)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                pixels_data_chunk_id   = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTextureSubImage3D(texture=[%u] level=[%d] xoffset=[%d] yoffset=[%d] zoffset=[%d] width=[%d] height=[%d] depth=[%d] format=[%s] type=[%s] pixels=[%p])",
                 texture,
                 level,
                 xoffset,
                 yoffset,
                 zoffset,
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 static_cast<int32_t>(depth),
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        pixels_data_chunk_id = APIInterceptor::register_data_chunk(pixels,
                                                                   Utils::get_n_texture_data_bytes(static_cast<uint32_t>(width),
                                                                                                   static_cast<uint32_t>(height),
                                                                                                   static_cast<uint32_t>(depth),
                                                                                                   format,
                                                                                                   type) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESUBIMAGE3D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (texture),
                APIInterceptor::APIFunctionArgument::create_i32          (level),
                APIInterceptor::APIFunctionArgument::create_i32          (xoffset),
                APIInterceptor::APIFunctionArgument::create_i32          (yoffset),
                APIInterceptor::APIFunctionArgument::create_i32          (zoffset),
                APIInterceptor::APIFunctionArgument::create_i32          (width),
                APIInterceptor::APIFunctionArgument::create_i32          (height),
                APIInterceptor::APIFunctionArgument::create_i32          (depth),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(pixels_data_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESUBIMAGE3D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXTURESUBIMAGE3DPROC>(OpenGL::g_cached_gl_texture_sub_image3d)(texture,
                                                                                              level,
                                                                                              xoffset,
                                                                                              yoffset,
                                                                                              zoffset,
                                                                                              width,
                                                                                              height,
                                                                                              depth,
                                                                                              format,
                                                                                              type,
                                                                                              pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESUBIMAGE3D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32          (texture),
            APIInterceptor::APIFunctionArgument::create_i32          (level),
            APIInterceptor::APIFunctionArgument::create_i32          (xoffset),
            APIInterceptor::APIFunctionArgument::create_i32          (yoffset),
            APIInterceptor::APIFunctionArgument::create_i32          (zoffset),
            APIInterceptor::APIFunctionArgument::create_i32          (width),
            APIInterceptor::APIFunctionArgument::create_i32          (height),
            APIInterceptor::APIFunctionArgument::create_i32          (depth),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(pixels_data_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESUBIMAGE3D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
