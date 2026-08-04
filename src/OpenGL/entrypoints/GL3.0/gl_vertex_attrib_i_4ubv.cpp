/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribI4ubv(GLuint         index,
                                             const GLubyte* v)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                v_chunk_id             = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttribI4ubv(index=[%u] v=[%p])",
                 index,
                 v);

        v_chunk_id = APIInterceptor::register_data_chunk(v,
                                                         (v != nullptr) ? 4u * sizeof(GLubyte) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I4UBV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32           (index),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (v_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I4UBV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIBI4UBVPROC>(OpenGL::g_cached_gl_vertex_attrib_i_4ubv)(index,
                                                                                               v);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I4UBV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (index),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (v_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_I4UBV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
