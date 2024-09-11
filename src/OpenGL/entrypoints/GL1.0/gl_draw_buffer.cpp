/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_draw_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawBuffer(GLenum buf)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glDrawBuffer(buf=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buf) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFER,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(buf),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFER,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_draw_buffer == nullptr)
    {
        OpenGL::g_cached_gl_draw_buffer = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDrawBuffer");
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWBUFFERPROC>(OpenGL::g_cached_gl_draw_buffer)(buf);
    }
}