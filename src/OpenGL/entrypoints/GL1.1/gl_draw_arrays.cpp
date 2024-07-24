/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_draw_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawArrays(GLenum  mode,
                                      GLint   first,
                                      GLsizei count)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawArrays(mode=[%s] first=[%d] count=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             first,
             static_cast<int32_t>(count) );

    if (OpenGL::g_cached_gl_delete_framebuffers == nullptr)
    {
        OpenGL::g_cached_gl_delete_framebuffers = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteFramebuffers");
    }

    reinterpret_cast<PFNGLDRAWARRAYSPROC>(OpenGL::g_cached_gl_draw_arrays)(mode,
                                                                           first,
                                                                           count);
}