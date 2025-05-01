/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMap2f(GLenum         target,
                                 GLfloat        u1,
                                 GLfloat        u2,
                                 GLint          ustride,
                                 GLint          uorder,
                                 GLfloat        v1,
                                 GLfloat        v2,
                                 GLint          vstride,
                                 GLint          vorder,
                                 const GLfloat* points)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glMap2f(target=[%s], u1=[%f], u2=[%f], ustride=[%d], uorder=[%d], v1=[%f], v2=[%f], vstride=[%d], vorder=[%d], points=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             u1,
             u2,
             ustride,
             uorder,
             v1,
             v2,
             vstride,
             vorder,
             points);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAP2F,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (target),
            APIInterceptor::APIFunctionArgument::create_fp32    (u1),
            APIInterceptor::APIFunctionArgument::create_fp32    (u2),
            APIInterceptor::APIFunctionArgument::create_i32     (ustride),
            APIInterceptor::APIFunctionArgument::create_i32     (uorder),
            APIInterceptor::APIFunctionArgument::create_fp32    (v1),
            APIInterceptor::APIFunctionArgument::create_fp32    (v2),
            APIInterceptor::APIFunctionArgument::create_i32     (vstride),
            APIInterceptor::APIFunctionArgument::create_i32     (vorder),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(points),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP2F,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAP2FPROC>(OpenGL::g_cached_gl_map_2f)(target,
                                                                     u1,
                                                                     u2,
                                                                     ustride,
                                                                     uorder,
                                                                     v1,
                                                                     v2,
                                                                     vstride,
                                                                     vorder,
                                                                     points);
    }
}