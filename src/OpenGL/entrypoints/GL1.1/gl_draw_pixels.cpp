/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_pixels.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawPixels(GLsizei       width,
                                      GLsizei       height,
                                      GLenum        format,
                                      GLenum        type,
                                      const GLvoid* pixels)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glDrawPixels(width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             width,
             height,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWPIXELS,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32     (width),
            APIInterceptor::APIFunctionArgument::create_i32     (height),
            APIInterceptor::APIFunctionArgument::create_u32     (format),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(pixels),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWPIXELS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWPIXELSPROC>(OpenGL::g_cached_gl_draw_pixels)(width,
                                                                               height,
                                                                               format,
                                                                               type,
                                                                               pixels);
    }
}