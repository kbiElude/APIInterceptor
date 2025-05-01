/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_gen_dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexGendv(GLenum    coord,
                                       GLenum    pname,
                                       GLdouble* params)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glGetTexGendv(coord=[%s], pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(coord),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETTEXGENDV,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (coord),
            APIInterceptor::APIFunctionArgument::create_u32     (pname),
            APIInterceptor::APIFunctionArgument::create_fp64_ptr(params),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETTEXGENDV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETTEXGENDVPROC>(OpenGL::g_cached_gl_get_tex_gen_dv)(coord,
                                                                                   pname,
                                                                                   params);
    }
}