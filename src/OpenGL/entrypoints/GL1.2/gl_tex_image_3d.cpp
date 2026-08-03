/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_image_3d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage3D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLsizei     height,
                                      GLsizei     depth,
                                      GLint       border,
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

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexImage3D(target=[%s] level=[%d] internalformat=[%s] width=[%d] height=[%d] depth=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 static_cast<int32_t>(depth),
                 border,
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE3D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_i32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
                APIInterceptor::APIFunctionArgument::create_i32       (depth),
                APIInterceptor::APIFunctionArgument::create_i32       (border),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE3D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXIMAGE3DPROC>(OpenGL::g_cached_gl_tex_image_3D)(target,
                                                                                level,
                                                                                internalformat,
                                                                                width,
                                                                                height,
                                                                                depth,
                                                                                border,
                                                                                format,
                                                                                type,
                                                                                pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE3D,
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
            APIInterceptor::APIFunctionArgument::create_i32       (height),
            APIInterceptor::APIFunctionArgument::create_i32       (depth),
            APIInterceptor::APIFunctionArgument::create_i32       (border),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE3D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
