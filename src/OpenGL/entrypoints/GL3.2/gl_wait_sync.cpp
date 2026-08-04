/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.2/gl_wait_sync.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiWaitSync(GLsync     sync,
                                    GLbitfield flags,
                                    GLuint64   timeout)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glWaitSync(sync=[%p] flags=[%u] timeout=[%llu])",
                 sync,
                 flags,
                 timeout);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLWAITSYNC,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(sync),
                APIInterceptor::APIFunctionArgument::create_u32     (flags),
                APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<const void*>(&timeout)),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLWAITSYNC,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLWAITSYNCPROC>(OpenGL::g_cached_gl_wait_sync)(sync,
                                                                            flags,
                                                                            timeout);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLWAITSYNC,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(sync),
            APIInterceptor::APIFunctionArgument::create_u32     (flags),
            APIInterceptor::APIFunctionArgument::create_void_ptr(reinterpret_cast<const void*>(&timeout)),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLWAITSYNC,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}