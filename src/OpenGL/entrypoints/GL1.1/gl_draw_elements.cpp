/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElements(GLenum      mode,
                                        GLsizei     count,
                                        GLenum      type,
                                        const void* indices)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glDrawElements(mode=[%s] count=[%d] type=[%s] indices=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (mode),
            APIInterceptor::APIFunctionArgument::create_i32     (count),
            APIInterceptor::APIFunctionArgument::create_u32     (type),
            APIInterceptor::APIFunctionArgument::create_void_ptr(indices),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWELEMENTSPROC>(OpenGL::g_cached_gl_draw_elements)(mode,
                                                                                   count,
                                                                                   type,
                                                                                   indices);
    }
}