/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage1D(GLenum      target,
                                      GLint       level,
                                      GLint       internalformat,
                                      GLsizei     width,
                                      GLint       border,
                                      GLenum      format,
                                      GLenum      type,
                                      const void* pixels)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexImage1D(target=[%s] level=[%d] internalformat=[%s] width=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 border,
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
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
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE1D,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXIMAGE1DPROC>(OpenGL::g_cached_gl_tex_image_1D)(target,
                                                                                level,
                                                                                internalformat,
                                                                                width,
                                                                                border,
                                                                                format,
                                                                                type,
                                                                                pixels);
    }
}