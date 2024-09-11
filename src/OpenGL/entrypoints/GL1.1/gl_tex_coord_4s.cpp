/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4s(GLshort s,
                                      GLshort t,
                                      GLshort r,
                                      GLshort q)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glTexCoord4s(s=[%d], t=[%d], r=[%d], q=[%d])",
             static_cast<int32_t>(s),
             static_cast<int32_t>(t),
             static_cast<int32_t>(r),
             static_cast<int32_t>(q) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4S,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i16(s),
            APIInterceptor::APIFunctionArgument::create_i16(t),
            APIInterceptor::APIFunctionArgument::create_i16(r),
            APIInterceptor::APIFunctionArgument::create_i16(q),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4S,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXCOORD4SPROC>(OpenGL::g_cached_gl_tex_coord_4s)(s,
                                                                                t,
                                                                                r,
                                                                                q);
    }
}