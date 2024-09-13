/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawElementsBaseVertex(GLenum             mode,
                                                       const GLsizei*     count,
                                                       GLenum             type,
                                                       const void* const* indices,
                                                       GLsizei            drawcount,
                                                       const GLint*       basevertex)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMultiDrawElementsBaseVertex(mode={%s] count=[%p] type=[%s] indices=[%p] drawcount=[%d] basevertex=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             count,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices,
             static_cast<int32_t>(drawcount),
             basevertex);

    reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>(g_cached_gl_multi_draw_elements_base_vertex)(mode,
                                                                                                        count,
                                                                                                        type,
                                                                                                        indices,
                                                                                                        drawcount,
                                                                                                        basevertex);
}