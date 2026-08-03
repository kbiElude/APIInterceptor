/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4d.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttrib4d(GLuint   index,
                                          GLdouble x,
                                          GLdouble y,
                                          GLdouble z,
                                          GLdouble w)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttrib4d(index=[%u] x=[%.4f] y=[%.4f] z=[%.4f] w=[%.4f])",
                 index,
                 static_cast<float>(x),
                 static_cast<float>(y),
                 static_cast<float>(z),
                 static_cast<float>(w) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32  (index),
                APIInterceptor::APIFunctionArgument::create_fp64 (x),
                APIInterceptor::APIFunctionArgument::create_fp64 (y),
                APIInterceptor::APIFunctionArgument::create_fp64 (z),
                APIInterceptor::APIFunctionArgument::create_fp64 (w),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4D,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(OpenGL::g_cached_gl_vertex_attrib_4d)(index,
                                                                                        x,
                                                                                        y,
                                                                                        z,
                                                                                        w);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32  (index),
            APIInterceptor::APIFunctionArgument::create_fp64 (x),
            APIInterceptor::APIFunctionArgument::create_fp64 (y),
            APIInterceptor::APIFunctionArgument::create_fp64 (z),
            APIInterceptor::APIFunctionArgument::create_fp64 (w),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB4D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
