/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPixelMapfv(GLenum   map,
                                         GLfloat* values)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glGetPixelMapfv(map=[%s], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             values);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPIXELMAPFV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (map),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(values),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPIXELMAPFV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETPIXELMAPFVPROC>(OpenGL::g_cached_gl_get_pixel_map_fv)(map,
                                                                                       values);
    }
}