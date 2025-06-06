/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_1d.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyTexSubImage1D(GLenum  target,
                                             GLint   level,
                                             GLint   xoffset,
                                             GLint   x,
                                             GLint   y,
                                             GLsizei width)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCopyTexSubImage1D(target=[%s] level=[%d] xoffset=[%d] x=[%d] y=[%d] width=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 xoffset,
                 x,
                 y,
                 static_cast<int32_t>(width) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYTEXSUBIMAGE1D,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_i32       (xoffset),
                APIInterceptor::APIFunctionArgument::create_i32       (x),
                APIInterceptor::APIFunctionArgument::create_i32       (y),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYTEXSUBIMAGE1D,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOPYTEXSUBIMAGE1DPROC>(OpenGL::g_cached_gl_copy_tex_sub_image_1D)(target,
                                                                                                level,
                                                                                                xoffset,
                                                                                                x,
                                                                                                y,
                                                                                                width);
    }
}