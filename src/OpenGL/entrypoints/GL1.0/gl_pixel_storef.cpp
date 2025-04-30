/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storef.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void APIENTRY OpenGL::aiPixelStoref(GLenum  pname,
                                    GLfloat param)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glPixelStoref(pname=[%s] param=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);


    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (pname),
            APIInterceptor::APIFunctionArgument::create_fp32(param),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPIXELSTOREFPROC>(g_cached_gl_pixel_storef)(pname,
                                                                         param);
    }
}