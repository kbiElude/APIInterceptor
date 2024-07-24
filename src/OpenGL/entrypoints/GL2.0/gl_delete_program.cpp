/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_delete_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteProgram(GLuint program)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteProgram(program=[%d])",
             program);

    if (OpenGL::g_cached_gl_delete_program == nullptr)
    {
        OpenGL::g_cached_gl_delete_program = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteProgram");
    }

    reinterpret_cast<PFNGLDELETEPROGRAMPROC>(OpenGL::g_cached_gl_delete_program)(program);
}