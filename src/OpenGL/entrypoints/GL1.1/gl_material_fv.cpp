/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_material_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMaterialfv(GLenum         face,
                                      GLenum         pname,
                                      const GLfloat* params)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glMaterialfv(face=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMATERIALFV,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (face),
            APIInterceptor::APIFunctionArgument::create_u32     (pname),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(params),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMATERIALFV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMATERIALFVPROC>(OpenGL::g_cached_gl_material_fv)(face,
                                                                               pname,
                                                                               params);
    }
}