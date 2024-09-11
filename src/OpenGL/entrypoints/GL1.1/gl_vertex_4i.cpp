/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4i(GLint x,
                                    GLint y,
                                    GLint z,
                                    GLint w)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glVertex4i(x=[%d], y=[%d], z=[%d], w=[%d])",
             x,
             y,
             z,
             w);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX4I,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(x),
            APIInterceptor::APIFunctionArgument::create_i32(y),
            APIInterceptor::APIFunctionArgument::create_i32(z),
            APIInterceptor::APIFunctionArgument::create_i32(w),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX4I,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX4IPROC>(OpenGL::g_cached_gl_vertex_4i)(x,
                                                                           y,
                                                                           z,
                                                                           w);
    }
}