/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_2f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
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
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
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
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_fp32      (u1),
                APIInterceptor::APIFunctionArgument::create_fp32      (u2),
                APIInterceptor::APIFunctionArgument::create_i32       (ustride),
                APIInterceptor::APIFunctionArgument::create_i32       (uorder),
                APIInterceptor::APIFunctionArgument::create_fp32      (v1),
                APIInterceptor::APIFunctionArgument::create_fp32      (v2),
                APIInterceptor::APIFunctionArgument::create_i32       (vstride),
                APIInterceptor::APIFunctionArgument::create_i32       (vorder),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (points),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP2F,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

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

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAP2F,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_fp32      (u1),
            APIInterceptor::APIFunctionArgument::create_fp32      (u2),
            APIInterceptor::APIFunctionArgument::create_i32       (ustride),
            APIInterceptor::APIFunctionArgument::create_i32       (uorder),
            APIInterceptor::APIFunctionArgument::create_fp32      (v1),
            APIInterceptor::APIFunctionArgument::create_fp32      (v2),
            APIInterceptor::APIFunctionArgument::create_i32       (vstride),
            APIInterceptor::APIFunctionArgument::create_i32       (vorder),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (points),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP2F,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}