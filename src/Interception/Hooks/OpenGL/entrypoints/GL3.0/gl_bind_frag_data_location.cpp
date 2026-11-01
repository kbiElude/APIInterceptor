/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.0/gl_bind_frag_data_location.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/string_chunk.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindFragDataLocation(GLuint        program,
                                                GLuint        color,
                                                const GLchar* name)
{
    OpenGL::StringChunk                     name_chunk(name);
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindFragDataLocation(program=[%u] color=[%u] name=[%s])",
                 program,
                 color,
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATION,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (program),
                APIInterceptor::APIFunctionArgument::create_u32          (color),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(name_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATION,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>(OpenGL::g_cached_gl_bind_frag_data_location)(program,
                                                                                                     color,
                                                                                                     name);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATION,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32          (program),
            APIInterceptor::APIFunctionArgument::create_u32          (color),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(name_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATION,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
