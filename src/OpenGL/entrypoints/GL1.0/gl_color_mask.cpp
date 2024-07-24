/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_color_mask.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColorMask(GLboolean red,
                                     GLboolean green,
                                     GLboolean blue,
                                     GLboolean alpha)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glColorMask(red=[%d] green=[%d] blue={%d] alpha=[%d])",
             (red   == GL_TRUE) ? 1 : 0,
             (green == GL_TRUE) ? 1 : 0,
             (blue  == GL_TRUE) ? 1 : 0,
             (alpha == GL_TRUE) ? 1 : 0);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLORMASK,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u8(red),
            APIInterceptor::APIFunctionArgument::create_u8(green),
            APIInterceptor::APIFunctionArgument::create_u8(blue),
            APIInterceptor::APIFunctionArgument::create_u8(alpha),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLORMASK,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_color_mask == nullptr)
    {
        OpenGL::g_cached_gl_color_mask = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glColorMask");
    }

    reinterpret_cast<PFNGLCOLORMASKPROC>(OpenGL::g_cached_gl_color_mask)(red,
                                                                         green,
                                                                         blue,
                                                                         alpha);
}