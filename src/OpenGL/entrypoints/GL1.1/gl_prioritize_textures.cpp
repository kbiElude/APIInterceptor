/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_prioritize_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPrioritizeTextures(GLsizei n,
                                              const GLuint* textures,
                                              const GLclampf* priorities)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPrioritizeTexturesEXT(n=[%d] textures=[%p] priorities=[%p])",
                 n,
                 textures,
                 priorities);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32     (n),
                APIInterceptor::APIFunctionArgument::create_u32_ptr (textures),
                APIInterceptor::APIFunctionArgument::create_fp32_ptr(priorities),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPRIORITIZETEXTURES,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPRIORITIZETEXTURESEXTPROC>(OpenGL::g_cached_prioritize_textures_ext)(n,
                                                                                                   textures,
                                                                                                   priorities);
    }
}