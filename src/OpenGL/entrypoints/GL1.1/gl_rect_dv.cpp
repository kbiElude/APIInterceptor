/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRectdv(const GLdouble* v1,
                                  const GLdouble* v2)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glRectdv(v1=[%p], v2=[%p])",
             v1,
             v2);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLRECTDV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64_ptr(v1),
            APIInterceptor::APIFunctionArgument::create_fp64_ptr(v2),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLRECTDV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLRECTDVPROC>(OpenGL::g_cached_gl_rect_dv)(v1,
                                                                       v2);
    }
}