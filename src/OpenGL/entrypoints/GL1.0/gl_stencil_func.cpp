/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilFunc(GLenum func,
                                       GLint  ref,
                                       GLuint mask)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glStencilFunc(func=[%s] ref=[%d] mask=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref,
             mask);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(func),
            APIInterceptor::APIFunctionArgument::create_i32(ref),
            APIInterceptor::APIFunctionArgument::create_u32(mask),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILFUNC,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSTENCILFUNCPROC>(g_cached_gl_stencil_func)(func,
                                                                         ref,
                                                                         mask);
    }
}