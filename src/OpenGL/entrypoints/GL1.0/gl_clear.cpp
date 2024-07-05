/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_clear.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClear(GLbitfield mask)
{
    AI_TRACE("glClear(mask=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Clear_Buffer_Mask, mask) );

    if (OpenGL::g_cached_gl_clear == nullptr)
    {
        OpenGL::g_cached_gl_clear = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClear");
    }

    reinterpret_cast<PFNGLCLEARPROC>(OpenGL::g_cached_gl_clear)(mask);
}