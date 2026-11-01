/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL4.0/gl_draw_arrays_indirect.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/indirect_command_chunk.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiDrawArraysIndirect(GLenum      mode,
                                                                   const void* indirect)
{
    Interception::Hooks::OpenGL::IndirectCommandChunk indirect_chunk;
    void*                                             post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC           post_callback_func_ptr = nullptr;
    void*                                             pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC            pre_callback_func_ptr  = nullptr;
    bool                                              should_pass_through    = true;
    APIInterceptor::Tracker                           tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawArraysIndirect(mode=[%s] indirect=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(mode),
                 indirect);

        indirect_chunk = Interception::Hooks::OpenGL::IndirectCommandChunk::create_for_draw_arrays(indirect,
                                                                                                   1,
                                                                                                   0);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINDIRECT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                indirect_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINDIRECT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWARRAYSINDIRECTPROC>(Interception::Hooks::OpenGL::g_cached_gl_draw_arrays_indirect)(mode,
                                                                                                                     indirect);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINDIRECT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            indirect_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWARRAYSINDIRECT,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
