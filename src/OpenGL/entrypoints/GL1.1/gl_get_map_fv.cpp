/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_map_fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetMapfv(GLenum   target,
                                    GLenum   query,
                                    GLfloat* v)
{
    AI_TRACE("glGetMapfv(target=[%s], query=[%s], v=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(query),
             v);

    reinterpret_cast<PFNGLGETMAPFVPROC>(OpenGL::g_cached_gl_get_map_fv)(target,
                                                                        query,
                                                                        v);
}