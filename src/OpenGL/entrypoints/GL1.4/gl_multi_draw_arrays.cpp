/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawArrays(GLenum         mode,
                                           const GLint*   first,
                                           const GLsizei* count,
                                           GLsizei        drawcount)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMultiDrawArrays(mode=[%s] first=[%p] count=[%p] drawcount=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             first,
             count,
             static_cast<int32_t>(drawcount) );

    reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(g_cached_gl_multi_draw_arrays)(mode,
                                                                              first,
                                                                              count,
                                                                              drawcount);
}