/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_gen_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexGeniv(GLenum coord,
                                       GLenum pname,
                                       GLint* params)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetTexGeniv(coord=[%s], pname=[%s], params=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(coord),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 params);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTEXGENIV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32    (coord),
                APIInterceptor::APIFunctionArgument::create_u32    (pname),
                APIInterceptor::APIFunctionArgument::create_i32_ptr(params),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTEXGENIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETTEXGENIVPROC>(OpenGL::g_cached_gl_get_tex_gen_iv)(coord,
                                                                                   pname,
                                                                                   params);
    }
}