/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiReadPixels(GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum  format,
                                      GLenum  type,
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
        AI_TRACE("glReadPixels(x=[%d] y=[%d] width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
                 x,
                 y,
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32       (x),
                APIInterceptor::APIFunctionArgument::create_i32       (y),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels)
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLREADPIXELSPROC>(g_cached_gl_read_pixels)(x,
                                                                       y,
                                                                       width,
                                                                       height,
                                                                       format,
                                                                       type,
                                                                       pixels);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32       (x),
            APIInterceptor::APIFunctionArgument::create_i32       (y),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (height),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (pixels)
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
