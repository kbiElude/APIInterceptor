/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_pop_debug_group.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPopDebugGroup(void)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPopDebugGroup()");

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOPDEBUGGROUPPROC,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOPDEBUGGROUPPROC,
                                  0,
                                  nullptr,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPOPDEBUGGROUPPROC>(OpenGL::g_cached_gl_pop_debug_group)();
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPOPDEBUGGROUPPROC,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPOPDEBUGGROUPPROC,
                               post_callback_func_arg,
                               0,
                               nullptr,
                              &result_arg);
    }
}
