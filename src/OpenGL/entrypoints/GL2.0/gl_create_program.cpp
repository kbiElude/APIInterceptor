/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_create_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiCreateProgram()
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCreateProgram()");

    if (OpenGL::g_cached_gl_create_program == nullptr)
    {
        OpenGL::g_cached_gl_create_program = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glCreateProgram");
    }

    return reinterpret_cast<PFNGLCREATEPROGRAMPROC>(OpenGL::g_cached_gl_create_program)();
}