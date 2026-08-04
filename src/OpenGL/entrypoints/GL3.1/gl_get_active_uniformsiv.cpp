/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniformsiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformsiv(GLuint        program,
                                               GLsizei       uniformCount,
                                               const GLuint* uniformIndices,
                                               GLenum        pname,
                                               GLint*        params)
{
    void*                                   post_callback_func_arg    = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr    = nullptr;
    void*                                   pre_callback_func_arg     = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr     = nullptr;
    bool                                    should_pass_through       = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                uniformIndices_chunk_id   = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetActiveUniformsiv(program=[%u] uniformCount=[%d] uniformIndices=[%p] pname=[%s] params=[%p])",
                 program,
                 static_cast<int32_t>(uniformCount),
                 uniformIndices,
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 params);

        uniformIndices_chunk_id = APIInterceptor::register_data_chunk(uniformIndices,
                                                                      (uniformIndices != nullptr) ? static_cast<uint32_t>(uniformCount) * sizeof(GLuint) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMSIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32           (program),
                APIInterceptor::APIFunctionArgument::create_i32           (uniformCount),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id (uniformIndices_chunk_id),
                APIInterceptor::APIFunctionArgument::create_u32_glenum    (pname),
                APIInterceptor::APIFunctionArgument::create_void_ptr      (params),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMSIV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>(OpenGL::g_cached_gl_get_active_uniformsiv)(program,
                                                                                                  uniformCount,
                                                                                                  uniformIndices,
                                                                                                  pname,
                                                                                                  params);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMSIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32           (program),
            APIInterceptor::APIFunctionArgument::create_i32           (uniformCount),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (uniformIndices_chunk_id),
            APIInterceptor::APIFunctionArgument::create_u32_glenum    (pname),
            APIInterceptor::APIFunctionArgument::create_void_ptr      (params),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETACTIVEUNIFORMSIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
