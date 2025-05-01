/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_1f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMap1f(GLenum         target,
                                 GLfloat        u1,
                                 GLfloat        u2,
                                 GLint          stride,
                                 GLint          order,
                                 const GLfloat* points)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glMap1f(target=[%s], u1=[%f], u2=[%f], stride=[%d], order=[%d], points=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             u1,
             u2,
             stride,
             order,
             points);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAP1F,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (target),
            APIInterceptor::APIFunctionArgument::create_fp32    (u1),
            APIInterceptor::APIFunctionArgument::create_fp32    (u2),
            APIInterceptor::APIFunctionArgument::create_i32     (stride),
            APIInterceptor::APIFunctionArgument::create_i32     (order),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(points),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP1F,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAP1FPROC>(OpenGL::g_cached_gl_map_1f)(target,
                                                                     u1,
                                                                     u2,
                                                                     stride,
                                                                     order,
                                                                     points);
    }
}