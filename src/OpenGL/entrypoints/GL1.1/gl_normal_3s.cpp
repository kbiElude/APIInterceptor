/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3s.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3s(GLshort nx,
                                    GLshort ny,
                                    GLshort nz)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glNormal3s(nx=[%d], ny=[%d], nz=[%d])",
                 static_cast<uint32_t>(nx),
                 static_cast<uint32_t>(ny),
                 static_cast<uint32_t>(nz));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNORMAL3S,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i16(nx),
                APIInterceptor::APIFunctionArgument::create_i16(ny),
                APIInterceptor::APIFunctionArgument::create_i16(nz),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNORMAL3S,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLNORMAL3SPROC>(OpenGL::g_cached_gl_normal_3s)(nx,
                                                                           ny,
                                                                           nz);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLNORMAL3S,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i16(nx),
            APIInterceptor::APIFunctionArgument::create_i16(ny),
            APIInterceptor::APIFunctionArgument::create_i16(nz),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLNORMAL3S,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}