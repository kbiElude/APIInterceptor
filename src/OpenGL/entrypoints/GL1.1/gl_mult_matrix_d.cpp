/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_mult_matrix_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultMatrixd(const GLdouble* m)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glMultMatrixd(m=[%p])",
             m);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTMATRIXD,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const auto                                data_chunk_id   = APIInterceptor::register_data_chunk(m,
                                                                                                        static_cast<uint32_t>(sizeof(double) * 16));
        const APIInterceptor::APIFunctionArgument args         [] =
        {
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTMATRIXD,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTMATRIXDPROC>(OpenGL::g_cached_gl_mult_matrix_d)(m);
    }
}