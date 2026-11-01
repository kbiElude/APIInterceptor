/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL4.3/gl_multi_draw_arrays_indirect.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/indirect_command_chunk.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawArraysIndirect(GLenum      mode,
                                                   const void* indirect,
                                                   GLsizei     drawcount,
                                                   GLsizei     stride)
{
    OpenGL::IndirectCommandChunk            indirect_chunk;
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiDrawArraysIndirect(mode=[%s] indirect=[%p] drawcount=[%d] stride=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 indirect,
                 static_cast<int32_t>(drawcount),
                 static_cast<int32_t>(stride));

        indirect_chunk = OpenGL::IndirectCommandChunk::create_for_draw_arrays(indirect,
                                                                              drawcount,
                                                                              stride);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYSINDIRECT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                indirect_chunk.get_arg(),
                APIInterceptor::APIFunctionArgument::create_i32       (drawcount),
                APIInterceptor::APIFunctionArgument::create_i32       (stride),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYSINDIRECT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTIDRAWARRAYSINDIRECTPROC>(OpenGL::g_cached_gl_multi_draw_arrays_indirect)(mode,
                                                                                                            indirect,
                                                                                                            drawcount,
                                                                                                            stride);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYSINDIRECT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            indirect_chunk.get_arg(),
            APIInterceptor::APIFunctionArgument::create_i32       (drawcount),
            APIInterceptor::APIFunctionArgument::create_i32       (stride),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWARRAYSINDIRECT,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
