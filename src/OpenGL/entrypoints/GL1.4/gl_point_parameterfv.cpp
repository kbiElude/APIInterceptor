/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterfv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameterfv(GLenum         pname,
                                            const GLfloat* params)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                params_chunk_id        = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPointParameterfv(pname=[%s] params=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 params);

        AI_ASSERT(pname == GL_POINT_SIZE_MIN             ||
                  pname == GL_POINT_SIZE_MAX             ||
                  pname == GL_POINT_FADE_THRESHOLD_SIZE  ||
                  pname == GL_POINT_DISTANCE_ATTENUATION);

        /* GL_POINT_DISTANCE_ATTENUATION takes 3 floats; all other point pnames take 1. */
        const uint32_t n_floats = (pname == GL_POINT_DISTANCE_ATTENUATION) ? 3 : 1;

        params_chunk_id = APIInterceptor::register_data_chunk(params,
                                                              (params != nullptr) ? sizeof(GLfloat) * n_floats : 0);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERFV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERFV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(g_cached_gl_point_parameterfv)(pname,
                                                                                   params);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERFV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERFV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
