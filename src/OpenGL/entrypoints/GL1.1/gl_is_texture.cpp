/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsTexture(GLuint texture)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    GLboolean                           result              = GL_FALSE;
    bool                                should_pass_through = true;

    AI_TRACE("glIsTexture(texture=[%u])",
               texture);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLISTEXTURE,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(texture),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLISTEXTURE,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLISTEXTUREPROC>(OpenGL::g_cached_gl_is_texture)(texture);
    }

    return result;
}