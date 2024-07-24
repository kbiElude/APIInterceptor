/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3d(GLdouble s,
                                      GLdouble t,
                                      GLdouble r)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glTexCoord3d(s=[%.4lf], t=[%.4lf], r=[%.4lf])",
             s,
             t,
             r);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD3D,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp64(s),
            APIInterceptor::APIFunctionArgument::create_fp64(t),
            APIInterceptor::APIFunctionArgument::create_fp64(r),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD3D,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLTEXCOORD3DPROC>(OpenGL::g_cached_gl_tex_coord_3d)(s,
                                                                            t,
                                                                            r);
}