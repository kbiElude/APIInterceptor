/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex2f(GLfloat x,
                                    GLfloat y)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertex2f(x=[%.4f], y=[%.4f])",
                 x,
                 y);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX2F,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp32(x),
                APIInterceptor::APIFunctionArgument::create_fp32(y),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX2F,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX2FPROC>(OpenGL::g_cached_gl_vertex_2f)(x,
                                                                           y);
    }
}