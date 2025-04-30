/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexGend(GLenum   coord,
                                   GLenum   pname,
                                   GLdouble param)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glTexGend(coord=[%s], pname=[%s], param=[%.4lf])",
             OpenGL::Utils::get_raw_string_for_gl_enum(coord),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXGEND,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (coord),
            APIInterceptor::APIFunctionArgument::create_u32 (pname),
            APIInterceptor::APIFunctionArgument::create_fp64(param),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXGEND,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXGENDPROC>(OpenGL::g_cached_gl_tex_gen_d)(coord,
                                                                          pname,
                                                                          param);
    }
}