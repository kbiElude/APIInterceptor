/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_front_face.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFrontFace(GLenum mode)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glFrontFace(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFRONTFACE,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(mode)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFRONTFACE,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_front_face == nullptr)
    {
        OpenGL::g_cached_gl_front_face = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glFrontFace");
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFRONTFACEPROC>(OpenGL::g_cached_gl_front_face)(mode);
    }
}