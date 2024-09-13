/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendColor(GLfloat red,
                                      GLfloat green,
                                      GLfloat blue,
                                      GLfloat alpha)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glBlendColor(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDCOLOR,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(red),
            APIInterceptor::APIFunctionArgument::create_fp32(green),
            APIInterceptor::APIFunctionArgument::create_fp32(blue),
            APIInterceptor::APIFunctionArgument::create_fp32(alpha),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDCOLOR,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLENDCOLORPROC>(OpenGL::g_cached_gl_blend_color)(red,
                                                                               green,
                                                                               blue,
                                                                               alpha);
    }
}