/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_draw_range_elements_base_vertex.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawRangeElementsBaseVertex(GLenum      mode,
                                                       GLuint      start,
                                                       GLuint      end,
                                                       GLsizei     count,
                                                       GLenum      type,
                                                       const void* indices,
                                                       GLint       basevertex)
{
    AI_TRACE("glDrawRangeElementsBaseVertex(mode=[%s] start=%u] end=[%u] count=[%d] type=[%s] indices=[%p] basevertex=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             start,
             end,
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices,
             basevertex);

    if (OpenGL::g_cached_gl_draw_range_elements_base_vertex == nullptr)
    {
        OpenGL::g_cached_gl_draw_range_elements_base_vertex = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDrawRangeElementsBaseVertex");
    }

    reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(OpenGL::g_cached_gl_draw_range_elements_base_vertex)(mode,
                                                                                                                start,
                                                                                                                end,
                                                                                                                count,
                                                                                                                type,
                                                                                                                indices,
                                                                                                                basevertex);
}
