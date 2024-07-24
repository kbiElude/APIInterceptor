/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4f(GLfloat s,
                                      GLfloat t,
                                      GLfloat r,
                                      GLfloat q)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glTexCoord4f(s=[%.4f], t=[%.4f], r=[%.4f], q=[%.4f])",
             s,
             t,
             r,
             q);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32(s),
            APIInterceptor::APIFunctionArgument::create_fp32(t),
            APIInterceptor::APIFunctionArgument::create_fp32(r),
            APIInterceptor::APIFunctionArgument::create_fp32(q),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD4F,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLTEXCOORD4FPROC>(OpenGL::g_cached_gl_tex_coord_4f)(s,
                                                                            t,
                                                                            r,
                                                                            q);
}