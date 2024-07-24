/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3i(GLint x,
                                    GLint y,
                                    GLint z)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glVertex3i(x=[%d], y=[%d], z=[%d])",
             x,
             y,
             z);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX3I,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(x),
            APIInterceptor::APIFunctionArgument::create_i32(y),
            APIInterceptor::APIFunctionArgument::create_i32(z),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX3I,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLVERTEX3IPROC>(OpenGL::g_cached_gl_vertex_3i)(x,
                                                                       y,
                                                                       z);
}