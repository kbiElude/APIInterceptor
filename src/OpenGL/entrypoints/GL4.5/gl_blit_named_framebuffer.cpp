/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_blit_named_framebuffer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlitNamedFramebuffer(GLuint     readFramebuffer,
                                                GLuint     drawFramebuffer,
                                                GLint      srcX0,
                                                GLint      srcY0,
                                                GLint      srcX1,
                                                GLint      srcY1,
                                                GLint      dstX0,
                                                GLint      dstY0,
                                                GLint      dstX1,
                                                GLint      dstY1,
                                                GLbitfield mask,
                                                GLenum     filter)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBlitNamedFramebuffer(readFramebuffer=[%u] drawFramebuffer=[%u] srcX0=[%d] srcY0=[%d] srcX1=[%d] srcY1=[%d] dstX0=[%d] dstY0=[%d] dstX1=[%d] dstY1=[%d] mask=[%u] filter=[%s])",
                 readFramebuffer,
                 drawFramebuffer,
                 srcX0,
                 srcY0,
                 srcX1,
                 srcY1,
                 dstX0,
                 dstY0,
                 dstX1,
                 dstY1,
                 mask,
                 OpenGL::Utils::get_raw_string_for_gl_enum(filter) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLITNAMEDFRAMEBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (readFramebuffer),
                APIInterceptor::APIFunctionArgument::create_u32       (drawFramebuffer),
                APIInterceptor::APIFunctionArgument::create_i32       (srcX0),
                APIInterceptor::APIFunctionArgument::create_i32       (srcY0),
                APIInterceptor::APIFunctionArgument::create_i32       (srcX1),
                APIInterceptor::APIFunctionArgument::create_i32       (srcY1),
                APIInterceptor::APIFunctionArgument::create_i32       (dstX0),
                APIInterceptor::APIFunctionArgument::create_i32       (dstY0),
                APIInterceptor::APIFunctionArgument::create_i32       (dstX1),
                APIInterceptor::APIFunctionArgument::create_i32       (dstY1),
                APIInterceptor::APIFunctionArgument::create_u32       (mask),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(filter),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLITNAMEDFRAMEBUFFER,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLITNAMEDFRAMEBUFFERPROC>(OpenGL::g_cached_gl_blit_named_framebuffer)(readFramebuffer,
                                                                                                    drawFramebuffer,
                                                                                                    srcX0,
                                                                                                    srcY0,
                                                                                                    srcX1,
                                                                                                    srcY1,
                                                                                                    dstX0,
                                                                                                    dstY0,
                                                                                                    dstX1,
                                                                                                    dstY1,
                                                                                                    mask,
                                                                                                    filter);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLITNAMEDFRAMEBUFFER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (readFramebuffer),
            APIInterceptor::APIFunctionArgument::create_u32       (drawFramebuffer),
            APIInterceptor::APIFunctionArgument::create_i32       (srcX0),
            APIInterceptor::APIFunctionArgument::create_i32       (srcY0),
            APIInterceptor::APIFunctionArgument::create_i32       (srcX1),
            APIInterceptor::APIFunctionArgument::create_i32       (srcY1),
            APIInterceptor::APIFunctionArgument::create_i32       (dstX0),
            APIInterceptor::APIFunctionArgument::create_i32       (dstY0),
            APIInterceptor::APIFunctionArgument::create_i32       (dstX1),
            APIInterceptor::APIFunctionArgument::create_i32       (dstY1),
            APIInterceptor::APIFunctionArgument::create_u32       (mask),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(filter),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLITNAMEDFRAMEBUFFER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
