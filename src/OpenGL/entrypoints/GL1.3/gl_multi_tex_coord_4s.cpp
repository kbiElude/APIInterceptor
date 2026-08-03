/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4s.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiTexCoord4s(GLenum  target,
                                           GLshort s,
                                           GLshort t,
                                           GLshort r,
                                           GLshort q)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiTexCoord4s(target=[%s] s=[%d] t=[%d] r=[%d] q=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(s),
                 static_cast<int32_t>(t),
                 static_cast<int32_t>(r),
                 static_cast<int32_t>(q));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD4S,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i16       (s),
                APIInterceptor::APIFunctionArgument::create_i16       (t),
                APIInterceptor::APIFunctionArgument::create_i16       (r),
                APIInterceptor::APIFunctionArgument::create_i16       (q),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD4S,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTITEXCOORD4SPROC>(OpenGL::g_cached_gl_multi_tex_coord_4s)(target,
                                                                                           s,
                                                                                           t,
                                                                                           r,
                                                                                           q);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD4S,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_i16       (s),
            APIInterceptor::APIFunctionArgument::create_i16       (t),
            APIInterceptor::APIFunctionArgument::create_i16       (r),
            APIInterceptor::APIFunctionArgument::create_i16       (q),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTITEXCOORD4S,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}