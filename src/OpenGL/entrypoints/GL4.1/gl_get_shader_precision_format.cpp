/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.1/gl_get_shader_precision_format.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetShaderPrecisionFormat(GLenum   shadertype,
                                                    GLenum   precisiontype,
                                                    GLint*   range,
                                                    GLint*   precision)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetShaderPrecisionFormat(shadertype=[%s] precisiontype=[%s] range=[%p] precision=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(shadertype),
                 OpenGL::Utils::get_raw_string_for_gl_enum(precisiontype),
                 range,
                 precision);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSHADERPRECISIONFORMAT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(shadertype),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(precisiontype),
                APIInterceptor::APIFunctionArgument::create_i32_ptr   (range),
                APIInterceptor::APIFunctionArgument::create_i32_ptr   (precision),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSHADERPRECISIONFORMAT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETSHADERPRECISIONFORMATPROC>(OpenGL::g_cached_gl_get_shader_precision_format)(shadertype,
                                                                                                             precisiontype,
                                                                                                             range,
                                                                                                             precision);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETSHADERPRECISIONFORMAT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          range_chunk_id     = APIInterceptor::register_data_chunk(range,
                                                                                                     (range != nullptr) ? 2 * sizeof(GLint) : 0);
        const auto                          precision_chunk_id = APIInterceptor::register_data_chunk(precision,
                                                                                                     (precision != nullptr) ? sizeof(GLint) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (shadertype),
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (precisiontype),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (range_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (precision_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETSHADERPRECISIONFORMAT,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
