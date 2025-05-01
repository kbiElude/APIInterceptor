/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_scale_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiScalef(GLfloat x,
                                  GLfloat y,
                                  GLfloat z)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glScalef(x=[%.4f], y=[%.4f], z=[%.4f])",
             x,
             y,
             z);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSCALEF,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(x),
            APIInterceptor::APIFunctionArgument::create_fp32(y),
            APIInterceptor::APIFunctionArgument::create_fp32(z),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSCALEF,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSCALEFPROC>(OpenGL::g_cached_gl_scale_f)(x,
                                                                       y,
                                                                       z);
    }
}