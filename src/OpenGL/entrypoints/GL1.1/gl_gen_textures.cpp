/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_gen_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenTextures(GLsizei n,
                                       GLuint* textures)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glGenTextures(n=[%d] textures=[%p])",
             static_cast<int32_t>(n),
             textures);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGENTEXTURES,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32    (n),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGENTEXTURES,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (OpenGL::g_cached_gl_gen_textures == nullptr)
    {
        OpenGL::g_cached_gl_gen_textures = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGenTextures");
    }

    // NOTE: This API call should always be passed through.
    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGENTEXTURESPROC>(OpenGL::g_cached_gl_gen_textures)(n,
                                                                                 textures);
    }
}