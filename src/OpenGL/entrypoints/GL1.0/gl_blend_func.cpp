/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_blend_func.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFunc(GLenum sfactor,
                                     GLenum dfactor)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBlendFunc(sfactor=[%s] dfactor=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(sfactor),
                 OpenGL::Utils::get_raw_string_for_gl_enum(dfactor) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNC,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(sfactor),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dfactor),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBLENDFUNC,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBLENDFUNCPROC>(OpenGL::g_cached_gl_blend_func)(sfactor,
                                                                             dfactor);
    }
}