/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4f.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4f(GLfloat s,
                                      GLfloat t,
                                      GLfloat r,
                                      GLfloat q)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTexCoord4f(s=[%.4f], t=[%.4f], r=[%.4f], q=[%.4f])",
                 s,
                 t,
                 r,
                 q);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_fp32(s),
                APIInterceptor::APIFunctionArgument::create_fp32(t),
                APIInterceptor::APIFunctionArgument::create_fp32(r),
                APIInterceptor::APIFunctionArgument::create_fp32(q),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXCOORD4FPROC>(OpenGL::g_cached_gl_tex_coord_4f)(s,
                                                                                t,
                                                                                r,
                                                                                q);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(s),
            APIInterceptor::APIFunctionArgument::create_fp32(t),
            APIInterceptor::APIFunctionArgument::create_fp32(r),
            APIInterceptor::APIFunctionArgument::create_fp32(q),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}