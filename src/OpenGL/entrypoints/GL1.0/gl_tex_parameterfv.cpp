/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameterfv(GLenum         target,
                                          GLenum         pname,
                                          const GLfloat* params)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glTexParameterfv(target=[%s] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERFV,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (target),
            APIInterceptor::APIFunctionArgument::create_u32     (pname),
            APIInterceptor::APIFunctionArgument::create_fp32_ptr(params)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERFV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXPARAMETERFVPROC>(OpenGL::g_cached_gl_tex_parameterfv)(target,
                                                                                       pname,
                                                                                       params);
    }
}