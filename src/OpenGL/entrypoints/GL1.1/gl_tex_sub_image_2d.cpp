/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexSubImage2D(GLenum      target,
                                         GLint       level,
                                         GLint       xoffset,
                                         GLint       yoffset,
                                         GLsizei     width,
                                         GLsizei     height,
                                         GLenum      format,
                                         GLenum      type,
                                         const void* pixels)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glTexSubImage2D(target=[%s] level=[%d] xoffset=[%d] yoffset=[%d] width=[%d] height=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             xoffset,
             yoffset,
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXSUBIMAGE2D,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (target),
            APIInterceptor::APIFunctionArgument::create_i32     (level),
            APIInterceptor::APIFunctionArgument::create_i32     (xoffset),
            APIInterceptor::APIFunctionArgument::create_i32     (yoffset),
            APIInterceptor::APIFunctionArgument::create_i32     (width),
            APIInterceptor::APIFunctionArgument::create_i32     (height),
            APIInterceptor::APIFunctionArgument::create_u32     (format),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(pixels)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXSUBIMAGE2D,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXSUBIMAGE2DPROC>(OpenGL::g_cached_gl_tex_sub_image_2D)(target,
                                                                                       level,
                                                                                       xoffset,
                                                                                       yoffset,
                                                                                       width,
                                                                                       height,
                                                                                       format,
                                                                                       type,
                                                                                       pixels);
    }
}