/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiReadPixels(GLint   x,
                                      GLint   y,
                                      GLsizei width,
                                      GLsizei height,
                                      GLenum  format,
                                      GLenum  type,
                                      void*   pixels)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glReadPixels(x=[%d] y=[%d] width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             x,
             y,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32     (x),
            APIInterceptor::APIFunctionArgument::create_i32     (y),
            APIInterceptor::APIFunctionArgument::create_i32     (width),
            APIInterceptor::APIFunctionArgument::create_i32     (height),
            APIInterceptor::APIFunctionArgument::create_u32     (format),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(pixels)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_read_pixels == nullptr)
    {
        OpenGL::g_cached_gl_read_pixels = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glReadPixels");
    }

    reinterpret_cast<PFNGLREADPIXELSPROC>(g_cached_gl_read_pixels)(x,
                                                                   y,
                                                                   width,
                                                                   height,
                                                                   format,
                                                                   type,
                                                                   pixels);
}