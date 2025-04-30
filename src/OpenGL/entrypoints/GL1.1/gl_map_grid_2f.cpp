/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMapGrid2f(GLint   un,
                                     GLfloat u1,
                                     GLfloat u2,
                                     GLint   vn,
                                     GLfloat v1,
                                     GLfloat v2)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glMapGrid2f(un=[%d], u1=[%.4f], u2=[%.4f], vn=[%d], v1=[%.4f], v2=[%.4f])",
             un,
             u1,
             u2,
             vn,
             v1,
             v2);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPGRID2F,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32 (un),
            APIInterceptor::APIFunctionArgument::create_fp32(u1),
            APIInterceptor::APIFunctionArgument::create_fp32(u2),
            APIInterceptor::APIFunctionArgument::create_i32 (vn),
            APIInterceptor::APIFunctionArgument::create_fp32(v1),
            APIInterceptor::APIFunctionArgument::create_fp32(v2),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPGRID2F,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAPGRID2FPROC>(OpenGL::g_cached_gl_map_grid_2f)(un,
                                                                              u1,
                                                                              u2,
                                                                              vn,
                                                                              v1,
                                                                              v2);
    }
}