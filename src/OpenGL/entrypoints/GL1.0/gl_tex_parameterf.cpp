/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterf.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexParameterf(GLenum  target,
                                         GLenum  pname,
                                         GLfloat param)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    if ( (pname == GL_TEXTURE_MIN_LOD)    ||
         (pname == GL_TEXTURE_MAX_LOD)    ||
         (pname == GL_TEXTURE_BASE_LEVEL) ||
         (pname == GL_TEXTURE_MAX_LEVEL)  )
    {
        AI_TRACE("glTexParameterf(target=[%s] pname=[%s] param=[%.4f])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 param);
    }
    else
    {
        AI_TRACE("glTexParameterf(target=[%s] pname=[%s] param=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 OpenGL::Utils::get_raw_string_for_gl_enum(static_cast<GLenum>(param) ));
    }

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERF,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32 (target),
            APIInterceptor::APIFunctionArgument::create_u32 (pname),
            APIInterceptor::APIFunctionArgument::create_fp32(param)
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERF,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_tex_parameterf == nullptr)
    {
        OpenGL::g_cached_gl_tex_parameterf = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glTexParameterf");
    }

    reinterpret_cast<PFNGLTEXPARAMETERFPROC>(OpenGL::g_cached_gl_tex_parameterf)(target,
                                                                                 pname,
                                                                                 param);
}