/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_validate_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiValidateProgram(GLuint program)
{
    AI_TRACE("glValidateProgram(program=[%u])",
             program);

    if (OpenGL::g_cached_gl_validate_program == nullptr)
    {
        OpenGL::g_cached_gl_validate_program = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glValidateProgram");
    }

    reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(OpenGL::g_cached_gl_validate_program)(program);
}