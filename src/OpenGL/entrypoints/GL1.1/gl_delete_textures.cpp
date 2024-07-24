/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteTextures(GLsizei       n,
                                          const GLuint* textures)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glDeleteTextures(n=[%d] texture=[%p])",
             static_cast<int32_t>(n),
             textures);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32    (n),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_delete_textures == nullptr)
    {
        OpenGL::g_cached_gl_delete_textures = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteTextures");
    }

    reinterpret_cast<PFNGLDELETETEXTURESPROC>(OpenGL::g_cached_gl_delete_textures)(n,
                                                                                   textures);
}