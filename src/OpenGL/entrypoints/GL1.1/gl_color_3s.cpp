/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3s(GLshort red,
                                   GLshort green,
                                   GLshort blue)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glColor3s(red=[%d] green=[%d] blue=[%d])",
             static_cast<uint32_t>(red),
             static_cast<uint32_t>(green),
             static_cast<uint32_t>(blue) );

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLOR3S,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i16(red),
            APIInterceptor::APIFunctionArgument::create_i16(green),
            APIInterceptor::APIFunctionArgument::create_i16(blue),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLOR3S,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLOR3SPROC>(OpenGL::g_cached_gl_color_3s)(red,
                                                                         green,
                                                                         blue);
    }
}