/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexImage(GLenum target,
                                       GLint  level,
                                       GLenum format,
                                       GLenum type,
                                       void*  pixels)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetTexImage(target=[%s] level=[%d] format=[%s] type=[%s] pixels=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 level,
                 OpenGL::Utils::get_raw_string_for_gl_enum(format),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 pixels);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32     (target),
                APIInterceptor::APIFunctionArgument::create_i32     (level),
                APIInterceptor::APIFunctionArgument::create_u32     (format),
                APIInterceptor::APIFunctionArgument::create_u32     (type),
                APIInterceptor::APIFunctionArgument::create_void_ptr(pixels),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTEXIMAGE,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETTEXIMAGEPROC>(OpenGL::g_cached_gl_get_tex_image)(target,
                                                                                  level,
                                                                                  format,
                                                                                  type,
                                                                                  pixels);
    }
}