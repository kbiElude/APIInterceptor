/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_mask.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilMask(GLuint mask)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glStencilMask(mask=[%u])",
             mask);


    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILMASK,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(mask),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILMASK,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSTENCILMASKPROC>(g_cached_gl_stencil_mask)(mask);
    }
}