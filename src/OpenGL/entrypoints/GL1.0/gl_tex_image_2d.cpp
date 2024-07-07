/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
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
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glTexImage2D(target=[%s] level={%d] internalformat=[%s] width=[%d] height=[%d] border=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             border,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLACCUM,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (target),
            APIInterceptor::APIFunctionArgument::create_i32     (level),
            APIInterceptor::APIFunctionArgument::create_i32     (internalformat),
            APIInterceptor::APIFunctionArgument::create_i32     (width),
            APIInterceptor::APIFunctionArgument::create_i32     (height),
            APIInterceptor::APIFunctionArgument::create_i32     (border),
            APIInterceptor::APIFunctionArgument::create_u32     (format),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(pixels)
        };

        callback_func_ptr(sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_tex_image_2D == nullptr)
    {
        OpenGL::g_cached_gl_tex_image_2D = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexImage2D");
    }

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