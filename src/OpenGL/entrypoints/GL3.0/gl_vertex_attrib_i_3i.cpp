/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI3i(GLuint index,
                                           GLint  x,
                                           GLint  y,
                                           GLint  z)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttribI3i(index=[%u] x=[%d] y=[%d] z=[%d])",
                 index,
                 x,
                 y,
                 z);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I3I,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(index),
                APIInterceptor::APIFunctionArgument::create_i32(x),
                APIInterceptor::APIFunctionArgument::create_i32(y),
                APIInterceptor::APIFunctionArgument::create_i32(z),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I3I,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIBI3IPROC>(OpenGL::g_cached_gl_vertex_attrib_i_3i)(index,
                                                                                           x,
                                                                                           y,
                                                                                           z);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I3I,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(index),
            APIInterceptor::APIFunctionArgument::create_i32(x),
            APIInterceptor::APIFunctionArgument::create_i32(y),
            APIInterceptor::APIFunctionArgument::create_i32(z),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I3I,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
