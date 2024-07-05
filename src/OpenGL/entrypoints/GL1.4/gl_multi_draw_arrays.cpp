/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawArrays(GLenum         mode,
                                           const GLint*   first,
                                           const GLsizei* count,
                                           GLsizei        drawcount)
{
    AI_TRACE("glMultiDrawArrays(mode=[%s] first=[%p] count=[%p] drawcount=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             first,
             count,
             static_cast<int32_t>(drawcount) );

    if (OpenGL::g_cached_gl_multi_draw_arrays == nullptr)
    {
        OpenGL::g_cached_gl_multi_draw_arrays = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glMultiDrawArrays");
    }

    reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(g_cached_gl_multi_draw_arrays)(mode,
                                                                              first,
                                                                              count,
                                                                              drawcount);
}