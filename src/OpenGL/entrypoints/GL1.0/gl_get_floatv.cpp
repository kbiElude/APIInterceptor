/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_floatv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetFloatv(GLenum   pname,
                                     GLfloat* data)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetFloatv(pname=[%s] data=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 data);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETFLOATV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_fp32_ptr  (data),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETFLOATV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETFLOATVPROC>(OpenGL::g_cached_gl_get_floatv)(pname,
                                                                             data);
    }
}