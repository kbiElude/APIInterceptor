/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyPixels(GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum  type)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glCopyPixels(x=[%d] y=[%d] width=[%d] height=[%d] type=[%s])",
             x,
             y,
             width,
             height,
             OpenGL::Utils::get_raw_string_for_gl_enum(type) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYPIXELS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(x),
            APIInterceptor::APIFunctionArgument::create_i32(y),
            APIInterceptor::APIFunctionArgument::create_i32(width),
            APIInterceptor::APIFunctionArgument::create_i32(height),
            APIInterceptor::APIFunctionArgument::create_u32(type),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYPIXELS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLCOPYPIXELSPROC>(OpenGL::g_cached_gl_copy_pixels)(x,
                                                                           y,
                                                                           width,
                                                                           height,
                                                                           type);
}