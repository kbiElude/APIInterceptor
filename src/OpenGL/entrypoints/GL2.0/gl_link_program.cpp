/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_link_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLinkProgram(GLuint program)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glLinkProgram(program=[%u])",
             program);

    if (OpenGL::g_cached_gl_link_program == nullptr)
    {
        OpenGL::g_cached_gl_link_program = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glLinkProgram");
    }

    return reinterpret_cast<PFNGLLINKPROGRAMPROC>(OpenGL::g_cached_gl_link_program)(program);
}