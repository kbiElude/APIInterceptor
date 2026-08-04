/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGetUniformBlockIndex(GLuint        program,
                                                  const GLchar* uniformBlockName)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLuint                                  result                 = GL_INVALID_INDEX;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetUniformBlockIndex(program=[%u] uniformBlockName=[%s])",
                 program,
                 uniformBlockName);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (program),
                APIInterceptor::APIFunctionArgument::create_void_ptr (uniformBlockName),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGETUNIFORMBLOCKINDEXPROC>(OpenGL::g_cached_gl_get_uniform_block_index)(program,
                                                                                                              uniformBlockName);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_u32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX,
                                   post_callback_func_arg,
                                   0,
                                   nullptr,
                                  &result_arg);
        }
    }

    return result;
}
