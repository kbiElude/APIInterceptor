/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/tracker.h"
#include "WGL/entrypoints/wgl_delete_context.h"
#include "WGL/globals.h"

BOOL WINAPI WGL::delete_context(HGLRC in_hglrc)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglDeleteContext(in_hglrc=[%p])",
                   in_hglrc);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLDELETECONTEXT,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLDELETECONTEXT,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }

        // This function should always patch through down the driver stack!
        AI_ASSERT(should_pass_through);
    }

    return reinterpret_cast<PFNWGLDELETECONTEXTPROC>(WGL::g_cached_delete_context_func_ptr)(in_hglrc);
}
