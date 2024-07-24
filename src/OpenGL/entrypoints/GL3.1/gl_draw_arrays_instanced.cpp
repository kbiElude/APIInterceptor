/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_draw_arrays_instanced.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawArraysInstanced(GLenum  mode,
                                               GLint   first,
                                               GLsizei count,
                                               GLsizei instancecount)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawArraysInstanced(mode=[%s] first=[%d] count=[%d] instancecount=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             first,
             static_cast<int32_t>(count),
             static_cast<int32_t>(instancecount) );

    if (OpenGL::g_cached_gl_draw_arrays_instanced == nullptr)
    {
        OpenGL::g_cached_gl_draw_arrays_instanced = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDrawArraysInstanced");
    }

    reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(OpenGL::g_cached_gl_draw_arrays_instanced)(mode,
                                                                                              first,
                                                                                              count,
                                                                                              instancecount);
}