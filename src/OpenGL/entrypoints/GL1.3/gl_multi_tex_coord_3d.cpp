/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiTexCoord3d(GLenum   target,
                                           GLdouble s,
                                           GLdouble t,
                                           GLdouble r)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiTexCoord3d(target=[%s] s=[%.4lf] t=[%.4lf] r=[%.4lf])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 s,
                 t,
                 r);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD3D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_fp64      (s),
                APIInterceptor::APIFunctionArgument::create_fp64      (t),
                APIInterceptor::APIFunctionArgument::create_fp64      (r),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD3D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTITEXCOORD3DPROC>(OpenGL::g_cached_gl_multi_tex_coord_3d)(target,
                                                                                           s,
                                                                                           t,
                                                                                           r);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD3D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_fp64      (s),
            APIInterceptor::APIFunctionArgument::create_fp64      (t),
            APIInterceptor::APIFunctionArgument::create_fp64      (r),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD3D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}