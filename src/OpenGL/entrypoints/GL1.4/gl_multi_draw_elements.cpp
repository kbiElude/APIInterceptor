/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawElements(GLenum             mode,
                                             const GLsizei*     count,
                                             GLenum             type,
                                             const void* const* indices,
                                             GLsizei            drawcount)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMultiDrawElements(mode=[%s] count=[%p] type=[%s] indices=[%p] drawcount=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             count,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices,
             static_cast<int32_t>(drawcount) );

    if (OpenGL::g_cached_gl_multi_draw_elements == nullptr)
    {
        OpenGL::g_cached_gl_multi_draw_elements = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glMultiDrawElements");
    }

    reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(g_cached_gl_multi_draw_elements)(mode,
                                                                                  count,
                                                                                  type,
                                                                                  indices,
                                                                                  drawcount);
}