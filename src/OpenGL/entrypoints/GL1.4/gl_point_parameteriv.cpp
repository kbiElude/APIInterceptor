/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteriv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPointParameteriv(GLenum       pname,
                                            const GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPointParameteriv(pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_point_parameteriv == nullptr)
    {
        OpenGL::g_cached_gl_point_parameteriv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPointParameteriv");
    }

    reinterpret_cast<PFNGLPOINTPARAMETERIVPROC>(g_cached_gl_point_parameteriv)(pname,
                                                                               params);
}