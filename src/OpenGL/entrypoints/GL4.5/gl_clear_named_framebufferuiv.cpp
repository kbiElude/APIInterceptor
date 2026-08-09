/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_clear_named_framebufferuiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearNamedFramebufferuiv(GLuint        framebuffer,
                                                    GLenum        buffer,
                                                    GLint         drawbuffer,
                                                    const GLuint* value)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glClearNamedFramebufferuiv(framebuffer=[%u] buffer=[%s] drawbuffer=[%d] value=[%p])",
                 framebuffer,
                 OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
                 drawbuffer,
                 value);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERUIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (framebuffer),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(buffer),
                APIInterceptor::APIFunctionArgument::create_i32       (drawbuffer),
                APIInterceptor::APIFunctionArgument::create_u32_ptr   (value),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERUIV,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC>(OpenGL::g_cached_gl_clear_named_framebufferuiv)(framebuffer,
                                                                                                           buffer,
                                                                                                           drawbuffer,
                                                                                                           value);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERUIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (framebuffer),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(buffer),
            APIInterceptor::APIFunctionArgument::create_i32       (drawbuffer),
            APIInterceptor::APIFunctionArgument::create_u32_ptr   (value),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERUIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
