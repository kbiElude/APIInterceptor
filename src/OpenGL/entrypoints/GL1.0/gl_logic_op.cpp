/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_logic_op.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLogicOp(GLenum opcode)
{
    AI_TRACE("glLogicOp(opcode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(opcode) );

    if (OpenGL::g_cached_gl_logic_op == nullptr)
    {
        OpenGL::g_cached_gl_logic_op = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glLogicOp");
    }

    reinterpret_cast<PFNGLLOGICOPPROC>(OpenGL::g_cached_gl_logic_op)(opcode);
}