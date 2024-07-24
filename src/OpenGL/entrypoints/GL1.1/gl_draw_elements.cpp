/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElements(GLenum      mode,
                                        GLsizei     count,
                                        GLenum      type,
                                        const void* indices)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawElements(mode=[%s] count=[%d] type=[%s] indices=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices);

    reinterpret_cast<PFNGLDRAWELEMENTSPROC>(OpenGL::g_cached_gl_draw_elements)(mode,
                                                                               count,
                                                                               type,
                                                                               indices);
}