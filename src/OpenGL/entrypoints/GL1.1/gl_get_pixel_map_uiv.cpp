/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPixelMapuiv(GLenum  map,
                                          GLuint* values)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetPixelMapuiv(map=[%s], values=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(map),
                 values);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETPIXELMAPUIV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(map),
                APIInterceptor::APIFunctionArgument::create_u32_ptr   (values),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETPIXELMAPUIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETPIXELMAPUIVPROC>(OpenGL::g_cached_gl_get_pixel_map_uiv)(map,
                                                                                         values);
    }
}