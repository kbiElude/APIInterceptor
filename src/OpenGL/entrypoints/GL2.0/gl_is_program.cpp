/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_is_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsProgram(GLuint program)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsProgram(program=[%u])",
             program);

    if (OpenGL::g_cached_gl_is_program == nullptr)
    {
        OpenGL::g_cached_gl_is_program = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsProgram");
    }

    return reinterpret_cast<PFNGLISPROGRAMPROC>(OpenGL::g_cached_gl_is_program)(program);
}