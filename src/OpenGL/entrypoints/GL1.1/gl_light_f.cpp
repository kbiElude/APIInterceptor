/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLightf(GLenum  light,
                                  GLenum  pname,
                                  GLfloat param)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glLightf(light=[%s], pname=[%s], param=[%.4f])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(light),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 param);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLLIGHTF,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(light),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_fp32      (param),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLLIGHTF,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLLIGHTFPROC>(OpenGL::g_cached_gl_light_f)(light,
                                                                       pname,
                                                                       param);
    }
}