/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_call_lists.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCallLists(GLsizei       n,
                                     GLenum        type,
                                     const GLvoid* lists)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glCallLists(n=[%d], type=[%s], lists=[%p])",
             n,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             lists);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCALLLISTS,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32     (n),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(lists),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCALLLISTS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCALLLISTSPROC>(OpenGL::g_cached_gl_call_lists)(n,
                                                                             type,
                                                                             lists);
    }
}