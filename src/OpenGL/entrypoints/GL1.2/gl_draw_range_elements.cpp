/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.2/gl_draw_range_elements.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawRangeElements(GLenum      mode,
                                             GLuint      start,
                                             GLuint      end,
                                             GLsizei     count,
                                             GLenum      type,
                                             const void* indices)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawRangeElements(mode=[%s] start=[%d] end=[%d] count={%d] type=[%s] indices=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             static_cast<int32_t>(start),
             static_cast<int32_t>(end),
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices);

    reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(OpenGL::g_cached_gl_draw_range_elements)(mode,
                                                                                         start,
                                                                                         end,
                                                                                         count,
                                                                                         type,
                                                                                         indices);
}