/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/globals.h"
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
        /* Query the compressed image size directly from the driver. This is a nested
         * GL call but safe: the Tracker already marks this thread as non-top-level,
         * so the interceptor won't re-enter the callback system. */
        GLint compressed_size = 0;

        reinterpret_cast<PFNGLGETTEXLEVELPARAMETERIVPROC>(OpenGL::g_cached_gl_get_tex_level_parameteriv)(target,
                                                                                                         level,
                                                                                                         GL_TEXTURE_COMPRESSED_IMAGE_SIZE,
                                                                                                        &compressed_size);

        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          img_chunk_id = APIInterceptor::register_data_chunk(img,
                                                                                               (img != nullptr) ? static_cast<uint32_t>(compressed_size) : 0);

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