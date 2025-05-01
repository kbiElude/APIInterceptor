/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid2d(GLint    un,
                                     GLdouble u1,
                                     GLdouble u2,
                                     GLint    vn,
                                     GLdouble v1,
                                     GLdouble v2)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glMapGrid2d(un=[%d], u1=[%.4lf], u2=[%.4lf], vn=[%d], v1=[%.4lf], v2=[%.4lf])",
             un,
             u1,
             u2,
             vn,
             v1,
             v2);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPGRID2D,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32 (un),
            APIInterceptor::APIFunctionArgument::create_fp64(u1),
            APIInterceptor::APIFunctionArgument::create_fp64(u2),
            APIInterceptor::APIFunctionArgument::create_i32 (vn),
            APIInterceptor::APIFunctionArgument::create_fp64(v1),
            APIInterceptor::APIFunctionArgument::create_fp64(v2),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPGRID2D,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAPGRID2DPROC>(OpenGL::g_cached_gl_map_grid_2d)(un,
                                                                              u1,
                                                                              u2,
                                                                              vn,
                                                                              v1,
                                                                              v2);
    }
}