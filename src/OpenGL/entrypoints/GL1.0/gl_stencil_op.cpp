/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_op.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilOp(GLenum fail,
                                     GLenum zfail,
                                     GLenum zpass)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glStencilOp(fail=[%s] zfail=[%s] zpass=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(fail),
                 OpenGL::Utils::get_raw_string_for_gl_enum(zfail),
                 OpenGL::Utils::get_raw_string_for_gl_enum(zpass) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLSTENCILOP,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(fail),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(zfail),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(zpass),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLSTENCILOP,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLSTENCILOPPROC>(g_cached_gl_stencil_op)(fail,
                                                                     zfail,
                                                                     zpass);
    }
}