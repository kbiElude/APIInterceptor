/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_blend_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFunc(GLenum sfactor,
                                     GLenum dfactor)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glBlendFunc(sfactor=[%s] dfactor=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(sfactor),
             OpenGL::Utils::get_raw_string_for_gl_enum(dfactor) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNC,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(sfactor),
            APIInterceptor::APIFunctionArgument::create_u32(dfactor),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNC,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_blend_func == nullptr)
    {
        OpenGL::g_cached_gl_blend_func = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBlendFunc");
    }

    reinterpret_cast<PFNGLBLENDFUNCPROC>(OpenGL::g_cached_gl_blend_func)(sfactor,
                                                                         dfactor);
}