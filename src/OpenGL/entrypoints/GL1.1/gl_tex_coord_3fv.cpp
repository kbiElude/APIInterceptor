/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3fv(const GLfloat* v)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glTexCoord3fv(v=[%p])",
             v);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD3FV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(v)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXCOORD3FV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLTEXCOORD3FVPROC>(OpenGL::g_cached_gl_tex_coord_3fv)(v);
}