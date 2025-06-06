/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4i.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4i(GLint s,
                                      GLint t,
                                      GLint r,
                                      GLint q)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexCoord4i(s=[%d], t=[%d], r=[%d], q=[%d])",
                 s,
                 t,
                 r,
                 q);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4I,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32(s),
                APIInterceptor::APIFunctionArgument::create_i32(t),
                APIInterceptor::APIFunctionArgument::create_i32(r),
                APIInterceptor::APIFunctionArgument::create_i32(q),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4I,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXCOORD4IPROC>(OpenGL::g_cached_gl_tex_coord_4i)(s,
                                                                                t,
                                                                                r,
                                                                                q);
    }
}