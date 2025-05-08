/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_elements_instanced_base_vertex.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElementsInstancedBaseVertex(GLenum      mode,
                                                           GLsizei     count,
                                                           GLenum      type,
                                                           const void* indices,
                                                           GLsizei     instancecount,
                                                           GLint       basevertex)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawElementsInstancedBaseVertex(mode=[%s] count={%d] type=[%s] indices=[%p] instancecount=[%d] basevertex=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices,
             static_cast<int32_t>(instancecount),
             basevertex);

    reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(OpenGL::g_cached_gl_draw_elements_instanced_base_vertex)(mode,
                                                                                                                        count,
                                                                                                                        type,
                                                                                                                        indices,
                                                                                                                        instancecount,
                                                                                                                        basevertex);
}