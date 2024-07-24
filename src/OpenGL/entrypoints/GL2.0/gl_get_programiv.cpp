/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_programiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetProgramiv(GLuint program,
                                        GLenum pname,
                                        GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetProgramiv(program=[%u] pname=[%s] params=[%p])",
             program,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_get_programiv == nullptr)
    {
        OpenGL::g_cached_gl_get_programiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetProgramiv");
    }

    reinterpret_cast<PFNGLGETPROGRAMIVPROC>(OpenGL::g_cached_gl_get_programiv)(program,
                                                                               pname,
                                                                               params);
}