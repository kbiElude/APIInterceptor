/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameteriv(GLenum       pname,
                                            const GLint* params)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPointParameteriv(pname=[%s] params=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 params);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERIV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            AI_ASSERT(pname == GL_POINT_SIZE_MIN             ||
                      pname == GL_POINT_SIZE_MAX             ||
                      pname == GL_POINT_FADE_THRESHOLD_SIZE  ||
                      pname == GL_POINT_DISTANCE_ATTENUATION);

            /* GL_POINT_DISTANCE_ATTENUATION takes 3 ints; all other point pnames take 1. */
            const uint32_t n_ints          = (pname == GL_POINT_DISTANCE_ATTENUATION) ? 3 : 1;
            const auto     params_chunk_id = APIInterceptor::register_data_chunk(params,
                                                                                 (params != nullptr) ? sizeof(GLint) * n_ints : 0);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (pname),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(params_chunk_id),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOINTPARAMETERIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>(g_cached_gl_point_parameteriv)(pname,
                                                                                   params);
    }
}