/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_copy_context.h"

BOOL WINAPI WGL::copy_context(HGLRC in_hglrc_source,
                              HGLRC in_hglrc_destination,
                              UINT  in_mask)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    BOOL                                result              = false;
    bool                                should_pass_through = true;

    AI_TRACE("wglCopyContext(in_hglrc_source=[%p] in_hglrc_destination=[%p] in_mask=[%d])",
               in_hglrc_source,
               in_hglrc_destination,
               in_mask);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc_source),
            APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc_destination),
            APIInterceptor::APIFunctionArgument::create_u32     (in_mask),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLCOPYCONTEXT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNWGLCOPYCONTEXTPROC>(WGL::g_cached_copy_context_func_ptr)(in_hglrc_source,
                                                                                              in_hglrc_destination,
                                                                                              in_mask);
    }

    return result;
}
