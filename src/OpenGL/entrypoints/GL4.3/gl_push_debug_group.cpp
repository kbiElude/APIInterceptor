/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_push_debug_group.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPushDebugGroup(GLenum        source,
                                          GLuint        id,
                                          GLsizei       length,
                                          const GLchar* message)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPushDebugGroup(source=[%s] id=[%u] length=[%d] message=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(source),
                 id,
                 static_cast<int32_t>(length),
                 message);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPUSHDEBUGGROUP,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(source),
                APIInterceptor::APIFunctionArgument::create_u32       (id),
                APIInterceptor::APIFunctionArgument::create_i32       (length),
                APIInterceptor::APIFunctionArgument::create_i8_ptr    (message),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPUSHDEBUGGROUP,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPUSHDEBUGGROUPPROC>(OpenGL::g_cached_gl_push_debug_group)(source,
                                                                                         id,
                                                                                         length,
                                                                                         message);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPUSHDEBUGGROUP,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(source),
            APIInterceptor::APIFunctionArgument::create_u32       (id),
            APIInterceptor::APIFunctionArgument::create_i32       (length),
            APIInterceptor::APIFunctionArgument::create_i8_ptr    (message),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPUSHDEBUGGROUP,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
