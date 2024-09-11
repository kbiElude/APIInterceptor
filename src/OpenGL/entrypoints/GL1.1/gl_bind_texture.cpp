/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_bind_texture.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindTexture(GLenum target,
                                       GLuint texture)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glBindTexture(target=[%s] texture=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             texture);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDTEXTURE,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(target),
            APIInterceptor::APIFunctionArgument::create_u32(texture),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDTEXTURE,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_bind_texture == nullptr)
    {
        OpenGL::g_cached_gl_bind_texture = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBindTexture");
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDTEXTUREPROC>(OpenGL::g_cached_gl_bind_texture)(target,
                                                                                 texture);
    }
}