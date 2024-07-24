/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexEnvi(GLenum target,
                                   GLenum pname,
                                   GLint  param)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glTexEnvi(target=[%s], pname=[%s], param=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             param);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXENVI,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(target),
            APIInterceptor::APIFunctionArgument::create_u32(pname),
            APIInterceptor::APIFunctionArgument::create_i32(param),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXENVI,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    reinterpret_cast<PFNGLTEXENVIPROC>(OpenGL::g_cached_gl_tex_env_i)(target,
                                                                      pname,
                                                                      param);
}